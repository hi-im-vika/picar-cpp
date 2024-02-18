/**
 * CPiControl.cpp - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/CPiControl.h"

CPiControl::CPiControl() {
    _device = "";
}

CPiControl::~CPiControl() {
    gpioTerminate();
}

void CPiControl::init_gpio(const std::vector<int> &input_pins, std::vector<int> &output_pins) {
    if (gpioInitialise() < 0) std::exit(-1);
    if (!input_pins.empty()) {
        for(auto i : input_pins) {
            gpioSetMode(i, PI_INPUT);
        }
    }
    if (!output_pins.empty()) {
        for (auto i : output_pins) {
            gpioSetMode(i, PI_OUTPUT);
        }
    }
}

void CPiControl::init_evdev_joystick() {
    std::cout << "joystick init" << std::endl;

    while (_device.empty()) {
        std::cout << "Searching for joystick..." << std::endl;
        // partially from https://stackoverflow.com/a/2340309
        for (const auto & entry : std::filesystem::directory_iterator("/dev/input")) {
            if (entry.path().string().find("event") != std::string::npos) {
                // from libevdev sample code
                auto fd = open(entry.path().string().c_str(), O_RDONLY|O_NONBLOCK);
                struct libevdev *dev = nullptr;
                int rc = libevdev_new_from_fd(fd, &dev);

                // looking for the dualshock 4
                if (std::string(libevdev_get_name(dev)) == "Wireless Controller") {
                    _device = entry.path().string();
                }
                int close(fd);
            }
        }
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
    }
    std::cout << "Joystick found at " << _device << std::endl;
    _joystick_fd = open(_device.c_str(), O_RDONLY|O_NONBLOCK);

    // TODO: handle if joystick cannot connect here
    libevdev_new_from_fd(_joystick_fd, &_evdev_dev);
}

void CPiControl::stop() {
    gpioTerminate();
}

int CPiControl::js_has_new_event() {
    if (_evdev_dev != nullptr) return libevdev_has_event_pending(_evdev_dev);
    return 0;
}

void CPiControl::js_get_next_thing() {
    if (_evdev_dev != nullptr && libevdev_has_event_pending(_evdev_dev)) {
        libevdev_next_event(_evdev_dev, LIBEVDEV_READ_FLAG_NORMAL, &_evdev_dev_event);
        if (_evdev_dev_event.type == EV_ABS)
            switch (_evdev_dev_event.code) {
                case 0:
                    std::cout << "Got input_event";
                    std::cout << " type=" << _evdev_dev_event.type;
                    std::cout << " code=" << "left analog x";
                    std::cout << " value=" << _evdev_dev_event.value << std::endl;
                    _vals[0] = _evdev_dev_event.value;
                    break;
                case 4:
                    std::cout << "Got input_event";
                    std::cout << " type=" << _evdev_dev_event.type;
                    std::cout << " code=" << "right analog y";
                    std::cout << " value=" << _evdev_dev_event.value << std::endl;
                    _vals[1] = _evdev_dev_event.value;
                    break;
                default:
                    break;
        }
    }
}
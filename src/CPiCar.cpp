/**
 * CPiCar.cpp - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/CPiCar.h"

CPiCar::CPiCar() {
    _output_pins.push_back(STEERING_PIN_BCM);
    _output_pins.push_back(THROTTLE_PIN_BCM);
    _output_pins.push_back(HEARTBEAT_PIN_BCM);
    _control.init_gpio(_input_pins, _output_pins);
    gpioHardwarePWM(STEERING_PIN_BCM, 100, 150000);
    gpioHardwarePWM(THROTTLE_PIN_BCM, 100, 150000);
//    gpioSetPWMrange(STEERING_PIN_BCM, 40000);
//    gpioSetPWMrange(THROTTLE_PIN_BCM,40000);
//    gpioSetPWMfrequency(STEERING_PIN_BCM,100);
//    gpioSetPWMfrequency(THROTTLE_PIN_BCM,100);
//    gpioPWM(STEERING_PIN_BCM,6000);
//    gpioPWM(THROTTLE_PIN_BCM,6000);
//    gpioWrite(HEARTBEAT_PIN_BCM, PI_ON);
    std::thread thread_for_joysticking(joystick_thread, this);
    thread_for_joysticking.detach();
}

CPiCar::~CPiCar() {
    _control.stop();
}

// yeah its draw but you know what i mean
void CPiCar::draw() {
    // TODO: implement safe mode on controller disconnect
    if (!_do_draw) {
        // send a log every second, no need for all the time
        long long now = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - CPiCar::_start).count();
        if ((!(now % 1000)) && _last_time != now) {
            _logger.show_log("CPiCar", "WARN", "_draw not asserted, defaulting to neutral values");
            _last_time = now;
        } else {
            _last_time = now;
        }
        gpioHardwarePWM(STEERING_PIN_BCM, 100, 150000);
        gpioHardwarePWM(THROTTLE_PIN_BCM, 100, 150000);
    } else {

        // get joystick values
        _last_js_values = _control.get_js_values();

        // perform trim adjustment
        if (_last_js_values[VECT_DPAD_XAXIS] != 0 && !_dpad_pressed_x) {
            switch (_last_js_values[VECT_DPAD_XAXIS]) {
                case -1:
                    _trim++;
                    break;
                case 1:
                    _trim--;
                    break;
                default:
                    break;
            }
            _dpad_pressed_x = true;
        }
        if (_last_js_values[VECT_DPAD_XAXIS] == 0 && _dpad_pressed_x) {
            _dpad_pressed_x = false;
        }

        // if greater than deadzone threshold
        if (_last_js_values[VECT_LEFT_XAXIS] > 138 || _last_js_values[VECT_LEFT_XAXIS] < 117) {
            gpioHardwarePWM(STEERING_PIN_BCM, 100, 200000 + (int) ((_last_js_values[VECT_LEFT_XAXIS] / 255.0) * -100000));
        } else {
            gpioHardwarePWM(STEERING_PIN_BCM, 100, 200000 + -50000 + (_trim * 1000));
        }
        if (_last_js_values[VECT_RIGHT_YAXIS] > 138 || _last_js_values[VECT_RIGHT_YAXIS] < 117) {
            gpioHardwarePWM(THROTTLE_PIN_BCM, 100, 200000 + (int) ((_last_js_values[VECT_RIGHT_YAXIS] / 255.0) * -100000));
        } else {
            gpioHardwarePWM(THROTTLE_PIN_BCM, 100, 200000 + -50000);
        }

//    // DEBUG: (gpioPWM) cycles PWM between 1 ms to 2 ms duty cycle
//    for (int duty = 0; duty < 4000; duty++) {
////        gpioPWM(STEERING_PIN_BCM,4000 + duty);
//        _last_js_values = _control.get_js_values();
//        gpioPWM(STEERING_PIN_BCM,4000 + (int) ((_last_js_values[0] / 255.0) * 4000));
//        gpioPWM(THROTTLE_PIN_BCM,8000 - duty);
//        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1));
//    }
//    for (int duty = 0; duty < 4000; duty++) {
////        gpioPWM(STEERING_PIN_BCM,8000 - duty);
//        _last_js_values = _control.get_js_values();
//        gpioPWM(STEERING_PIN_BCM,4000 + (int) ((_last_js_values[0] / 255.0) * 4000));
//        gpioPWM(THROTTLE_PIN_BCM,4000 + duty);
//        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1));
//    }
    }
}

void CPiCar::update() {
    if (_do_heartbeat) heartbeat();
    if (_found_joystick) _control.js_get_next_thing();
}

void CPiCar::heartbeat() {
    long long now = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - CPiCar::_start).count();
    if ((!(now % 1000) && now != _last_heartbeat) || (!((now % 1000) - 200) && now != _last_heartbeat)) {
        gpioWrite(HEARTBEAT_PIN_BCM, PI_ON);
        _last_heartbeat = now;
    }
    if ((!((now % 1000) - 50) && now != _last_heartbeat) || (!((now % 1000) - 250) && now != _last_heartbeat)) {
        gpioWrite(HEARTBEAT_PIN_BCM, PI_OFF);
        _last_heartbeat = now;
    }
}

void CPiCar::joystick() {
    /**
     * 1. check to see if saved joystick is still there. if yes, go to next iteration
     * 2. otherwise, no joystick is there. go into joystick finding loop.
     */
    _found_joystick = false;
    for (const auto &entry: std::filesystem::directory_iterator("/dev/input")) {
        if (entry.path().string() == _control.get_device_path()) {
            _found_joystick = true;
        }
    }
    if (!_found_joystick) {
        // set flag to stop updating
        _do_draw = false;
        _do_heartbeat = false;
        _control.stop();
        _logger.show_log("CPiCar", "WARN", "Joystick not found");
        gpioWrite(HEARTBEAT_PIN_BCM, PI_ON);
        while (_control.get_device_path().empty()) {
            _control.init_evdev_joystick();
        }
        _logger.show_log("CPiCar", "INFO", "Joystick found at " + _control.get_device_path());
        gpioWrite(HEARTBEAT_PIN_BCM, PI_OFF);
        _do_heartbeat = true;
        _do_draw = true;
    }
}

void CPiCar::joystick_thread(CPiCar *who_called_me) {
    while (!who_called_me->_do_exit) {
        who_called_me->joystick();
    }
}
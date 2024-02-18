/**
 * CPiControl.h - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#pragma once

#define HEARTBEAT_PIN_BCM 17
#define STEERING_PIN_BCM 12
#define THROTTLE_PIN_BCM 13

#include <iostream>
#include <vector>
#include <filesystem>
#include <pigpio.h>
#include <thread>

// Linux specific includes
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>

class CPiControl {
public:
    CPiControl();
    ~CPiControl();
    void stop();
    void init_gpio(const std::vector<int> &input_pins, std::vector<int> &output_pins);
    void init_evdev_joystick();
    int js_has_new_event();
    void js_get_next_thing();
    std::vector<int> get_vals() { return _vals;};
private:
    std::vector<std::string> _event_codes = {
            "ls_x",
            "ls_y",
            "lt",
            "rs_x",
            "rs_y",
            "rt",
            "dpad_x",
            "dpad_y"
    };
    std::vector<int> _vals {
            0,
            0,
            0,
            0
    };
    std::string _device;
    struct libevdev *_evdev_dev = nullptr;
    struct input_event _evdev_dev_event = {};
    int _joystick_fd;
};

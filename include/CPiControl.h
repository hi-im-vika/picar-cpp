/**
 * CPiControl.h - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#pragma once

#define HEARTBEAT_PIN_BCM 17
#define STEERING_PIN_BCM 12
#define THROTTLE_PIN_BCM 13

#define DS4_LEFT_XAXIS_EVCODE       0
#define DS4_LEFT_YAXIS_EVCODE       1
#define DS4_LEFT_TRIGGER_EVCODE     2
#define DS4_RIGHT_XAXIS_EVCODE      3
#define DS4_RIGHT_YAXIS_EVCODE      4
#define DS4_RIGHT_TRIGGER_EVCODE    5
#define DS4_DPAD_XAXIS_EVCODE       16      // range -1 to 1
#define DS4_DPAD_YAXIS_EVCODE       17      // range -1 to 1

#define DS4_CROSS                   304
#define DS4_CIRCLE                  305
#define DS4_TRIANGLE                307
#define DS4_SQUARE                  308

#define DS4_SHOULDER_LEFT           310
#define DS4_SHOULDER_RIGHT          311
#define DS4_TRIGGER_LEFT            312
#define DS4_TRIGGER_RIGHT           313

#define DS4_SHARE                   314
#define DS4_OPTIONS                 315
#define DS4_HOME                    316
#define DS4_STICK_LEFT              317
#define DS4_STICK_RIGHT             318

#define VECT_LEFT_XAXIS             0
#define VECT_RIGHT_YAXIS            1
#define VECT_DPAD_XAXIS             2
#define VECT_DPAD_YAXIS             3

#include <iostream>
#include <vector>
#include <filesystem>
#include <pigpio.h>
#include <thread>

// Linux specific includes
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>

class CPiControl {
public:
    CPiControl() = default;
    ~CPiControl() = default;
    void stop();
    void init_gpio(const std::vector<int> &input_pins, std::vector<int> &output_pins);
    void init_evdev_joystick();
    void js_get_next_thing();
    std::vector<int> get_js_values() { return _vals;};
    std::string get_device_path() { return _device; };
private:
    std::vector<int> _vals {
            127,            // VECT_LEFT_XAXIS
            127,            // VECT_RIGHT_YAXIS
            0,              // VECT_DPAD_XAXIS
            0               // VECT_DPAD_YAXIS
    };
    std::string _device;
    struct libevdev *_evdev_dev = nullptr;
    struct input_event _evdev_dev_event = {};
    int _joystick_fd = 0;
};

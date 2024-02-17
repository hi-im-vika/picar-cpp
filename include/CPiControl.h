/**
 * CPiControl.h - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#pragma once

#define STEERING_PIN_BCM 12
#define THROTTLE_PIN_BCM 13

#include <iostream>
#include <vector>
#include <libevdev/libevdev.h>
#include <pigpio.h>

class CPiControl {
public:
    CPiControl();
    ~CPiControl();
    void stop();
    void init_gpio(const std::vector<int> &input_pins, std::vector<int> &output_pins);
    void init_evdev_joystick();
private:
    std::string _device;
};

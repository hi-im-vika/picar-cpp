/**
 * CPiControl.h - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#pragma once

#define STEERING_PIN_BCM 12
#define THROTTLE_PIN_BCM 11

#include <iostream>
#include <libevdev/libevdev.h>
#include <pigpio.h>

class CPiControl {
public:
    CPiControl();
    ~CPiControl();
private:
    std::string _device;
};

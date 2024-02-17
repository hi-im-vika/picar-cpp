/**
 * CPiControl.cpp - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/CPiControl.h"

CPiControl::CPiControl() {
    _device = "";
    gpioInitialise();
    gpioSetMode(STEERING_PIN_BCM, PI_OUTPUT);
    gpioSetMode(THROTTLE_PIN_BCM, PI_OUTPUT);
}

CPiControl::~CPiControl() {
    gpioTerminate();
}

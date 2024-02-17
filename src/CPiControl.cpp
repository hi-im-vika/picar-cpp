/**
 * CPiControl.cpp - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#include <vector>
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

void CPiControl::stop() {
    gpioTerminate();
}
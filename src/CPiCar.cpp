/**
 * CPiCar.cpp - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/CPiCar.h"

CPiCar::CPiCar() {
    _output_pins.push_back(STEERING_PIN_BCM);
    _output_pins.push_back(THROTTLE_PIN_BCM);
    _control.init_gpio(_input_pins, _output_pins);
}

CPiCar::~CPiCar() {
    _control.stop();
}

void CPiCar::draw() {
    std::cout << "draw" << std::endl;

    // DEBUG: cycles PWM between 1 ms to 2 ms duty cycle
    for (int duty = 0; duty < 100000; duty++) {
        gpioHardwarePWM(STEERING_PIN_BCM,100,100000 + duty);
        gpioHardwarePWM(THROTTLE_PIN_BCM,100,200000 - duty);
    }
    for (int duty = 0; duty < 100000; duty++) {
        gpioHardwarePWM(STEERING_PIN_BCM,100,200000 - duty);
        gpioHardwarePWM(THROTTLE_PIN_BCM,100,100000 + duty);
    }
}

void CPiCar::update() {
//    std::cout << "update" << std::endl;
}
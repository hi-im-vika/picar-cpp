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
    gpioHardwarePWM(STEERING_PIN_BCM,100,150000);
    gpioHardwarePWM(THROTTLE_PIN_BCM,100,150000);
//    gpioSetPWMrange(STEERING_PIN_BCM, 40000);
//    gpioSetPWMrange(THROTTLE_PIN_BCM,40000);
//    gpioSetPWMfrequency(STEERING_PIN_BCM,100);
//    gpioSetPWMfrequency(THROTTLE_PIN_BCM,100);
//    gpioPWM(STEERING_PIN_BCM,6000);
//    gpioPWM(THROTTLE_PIN_BCM,6000);
    gpioWrite(HEARTBEAT_PIN_BCM, PI_ON);
    _control.init_evdev_joystick();
}

CPiCar::~CPiCar() {
    _control.stop();
}

void CPiCar::draw() {
//    std::cout << "draw" << std::endl;
    _last_vals = _control.get_vals();
    if (_control.get_vals()[0] > 138 || _control.get_vals()[0] < 117) {
        gpioHardwarePWM(STEERING_PIN_BCM,100,200000 + (int) ((_control.get_vals()[0] / 255.0) * -100000));
    } else {
        gpioHardwarePWM(STEERING_PIN_BCM,100,200000 + (int) (0.5 * -100000));
    }
    if (_control.get_vals()[1] > 138 || _control.get_vals()[1] < 117) {
        gpioHardwarePWM(THROTTLE_PIN_BCM,100,200000 + (int) ((_control.get_vals()[1] / 255.0) * -100000));
    } else {
        gpioHardwarePWM(THROTTLE_PIN_BCM,100,200000 + (int) (0.5 * -100000));
    }

//    // DEBUG: (gpioPWM) cycles PWM between 1 ms to 2 ms duty cycle
//    for (int duty = 0; duty < 4000; duty++) {
////        gpioPWM(STEERING_PIN_BCM,4000 + duty);
//        _last_vals = _control.get_vals();
//        gpioPWM(STEERING_PIN_BCM,4000 + (int) ((_last_vals[0] / 255.0) * 4000));
//        gpioPWM(THROTTLE_PIN_BCM,8000 - duty);
//        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1));
//    }
//    for (int duty = 0; duty < 4000; duty++) {
////        gpioPWM(STEERING_PIN_BCM,8000 - duty);
//        _last_vals = _control.get_vals();
//        gpioPWM(STEERING_PIN_BCM,4000 + (int) ((_last_vals[0] / 255.0) * 4000));
//        gpioPWM(THROTTLE_PIN_BCM,4000 + duty);
//        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1));
//    }
}

void CPiCar::update() {
//    std::cout << "update" << std::endl;
    _control.js_get_next_thing();
}
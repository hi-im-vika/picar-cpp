/**
 * CPiCar.h - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#pragma once

#include "CPiCommonBase.h"

class CPiCar : public CPiCommonBase {
public:
    CPiCar();
    ~CPiCar();
    void draw() override;
    void update() override;
    void heartbeat();
    void joystick();
    static void joystick_thread(CPiCar *who_called_me);
private:
    std::vector<int> _last_vals = _control.get_vals();
    int _trim = 0;
    bool _dpax_prev = false;
    bool _dpay_prev = false;
    bool _do_heartbeat = true;
    bool _do_draw = false;
    bool _found_joystick = false;
    long long _last_time = 0;
    std::chrono::steady_clock::time_point _start;       ///< Start time to schedule interrupts
    long long _last_heartbeat = 0;
};

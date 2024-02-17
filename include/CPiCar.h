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
};

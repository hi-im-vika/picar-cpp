/**
 * main.cpp - new file
 * 2024-02-17
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/main.h"


int main() {
//    std::cout << "Hello, World!" << std::endl;
    auto cpc = CPiCar();
    cpc.run();
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(2000));
    cpc.stop();

    return 0;
}

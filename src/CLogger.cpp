/**
 * CLogger.cpp - new file
 * 2024-02-18
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/CLogger.h"


//CLogger *CLogger::get_instance() {
//    if (_clogger == nullptr) {
//        _clogger = new CLogger();
//    }
//    return _clogger;
//}

void CLogger::show_log(const std::string& source, const std::string& level, const std::string& content) {
    auto now = std::chrono::system_clock::now();
    std::cout << std::chrono::system_clock::to_time_t(now);
    std::cout << " [";
    std::cout << level;
    std::cout << "][";
    std::cout << source;
    std::cout << "] ";
    std::cout << content;
    std::cout << std::endl;
}
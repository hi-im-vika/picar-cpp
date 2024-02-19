/**
 * CLogger.h - new file
 * 2024-02-18
 * vika <https://github.com/hi-im-vika>
 */

#pragma once
#include <iostream>
#include <chrono>

/**
 * @brief   This is a class to make outputting logs easier.
 * @details This is intended to be a singleton beacuse only one object is required to show logs, will actually do later
 * @author  vika
 */
class CLogger {
public:
    CLogger() = default;
    ~CLogger() = default;
    void show_log(const std::string& source, const std::string& level, const std::string& content);
private:
//protected:
//    CLogger() = default;
//    CLogger *_clogger;
//public:
//    CLogger(CLogger &other) = delete;
//    void operator = (const CLogger &) = delete;
//    static CLogger *get_instance() {
//        if (_clogger
//    }
//    void show_log();
};

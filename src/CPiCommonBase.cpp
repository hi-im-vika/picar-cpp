/**
 * CPiCommonBase.cpp - inheritable class with common functions
 * 2024-02-08
 * vika <https://github.com/hi-im-vika>
 */

#include "../include/CPiCommonBase.h"

CPiCommonBase::CPiCommonBase() {
    std::thread thread_for_updating(update_thread, this);
    thread_for_updating.detach();
};

CPiCommonBase::~CPiCommonBase() = default;

void CPiCommonBase::run() {
    do {
        draw();
    } while (!_do_exit);
}

void CPiCommonBase::update_thread(CPiCommonBase *who_called_me) {
    while (!who_called_me->_do_exit) {
        who_called_me->update();
    }
}

void CPiCommonBase::stop() {
    _do_exit = true;
}

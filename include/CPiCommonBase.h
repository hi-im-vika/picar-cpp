/**
 * CPiCommonBase.h - inheritable class with common functions
 * 2024-02-08
 * vika <https://github.com/hi-im-vika>
 */

#pragma once

#include <opencv2/core.hpp>
#include <chrono>
#include <thread>
#include "CPiControl.h"

/**
 * @brief A class designed to be inherited from to provide functions common to all
 * @author vika
 */
class CPiCommonBase {
public:

    /**
     * Constructor for CPiCommonBase
     */
    CPiCommonBase();

    /**
     * Destructor for CPiCommonBase
     */
    ~CPiCommonBase();

    /**
     *
     */
    virtual void update() = 0;

    /**
     * @brief yeah i said draw but what i really mean is "draw" output onto servos
     */
    virtual void draw() = 0;

    /**
     *
     */
    void run();

    /**
     *
     */
    static void update_thread(CPiCommonBase *who_called_me);

    /**
     *
     */
    void stop();
//    static void draw_thread();

protected:
    CPiControl _control;    ///< Object for GPIO communication.
    std::string _port;      ///< Name of port to connect to.
    std::vector<int> _input_pins;
    std::vector<int> _output_pins;
    int _do_exit = 0;       ///< Flag to exit program.
};

cmake_minimum_required(VERSION 3.10)
project(picar-cpp)

# detect linux host
# https://stackoverflow.com/a/32259072
if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

# linux-specific compilation options
# cite source when found (stackoverflow)
if (LINUX)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(PkgConfig REQUIRED)
pkg_search_module(EVDEV REQUIRED libevdev)

set(OpenCV_STATIC ON)
find_package(OpenCV)

find_package(Boost REQUIRED)
find_library(PIGPIO_LIBS pigpio)

include_directories(${OpenCV_INCLUDE_DIRS} ${EVDEV_INCLUDE_DIRS})

add_definitions(-DWINDOW_NAME="${CMAKE_PROJECT_NAME}" -DBOOST_BIND_GLOBAL_PLACEHOLDERS)
add_executable(${CMAKE_PROJECT_NAME}
        src/main.cpp
        src/CPiControl.cpp
        include/CPiControl.h
        include/main.h
        src/CPiCommonBase.cpp
        src/CPiCar.cpp
        include/CPiCar.h
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Boost::headers ${OpenCV_LIBS} ${EVDEV_LIBRARIES} ${PIGPIO_LIBS})

# windows-specific compile options
if (WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ws2_32 "-static")
endif (WIN32)
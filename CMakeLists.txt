cmake_minimum_required(VERSION 3.5)

project(nokia7.1_stock_rom_flasher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_executable(nokia7.1_stock_rom_flasher src/main.cpp include/mainwindow.hpp src/mainwindow.cpp include/log.hpp src/log.cpp
    include/gtkmm_log.hpp src/gtkmm_log.cpp include/terminal_view.hpp src/terminal_view.cpp src/g_resources.cpp)
target_link_libraries(nokia7.1_stock_rom_flasher ${GTKMM_LIBRARIES})

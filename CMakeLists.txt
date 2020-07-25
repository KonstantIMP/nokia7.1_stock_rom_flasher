cmake_minimum_required(VERSION 3.5)

project(nokia7.1_stock_rom_flasher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_executable(nokia7.1_stock_rom_flasher src/main.cpp include/terminalview.hpp src/terminalview.cpp include/mainwindow.hpp src/mainwindow.cpp src/resources.cpp include/log.hpp src/log.cpp
    include/gtkmm_log.hpp src/gtkmm_log.cpp)
target_link_libraries(nokia7.1_stock_rom_flasher ${GTKMM_LIBRARIES})

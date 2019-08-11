cmake_minimum_required(VERSION 2.8)
project( qtrader )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui/include)

add_subdirectory(core)
add_subdirectory(gui)

add_executable(qtrader main.cpp)

target_link_libraries(qtrader Qt5::Widgets Qt5::Charts core gui)

install(TARGETS qtrader DESTINATION bin)

cmake_minimum_required(VERSION 2.8)
project( qtrader )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_executable(qtrader main.cpp)
target_link_libraries(qtrader Qt5::Widgets Qt5::Charts)
install(TARGETS qtrader DESTINATION bin)

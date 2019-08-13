cmake_minimum_required(VERSION 2.8)
project( qtrader )

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Charts Core Sql REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui/include)

add_subdirectory(core)
add_subdirectory(gui)

add_executable(qtrader main.cpp)

ADD_LIBRARY(mysql STATIC IMPORTED)
SET_TARGET_PROPERTIES(mysql PROPERTIES IMPORTED_LOCATION /usr/local/mysql/lib/libmysqlclient.a)


target_link_libraries(qtrader Qt5::Widgets Qt5::Charts Qt5::Sql core gui mysql)
link_directories(/usr/local/mysql/lib)

install(TARGETS qtrader DESTINATION bin)

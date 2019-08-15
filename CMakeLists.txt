# minimum version
cmake_minimum_required(VERSION 2.8)

# project name
project( qtrader )

# disable automatic stuff
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

# tell cmake to include the current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt5 required modules
find_package(Qt5 COMPONENTS Widgets Charts Core Sql REQUIRED)

# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui/include)

# tell cmake to search for more CMakeLists.txt files in these folders
add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(test)

# main executable
add_executable(qtrader main.cpp)

# add system library
ADD_LIBRARY(mysql STATIC IMPORTED)
SET_TARGET_PROPERTIES(mysql PROPERTIES IMPORTED_LOCATION /usr/local/mysql/lib/libmysqlclient.a)

# tell cmake to include these libraries in the linking
target_link_libraries(qtrader Qt5::Widgets Qt5::Charts Qt5::Sql core gui mysql)
#link_directories(/usr/local/mysql/lib)

install(TARGETS qtrader DESTINATION bin)

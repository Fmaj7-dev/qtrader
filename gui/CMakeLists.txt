include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_library(gui src/serieplot.cpp )

qt5_use_modules(gui Charts)

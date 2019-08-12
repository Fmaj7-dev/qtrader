include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

set( GUI_SOURCES
src/serieplot.cpp 
src/configtree.cpp
src/treemodel.cpp
src/treeitem.cpp
)

set( GUI_MOCS
include/configtree.h
include/treemodel.h
)

qt5_wrap_cpp( GUI_MOC_SOURCES ${GUI_MOCS} )

set(GUI_SOURCES ${GUI_SOURCES} ${GUI_MOC_SOURCES})

add_library(gui 
${GUI_SOURCES}
)

qt5_use_modules(gui Charts)

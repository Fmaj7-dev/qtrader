# tell cmake to include this
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# source files
set( GUI_SOURCES
    src/serieplot.cpp 
    src/configtree.cpp
    src/treemodel.cpp
    src/treeitem.cpp
)

# files needed to moc
set( GUI_MOCS
    include/configtree.h
    include/treemodel.h
)

# mc header files
qt5_wrap_cpp( GUI_MOC_SOURCES ${GUI_MOCS} )

# add moced files to sources
set(GUI_SOURCES ${GUI_SOURCES} ${GUI_MOC_SOURCES})

# we are making a library
add_library(gui 
    ${GUI_SOURCES}
)

qt5_use_modules(gui Charts)

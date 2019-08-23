# tell cmake to include this
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# source files
set( GUI_SOURCES
    src/seriesplot.cpp 
    src/configtree.cpp
    src/treemodel.cpp
    src/treeitem.cpp
    src/plotcontroller.cpp
)

# files needed to moc
set( GUI_MOCS
    include/configtree.h
    include/treemodel.h
    include/plotcontroller.h
    include/treeview.h
)

set( UI_FILES
    ui/smaconfig.ui 
)

# mc header files
qt5_wrap_cpp( GUI_MOC_SOURCES ${GUI_MOCS} )

qt5_wrap_ui( UI_SOURCES ${UI_FILES})

# add moced files to sources
set(GUI_SOURCES ${GUI_SOURCES} ${GUI_MOC_SOURCES} ${UI_SOURCES})

# we are making a library
add_library(gui 
    ${GUI_SOURCES}
)

qt5_use_modules(gui Charts Sql)

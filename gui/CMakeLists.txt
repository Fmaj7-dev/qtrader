# tell cmake to include this
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/simulation)

# source files
set( GUI_SOURCES
    src/plotting/seriesplot.cpp 
    src/plotting/configtree.cpp
    src/plotting/treemodel.cpp
    src/plotting/treeitem.cpp
    src/plotting/plotcontroller.cpp
    src/plotting/plottingwidget.cpp
    src/simulation/simulationwidget.cpp
    src/simulation/scatterchart.cpp
)

# files needed to moc
set( GUI_MOCS
    include/plotting/configtree.h
    include/plotting/treemodel.h
    include/plotting/plotcontroller.h
    include/plotting/treeview.h
    include/plotting/plottingwidget.h
    include/simulation/simulationwidget.h
    include/simulation/scatterchart.h
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

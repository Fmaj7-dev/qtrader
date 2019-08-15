# tell cmake to include this
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# source files
set (CORE_SOURCES
    src/liveseries.cpp 
    src/seriesrepository.cpp
    src/sqldataprovider.cpp
)

# we are making a library
add_library(core ${CORE_SOURCES})

qt5_use_modules(core Sql )

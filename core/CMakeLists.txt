include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set (CORE_SOURCES
src/serie.cpp 
src/seriesrepository.cpp
src/sqldataprovider.cpp
)

add_library(core ${CORE_SOURCES})

qt5_use_modules(core Sql )
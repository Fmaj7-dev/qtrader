
add_executable( check 
                testDB.cpp
                testSimulation.cpp )
target_link_libraries(check core gui)
install(TARGETS check DESTINATION bin)

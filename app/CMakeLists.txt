# add the executable
add_executable(louis louis_work.cxx)
target_include_directories(louis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(louis game)

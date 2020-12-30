
add_library(sirensound sirensound.cpp sirensound.h)
target_include_directories(sirensound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sirensound PRIVATE component service)

add_library(soundcomponents INTERFACE)
target_link_libraries(soundcomponents INTERFACE sirensound)

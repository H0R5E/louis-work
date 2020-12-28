
add_library(sldraw singleletterdraw.cpp singleletterdraw.h)
target_include_directories(sldraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sldraw PRIVATE command component game)

add_library(drawcomponents INTERFACE)
target_link_libraries(drawcomponents INTERFACE sldraw)

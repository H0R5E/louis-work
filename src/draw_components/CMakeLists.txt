
add_library(louisdraw louisdraw.cpp louisdraw.h)
target_include_directories(louisdraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(louisdraw PRIVATE component service)

add_library(sldraw singleletterdraw.cpp singleletterdraw.h)
target_include_directories(sldraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sldraw PRIVATE component service)

add_library(twdraw typewriterdraw.cpp typewriterdraw.h)
target_include_directories(twdraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(twdraw PRIVATE component service)

add_library(drawcomponents INTERFACE)
target_link_libraries(drawcomponents INTERFACE louisdraw sldraw twdraw)

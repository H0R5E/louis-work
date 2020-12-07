
add_library(windowstate INTERFACE)
target_sources(windowstate INTERFACE windowstate.h)
target_include_directories(windowstate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(windowstate INTERFACE ${CONAN_LIBS})

add_library(startstate startstate.cpp startstate.h)
target_include_directories(startstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(startstate windowstate ${CONAN_LIBS})

add_library(states INTERFACE)
target_link_libraries(states INTERFACE windowstate startstate)

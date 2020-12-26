
add_library(state INTERFACE)
target_sources(state INTERFACE state.h)
target_include_directories(state INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(command INTERFACE)
target_sources(command INTERFACE command.h)
target_include_directories(command INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(resource INTERFACE)
target_sources(resource INTERFACE resourceholder.h)
target_include_directories(resource INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(window INTERFACE)
target_sources(resource INTERFACE window.h)
target_include_directories(window INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(helpers helpers.cpp helpers.h)
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(helpers PRIVATE ${CONAN_LIBS})

add_library(game game.cpp game.h)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game command state gamestates window ${CONAN_LIBS})

add_subdirectory(states)
add_subdirectory(commands)

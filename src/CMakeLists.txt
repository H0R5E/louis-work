
add_library(component INTERFACE)
target_sources(component INTERFACE component.h)
target_include_directories(component INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(component INTERFACE service sound ${CONAN_LIBS})

add_library(resource INTERFACE)
target_sources(resource INTERFACE resourceholder.h)
target_include_directories(resource INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(resource INTERFACE helpers)

add_library(service INTERFACE)
target_sources(service INTERFACE service.h)
target_include_directories(service INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(service INTERFACE sound window ${CONAN_LIBS})

add_library(state INTERFACE)
target_sources(state INTERFACE state.h)
target_include_directories(state INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(state INTERFACE ${CONAN_LIBS})

add_library(command command.cpp command.h)
target_include_directories(command PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(command PRIVATE component service ${CONAN_LIBS})

add_library(helpers helpers.cpp helpers.h)
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(helpers PRIVATE ${CONAN_LIBS})

add_library(factory factory.cpp factory.h)
target_include_directories(factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(factory PRIVATE command
                                      drawcomponents
                                      soundcomponents)

add_library(stateholder stateholder.cpp stateholder.h)
target_include_directories(stateholder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(stateholder PUBLIC gamestates PRIVATE state)

add_library(game game.cpp game.h)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game command
                           factory
                           resource
                           service
                           sound
                           state
                           stateholder
                           window
                           ${CONAN_LIBS})

add_subdirectory(adapters)
add_subdirectory(draw_components)
add_subdirectory(sound_components)
add_subdirectory(states)

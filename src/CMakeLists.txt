
add_library(helpers helpers.cpp helpers.h)
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(helpers ${CONAN_LIBS})

add_library(gamestate INTERFACE)
target_sources(gamestate INTERFACE gamestate.h)
target_include_directories(gamestate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(startstate startstate.cpp startstate.h)
target_include_directories(startstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(startstate gamestate helpers ${CONAN_LIBS})

add_library(playstate playstate.cpp playstate.h)
target_include_directories(playstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(playstate gamestate ${CONAN_LIBS})

add_library(game game.cpp game.h)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game startstate playstate ${CONAN_LIBS})

add_library(states INTERFACE)
target_link_libraries(states INTERFACE game gamestate)


add_library(helpers helpers.cpp helpers.h)
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(helpers ${CONAN_LIBS})

add_library(command INTERFACE)
target_sources(command INTERFACE command.h)
target_include_directories(command INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(slc singlelettercommand.cpp singlelettercommand.h)
target_include_directories(slc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(slc command helpers ${CONAN_LIBS})

add_library(gamestate INTERFACE)
target_sources(gamestate INTERFACE gamestate.h)
target_include_directories(gamestate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(startstate startstate.cpp startstate.h)
target_include_directories(startstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(startstate gamestate helpers ${CONAN_LIBS})

add_library(playstate playstate.cpp playstate.h)
target_include_directories(playstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(playstate gamestate helpers slc ${CONAN_LIBS})

add_library(drawstate drawstate.cpp drawstate.h)
target_include_directories(drawstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(drawstate gamestate helpers ${CONAN_LIBS})

add_library(waitstate waitstate.cpp waitstate.h)
target_include_directories(waitstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(waitstate gamestate helpers ${CONAN_LIBS})

add_library(game game.cpp game.h)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game startstate playstate drawstate waitstate ${CONAN_LIBS})

add_library(states INTERFACE)
target_link_libraries(states INTERFACE game gamestate)


add_library(startstate startstate.cpp startstate.h)
target_include_directories(startstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(startstate helpers game)

add_library(playstate playstate.cpp playstate.h)
target_include_directories(playstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(playstate helpers game gamecommands)

add_library(drawstate drawstate.cpp drawstate.h)
target_include_directories(drawstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(drawstate helpers game)

add_library(waitstate waitstate.cpp waitstate.h)
target_include_directories(waitstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(waitstate helpers game)

add_library(gamestates INTERFACE)
target_link_libraries(gamestates INTERFACE startstate
                                           playstate
                                           drawstate
                                           waitstate)

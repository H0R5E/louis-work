
#add_library(sirensound sirensound.cpp sirensound.h)
#target_include_directories(sirensound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(sirensound component service)

add_library(lettersound lettersound.cpp lettersound.h)
target_include_directories(lettersound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lettersound component service voice)

add_library(soundcomponents INTERFACE)
target_link_libraries(soundcomponents INTERFACE lettersound)

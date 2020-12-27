
add_library(slc singlelettercommand.cpp singlelettercommand.h)
target_include_directories(slc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(slc PRIVATE command game ${CONAN_LIBS})

add_library(gamecommands INTERFACE)
target_link_libraries(gamecommands INTERFACE slc)

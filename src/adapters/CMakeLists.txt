add_library(sound INTERFACE)
target_sources(sound INTERFACE sound.h)
target_include_directories(sound INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sound INTERFACE polymorphic_value ${CONAN_LIBS})

add_library(window INTERFACE)
target_sources(window INTERFACE window.h)
target_include_directories(window INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(window INTERFACE ${CONAN_LIBS})

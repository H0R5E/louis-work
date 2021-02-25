# add the executable
add_executable(louis louis_work.cxx)
target_link_libraries(louis
                      drawcomponents
                      game
                      polymorphic_value
                      sound
                      soundcomponents
                      window)

if (UNIX)
    install(TARGETS louis DESTINATION bin)
    SET(LOUIS_INSTALL_PATH
        "${CMAKE_INSTALL_PREFIX}/bin/$<TARGET_FILE_NAME:louis>"
        PARENT_SCOPE)
endif ()

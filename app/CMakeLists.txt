# add the executable
add_executable(louis louis_work.cxx)
target_link_libraries(louis
                      drawcomponents
                      game
                      polymorphic_value
                      sound
                      soundcomponents
                      window)

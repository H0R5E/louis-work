
#   louis-work: a game
#   Copyright (C) 2021  Mathew Topper
# 
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
# 
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
# 
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

# add the executable
add_executable(louis louis_work.cxx)
target_link_libraries(louis
                      drawcomponents
                      game
                      logging
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


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

add_library(sirensound sirensound.cpp sirensound.h)
target_include_directories(sirensound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sirensound component service)

add_library(specialsound specialsound.cpp specialsound.h)
target_include_directories(specialsound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(specialsound PUBLIC component service PRIVATE voice)

add_library(lettersound lettersound.cpp lettersound.h)
target_include_directories(lettersound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lettersound PUBLIC component service PRIVATE voice)

add_library(soundcomponents INTERFACE)
target_link_libraries(soundcomponents INTERFACE sirensound
                                                specialsound
                                                lettersound)

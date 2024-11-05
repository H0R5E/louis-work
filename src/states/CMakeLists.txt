
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

add_library(startstate startstate.cpp startstate.h)
target_include_directories(startstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(startstate PRIVATE service
                                         scene
                                         stateholder)

add_library(playstate playstate.cpp playstate.h)
target_include_directories(playstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(playstate PRIVATE service scene stateholder)

add_library(drawstate drawstate.cpp drawstate.h)
target_include_directories(drawstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(drawstate PRIVATE service scene stateholder)

add_library(waitstate waitstate.cpp waitstate.h)
target_include_directories(waitstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(waitstate PRIVATE service scene stateholder)

add_library(restartstate restartstate.cpp restartstate.h)
target_include_directories(restartstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(restartstate PRIVATE service
                                           scene
                                           stateholder)

add_library(specialstate specialstate.cpp specialstate.h)
target_include_directories(specialstate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(specialstate PRIVATE service
                                           scene
                                           stateholder)

add_library(gamestates INTERFACE)
target_link_libraries(gamestates INTERFACE startstate
                                           playstate
                                           drawstate
                                           waitstate
                                           restartstate
                                           specialstate)

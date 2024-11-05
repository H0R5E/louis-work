
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

add_library(sldraw singleletterdraw.cpp singleletterdraw.h)
target_include_directories(sldraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sldraw PRIVATE component service spdlog::spdlog)

add_library(specialdraw specialdraw.cpp specialdraw.h)
target_include_directories(specialdraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(specialdraw PRIVATE component service spdlog::spdlog)

add_library(twdraw typewriterdraw.cpp typewriterdraw.h)
target_include_directories(twdraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(twdraw PRIVATE component service spdlog::spdlog)

add_library(drawcomponents INTERFACE)
target_link_libraries(drawcomponents INTERFACE sldraw specialdraw twdraw)

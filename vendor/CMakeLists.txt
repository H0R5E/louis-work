
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

# external projects
include(ExternalProject)
include(FetchContent)

# check for autoconf on linux
if (CMAKE_COMPILER_IS_GNUCXX)
    find_program(AUTOCONF autoconf
                 REQUIRED)
endif()

# espeak
SET(ESPEAKNG_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/espeak-ng)
option(ESPEAKNG_BUILD "Build espeak-ng" ON)

if (ESPEAKNG_BUILD)
    
    # prep
    if (WIN32)
        message (FATAL_ERROR "Windows not yet supported")
    else()
        ExternalProject_Add(espeak-ng
        GIT_REPOSITORY "git://github.com/espeak-ng/espeak-ng"
        GIT_TAG "master"
        CONFIGURE_COMMAND ./autogen.sh
        COMMAND ./configure --prefix=${ESPEAKNG_PREFIX}
        PREFIX ${ESPEAKNG_PREFIX}
        BUILD_COMMAND make
        BUILD_IN_SOURCE 1
        BUILD_BYPRODUCTS ${ESPEAKNG_PREFIX}/lib/libespeak-ng.so
        INSTALL_COMMAND make LIBDIR=${ESPEAKNG_PREFIX}/lib install)
    endif()
    
    # trigger build
    add_dependencies(voice espeak-ng)
    
endif()

# link and include
add_library(libespeak-ng INTERFACE)
target_link_libraries(libespeak-ng INTERFACE
                      ${ESPEAKNG_PREFIX}/lib/libespeak-ng.so)
target_include_directories(libespeak-ng INTERFACE
                           ${ESPEAKNG_PREFIX}/include/espeak-ng)

# install
if (INSTALL3RDPARTY)
    if (UNIX)
        set(espeak_libs
            "${ESPEAKNG_PREFIX}/lib/libespeak-ng.so"
            "${ESPEAKNG_PREFIX}/lib/libespeak-ng.so.1"
            "${ESPEAKNG_PREFIX}/lib/libespeak-ng.so.1.1.51"
        )
    endif ()
    message(STATUS "espeak libs: ${espeak_libs}")
    install(FILES ${espeak_libs} DESTINATION ${INTALL3RDPARTY_PATH})
endif()

# polymorphic_value
FetchContent_Declare(polymorphic_value
    GIT_REPOSITORY "git://github.com/jbcoe/polymorphic_value"
    GIT_TAG "master")

FetchContent_MakeAvailable(polymorphic_value)
target_include_directories(polymorphic_value INTERFACE
                           ${polymorphic_value_SOURCE_DIR})

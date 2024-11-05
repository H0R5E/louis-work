
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
SET(VENDOR_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
option(ESPEAKNG_BUILD "Build espeak-ng" OFF)

if (ESPEAKNG_BUILD)
    
    add_library(libespeak-ng INTERFACE)
    
    if (WIN32)
        ExternalProject_Add(
            libespeak-ng-win
            DOWNLOAD_COMMAND git clone "https://github.com/espeak-ng/espeak-ng" ${VENDOR_PREFIX}/espeak-ng
                COMMAND git clone "https://github.com/espeak-ng/pcaudiolib" ${VENDOR_PREFIX}/espeak-ng/src/pcaudiolib
            CONFIGURE_COMMAND ""
            BUILD_COMMAND msbuild ${VENDOR_PREFIX}/espeak-ng/src/windows/libespeak-ng.vcxproj /p:PlatformToolset=v142 /p:Platform=x64 /p:Configuration=Release
            BUILD_BYPRODUCTS ${VENDOR_PREFIX}/src/windows/x64/Release/libespeak-ng.dll
            INSTALL_COMMAND ""
            BUILD_IN_SOURCE 1
        )
        target_link_libraries(libespeak-ng INTERFACE
                              ${VENDOR_PREFIX}/src/windows/x64/Release/libespeak-ng.dll)
        add_dependencies(voice libespeak-ng-win)
    else()
        ExternalProject_Add(
            libespeak-ng-nix
            GIT_REPOSITORY "https://github.com/espeak-ng/espeak-ng"
            GIT_TAG "master"
            PREFIX ${VENDOR_PREFIX}
            CONFIGURE_COMMAND ./autogen.sh
            COMMAND ./configure --prefix=${VENDOR_PREFIX}
            BUILD_COMMAND make
            BUILD_IN_SOURCE 1
            BUILD_BYPRODUCTS ${VENDOR_PREFIX}/lib/libespeak-ng.so
            INSTALL_COMMAND make LIBDIR=${VENDOR_PREFIX}/lib install
        )
        target_link_libraries(libespeak-ng INTERFACE
                              ${VENDOR_PREFIX}/lib/libespeak-ng.so)
        add_dependencies(voice espeak-ng-nix)
    endif()
    
endif()

# link and include
target_include_directories(libespeak-ng INTERFACE
                           ${VENDOR_PREFIX}/include/espeak-ng)

# install
if (INSTALL3RDPARTY)
    if (UNIX)
        set(espeak_libs
            "${VENDOR_PREFIX}/lib/libespeak-ng.so"
            "${VENDOR_PREFIX}/lib/libespeak-ng.so.1"
            "${VENDOR_PREFIX}/lib/libespeak-ng.so.1.1.51"
        )
    endif ()
    message(STATUS "espeak libs: ${espeak_libs}")
    install(FILES ${espeak_libs} DESTINATION ${INTALL3RDPARTY_PATH})
endif()

# polymorphic_value
FetchContent_Declare(polymorphic_value
    GIT_REPOSITORY "https://github.com/jbcoe/polymorphic_value"
    GIT_TAG "main")

FetchContent_MakeAvailable(polymorphic_value)
target_include_directories(polymorphic_value INTERFACE
                           ${polymorphic_value_SOURCE_DIR})

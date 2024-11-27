
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

if (ESPEAKNG_BUILD)
    
    add_library(libespeak-ng SHARED IMPORTED GLOBAL)
    
    if (WIN32)
        ExternalProject_Add(
            libespeak-ng-win
            DOWNLOAD_COMMAND ${CMAKE_COMMAND} -E rm -rf ${VENDOR_PREFIX}/src/espeak-ng
                COMMAND git clone "https://github.com/espeak-ng/espeak-ng" ${VENDOR_PREFIX}/src/espeak-ng
                COMMAND git clone "https://github.com/espeak-ng/pcaudiolib" ${VENDOR_PREFIX}/src/espeak-ng/src/pcaudiolib
            CONFIGURE_COMMAND ""
            BUILD_COMMAND msbuild ${VENDOR_PREFIX}/src/espeak-ng/src/windows/libespeak-ng.vcxproj /p:PlatformToolset=v142 /p:Platform=x64 /p:Configuration=Release
                COMMAND msbuild ${VENDOR_PREFIX}/src/espeak-ng/src/windows/espeak-ng.vcxproj /p:PlatformToolset=v142 /p:Platform=x64 /p:Configuration=Release
                COMMAND msbuild ${VENDOR_PREFIX}/src/espeak-ng/src/windows/data.vcxproj /p:PlatformToolset=v142 /p:Platform=x64 /p:Configuration=Release
            INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${VENDOR_PREFIX}/src/espeak-ng/src/windows/x64/Release/libespeak-ng.dll ${CMAKE_SOURCE_DIR}/bin/libespeak-ng.dll
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${VENDOR_PREFIX}/src/espeak-ng/src/include ${VENDOR_PREFIX}/include
            BUILD_BYPRODUCTS ${VENDOR_PREFIX}/src/espeak-ng/src/windows/x64/Release/libespeak-ng.dll
                             ${VENDOR_PREFIX}/src/espeak-ng/src/windows/x64/Release/libespeak-ng.lib
                             ${CMAKE_SOURCE_DIR}/bin/libespeak-ng.dll
            BUILD_IN_SOURCE 1
        )
        add_dependencies(libespeak-ng libespeak-ng-win)
        
        set_property(TARGET libespeak-ng PROPERTY
                     IMPORTED_LOCATION ${VENDOR_PREFIX}/src/espeak-ng/src/windows/x64/Release/libespeak-ng.dll)
        set_property(TARGET libespeak-ng PROPERTY
                     IMPORTED_IMPLIB ${VENDOR_PREFIX}/src/espeak-ng/src/windows/x64/Release/libespeak-ng.lib)
        
        install(DIRECTORY ${VENDOR_PREFIX}/src/espeak-ng/espeak-ng-data DESTINATION vendor)
    else(UNIX)
        ExternalProject_Add(
            libespeak-ng-nix
            GIT_REPOSITORY "https://github.com/espeak-ng/espeak-ng"
            GIT_TAG "master"
            PREFIX ${VENDOR_PREFIX}
            CONFIGURE_COMMAND ./autogen.sh
	    COMMAND CC=clang CXX=clang ./configure --prefix=${VENDOR_PREFIX} --with-speechplayer=no --with-sonic=no
            BUILD_COMMAND make
            BUILD_IN_SOURCE 1
            BUILD_BYPRODUCTS ${VENDOR_PREFIX}/lib/libespeak-ng.so
            INSTALL_COMMAND make install
        )
        add_dependencies(libespeak-ng libespeak-ng-nix)
        set_property(TARGET libespeak-ng PROPERTY
                     IMPORTED_LOCATION ${VENDOR_PREFIX}/lib/libespeak-ng.so)
    endif()
    
    # include
    file (MAKE_DIRECTORY ${VENDOR_PREFIX}/include/espeak-ng)
    target_include_directories(libespeak-ng INTERFACE ${VENDOR_PREFIX}/include/espeak-ng)
    
endif()

# polymorphic_value
FetchContent_Declare(polymorphic_value
    GIT_REPOSITORY "https://github.com/jbcoe/polymorphic_value"
    GIT_TAG "main")

FetchContent_MakeAvailable(polymorphic_value)
target_include_directories(polymorphic_value INTERFACE
                           ${polymorphic_value_SOURCE_DIR})

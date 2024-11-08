
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

# disallow macos for now
if (APPLE)
    message( FATAL_ERROR "MacOS is not yet supported" )
endif()

cmake_minimum_required(VERSION 3.27)

# set the project name and version
project("Louis Work" VERSION 0.0.1
                     DESCRIPTION "A game about words and letters")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# options
option(ESPEAKNG_BUILD "Build espeak-ng" ON)
option(GCOV "Check code coverage" ON)
option(RPM "Create an RPM package" OFF)
option(INNO "Create a inno setup package" OFF)

# conan
find_package(argparse REQUIRED)
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)
find_package(platform_folders REQUIRED)
find_package(SFML REQUIRED)
find_package(spdlog REQUIRED)

# vscode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# testing
include(GoogleTest)
enable_testing()

# code coverage
find_program(GCOVR_PATH gcovr)

# install settings
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)

# debug compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

# boost_stacktrace
if (UNIX)
    add_definitions(-DBOOST_STACKTRACE_USE_ADDR2LINE)
endif ()

# build output structure
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# define asset and log path in pathconfig.h
set(ASSETS_DIR_TEST ${CMAKE_SOURCE_DIR})
set(LOGS_DIR_TEST ${CMAKE_SOURCE_DIR}/logs)

if (WIN32)
    set(ASSETS_DIR_RELEASE .)
    set(LOGS_DIR_RELEASE "Louis Work")
elseif (UNIX)
    set(ASSETS_DIR_RELEASE /usr/share/louis-work)
    set(LOGS_DIR_RELEASE louis-work)
endif ()

configure_file(${CMAKE_SOURCE_DIR}/src/pathconfig.h.in
               ${CMAKE_SOURCE_DIR}/src/pathconfig.h)

# coverage target and compiler flags
if (CMAKE_COMPILER_IS_GNUCXX AND GCOVR_PATH AND GCOV)
    
    include(CodeCoverage)
    
    append_coverage_compiler_flags()
    set(TEST_COMPILER_FLAGS
        "-O0 -fno-default-inline -fno-inline -fno-elide-constructors -save-temps")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${TEST_COMPILER_FLAGS}")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${TEST_COMPILER_FLAGS}")
     
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE tests
        DEPENDENCIES tests
        EXCLUDE "${CMAKE_SOURCE_DIR}/app/*"
                "${CMAKE_SOURCE_DIR}/build/_deps/*"
                "${CMAKE_SOURCE_DIR}/src/adapters/*"
                "${CMAKE_SOURCE_DIR}/test/*")
    
    add_dependencies(coverage tests)
    
    file(GLOB_RECURSE GCOV_FILES CONFIGURE_DEPENDS ${PROJECT_BINARY_DIR}
            *.gcda *.gcno)
    
    add_custom_target(coverage-clean
        COMMAND rm -f ${GCOV_FILES};
        COMMAND ${CMAKE_MAKE_PROGRAM} clean WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR};
        COMMENT "Removing build and gcov files."
    )
    
endif ()

# RPATH handling

if (UNIX)

    # use, i.e. don't skip the full RPATH for the build tree
    set(CMAKE_SKIP_BUILD_RPATH FALSE)

    # when building, don't use the install RPATH already
    # (but later on when installing)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

endif ()

# path to source code
add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(vendor)

# discover test files
file(GLOB test_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/test/*.cpp"
                                     "${CMAKE_SOURCE_DIR}/test/*.h")

# add tests
add_executable(tests ${test_SRC})
#add_executable(tests "${CMAKE_SOURCE_DIR}/test/game_test.cpp" 
#                     "${CMAKE_SOURCE_DIR}/test/mock.h")
target_link_libraries(tests
                      game
                      drawcomponents
                      soundcomponents
                      gtest::gtest)

gtest_discover_tests(tests)

# extra install commands

# Install libs
install(FILES $<TARGET_RUNTIME_DLLS:louis> TYPE BIN)

# Install assets
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${ASSETS_DIR_RELEASE})

# Install desktop entry
if (UNIX)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/data/louis.desktop.in
        ${CMAKE_CURRENT_BINARY_DIR}/louis.desktop)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/louis.desktop
                  DESTINATION share/applications/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/l-key.svg
                  DESTINATION share/icons/hicolor/scalable/apps/)
    SET(DESKTOP_INSTALL_PATH
        "${CMAKE_INSTALL_PREFIX}/share/applications/louis.desktop")
    SET(ICON_INSTALL_PATH
        "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps/l-key.svg")
endif()

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)
endif()

if (RPM OR INNO)
    
    # General CPack variables
    SET(CPACK_VERBATIM_VARIABLES TRUE)
    set(CPACK_PACKAGE_DESCRIPTION "\
    A C++ project to create a game for my son to do his work on my computer")
    set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/packages")
    set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)
    
    # RPM
    if (RPM AND UNIX)
        set(CPACK_PACKAGE_NAME "louis")
        set(CPACK_GENERATOR "RPM")
        set(CPACK_RPM_PACKAGE_RELEASE 1)
    endif ()
    
    if (INNO AND WIN32)
        set(CPACK_PACKAGE_NAME "Louis Work")
        set(CPACK_GENERATOR "INNOSETUP")
        # set(CPACK_BINARY_INNOSETUP "ON")
        # set(CPACK_BINARY_NSIS "OFF")
        set(CPACK_INNOSETUP_EXTRA_SCRIPTS ${CMAKE_SOURCE_DIR}/cmake/icons.iss)
    endif ()
    
    include(CPack)

endif()

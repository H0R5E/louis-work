cmake_minimum_required(VERSION 3.13)

# set the project name and version
project("Louis' Work" VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# testing
include(GoogleTest)
enable_testing()

# code coverage
find_program(GCOVR_PATH gcovr)
option(GCOV "Check code coverage" OFF)

# install options
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)
option(INSTALL3RDPARTY "Install 3rd party libraries" ON)

if (WIN32)
    SET(INTALL3RDPARTY_PATH "bin")
else ()
    SET(INTALL3RDPARTY_PATH "lib")
endif ()

# debug compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

# build output structure
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# define asset path in pathconfig.h
set(ASSETS_DIR_TEST ${CMAKE_SOURCE_DIR}/assets)

if (WIN32)
    set(ASSETS_DIR_RELEASE "C:/ProgramData/louis")
elseif (UNIX)
    set(ASSETS_DIR_RELEASE "/usr/share/louis")
else ()
    message (FATAL_ERROR "Unknown OS")
endif ()

configure_file(${CMAKE_SOURCE_DIR}/src/pathconfig.h.in
               ${CMAKE_SOURCE_DIR}/src/pathconfig.h)

# coverage target and compiler flags
if (CMAKE_COMPILER_IS_GNUCXX AND GCOVR_PATH AND GCOV)
    
    include(CodeCoverage)
    
    append_coverage_compiler_flags()
    set(TEST_COMPILER_FLAGS "-O0 -fno-default-inline -fno-inline -fno-elide-constructors -save-temps")
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
                      ${CONAN_LIBS})

gtest_discover_tests(tests)

# extra install commands

# Install SFML
if (INSTALL3RDPARTY)
    if (UNIX)
        FILE(GLOB sfml_libs "${CMAKE_BINARY_DIR}/lib/*.so.*")
    endif ()
    message(STATUS "SFML libs: ${sfml_libs}")
    install(FILES ${sfml_libs} DESTINATION ${INTALL3RDPARTY_PATH})
endif ()

# Install assets
install(DIRECTORY ${ASSETS_DIR_TEST} DESTINATION ${ASSETS_DIR_RELEASE})

# Install desktop entry
if (UNIX AND NOT APPLE)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/data/louis.desktop.in
        ${CMAKE_CURRENT_BINARY_DIR}/louis.desktop)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/louis.desktop
                  DESTINATION share/applications/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/l-key.svg
                  DESTINATION share/icons/hicolor/scalable/apps/)
endif()

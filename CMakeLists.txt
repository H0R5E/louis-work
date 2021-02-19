cmake_minimum_required(VERSION 3.13)

# set the project name and version
project("Louis' Work" VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# testing
include(GoogleTest)
enable_testing()

# code coverage
include(CodeCoverage)
find_program(GCOVR_PATH gcovr)
set(GCOV TRUE)

# output structure
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# define asset path
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
configure_file(${CMAKE_SOURCE_DIR}/src/pathconfig.h.in
               ${CMAKE_SOURCE_DIR}/src/pathconfig.h)

# release compiler flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# coverage target and compiler flags
if (CMAKE_COMPILER_IS_GNUCXX AND GCOVR_PATH AND GCOV)
    
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
target_link_libraries(tests game drawcomponents soundcomponents ${CONAN_LIBS})
gtest_discover_tests(tests)

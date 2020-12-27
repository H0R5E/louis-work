cmake_minimum_required(VERSION 3.13)

# set the project name and version
project("Louis' Work" VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# testing
include(GoogleTest)
enable_testing()

# conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

# output structure
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# define asset path
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
configure_file(${CMAKE_SOURCE_DIR}/src/pathconfig.h.in
               ${CMAKE_SOURCE_DIR}/src/pathconfig.h)

# compiler flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# path to source code
add_subdirectory(app)
add_subdirectory(src)

# discover test files
file(GLOB test_SRC CONFIGURE_DEPENDS "test/*.cpp" "test/*.h")

# add tests
#add_executable(tests ${test_SRC})
#target_link_libraries(tests game ${CONAN_LIBS})
#gtest_discover_tests(tests)


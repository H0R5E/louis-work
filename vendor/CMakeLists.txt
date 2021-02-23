
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
SET(ESPEAKNG_BUILD TRUE)

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
        BUILD_BYPRODUCTS ${ESPEAKNG_PREFIX}/lib/libespeak-ng.so)
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
if (UNIX)
    set(espeak_libs
        "${ESPEAKNG_PREFIX}/lib/libespeak-ng.so"
        "${ESPEAKNG_PREFIX}/lib/libespeak-ng.so.1"
    )
    message(STATUS "espeak libs: ${espeak_libs}")
    install(FILES ${espeak_libs} DESTINATION lib)
endif ()

# polymorphic_value
FetchContent_Declare(polymorphic_value
    GIT_REPOSITORY "git://github.com/jbcoe/polymorphic_value"
    GIT_TAG "master")

FetchContent_MakeAvailable(polymorphic_value)
target_include_directories(polymorphic_value INTERFACE
                           ${polymorphic_value_SOURCE_DIR})

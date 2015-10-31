cmake_minimum_required(VERSION 3.3)
project(cmake_org_tutorial)

include(FeatureSummary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# The version number.
set(BUILD_VERSION_MAJOR 1)
set(BUILD_VERSION_MINOR 0)
set(BUILD_VERSION_MICRO 0)

string(TIMESTAMP BUILD_DATE "%Y-%m-%d")
set(PACKAGE "CMake_Tutorial")
set(PACKAGE_NAME "CMake_Tutorial")
set(PACKAGE_VERSION "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(PACKAGE_STRING "CMake_Tutorial ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(PACKAGE_TARNAME "CMake_Tutorial")
set(PACKAGE_BUGREPORT "bl@CMake_Tutorial.com")
set(PACKAGE_URL "http://www.CMake_Tutorial.com/") # empty leaves it undefined
set(VERSION "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(HEX_VERSION "0x0${BUILD_MAJOR}0${BUILD_MINOR}0${BUILD_MICRO}")

# should we use cereal serialization?
option (USE_CEREAL "Use cereal serialization" ON)

# add the cereal header?
#
if (USE_CEREAL)
    include_directories (".")
    include_directories ("./cereal")
#    include_directories ("${PROJECT_SOURCE_DIR}/cereal/")
endif (USE_CEREAL)

# should we use our own math functions?
option (USE_MYMATH "Use tutorial provided math implementation" OFF)

# add the MathFunctions library?
#
if (USE_MYMATH)
    include_directories ("${PROJECT_SOURCE_DIR}/math_functions")

    add_subdirectory (math_functions)
    set (EXTRA_LIBS ${EXTRA_LIBS} math_functions)
endif (USE_MYMATH)

#find_package(ZLIB)
#set_package_properties(ZLIB PROPERTIES
#        PURPOSE "Required for compression support"
#        DESCRIPTION "A Massively Spiffy Yet Delicately Unobtrusive Compression Library"
#        URL "http://zlib.net"
#        TYPE RECOMMENDED
#)

#find_package( ZLIB REQUIRED )
#if ( ZLIB_FOUND )
#    include_directories( ${ZLIB_INCLUDE_DIRS} )
#    #target_link_libraries( YourProject ${ZLIB_LIBRARIES} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${ZLIB_LIBRARIES})
#endif( ZLIB_FOUND )

#find_package( PNG REQUIRED )
#if ( PNG_FOUND )
#    include_directories( ${PNG_INCLUDE_DIRS} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${PNG_LIBRARIES})
#endif( PNG_FOUND )

#find_package( JPEG )
##if ( JPEG_FOUND )
#    include_directories( ${JPEG_INCLUDE_DIR} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${JPEG_LIBRARIES})
#endif( JPEG_FOUND )

#find_package( Freetype REQUIRED )
#if ( FREETYPE_FOUND )
#    include_directories( ${FREETYPE_INCLUDE_DIRS} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${FREETYPE_LIBRARIES})
#endif( FREETYPE_FOUND )

#find_package( GIF  )
#if ( GIF_FOUND )
#    include_directories( ${GIF_INCLUDE_DIR} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${GIF_LIBRARIES})
#endif( GIF_FOUND )

#find_package( GLEW)
#if ( GLEW_FOUND )
#    include_directories( ${GLEW_INCLUDE_DIRS} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${GLEW_LIBRARIES})
#endif( GLEW_FOUND )

#find_package( OPENGL REQUIRED)
#if ( OPENGL_FOUND )
#    include_directories( ${OPENGL_INCLUDE_DIR} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${OPENGL_LIBRARIES})
#endif( OPENGL_FOUND )

#find_package( SDL REQUIRED)
#if ( SDL_FOUND )
#    include_directories( ${SDL_INCLUDE_DIR} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${SDL_LIBRARY})
#endif( SDL_FOUND )

#find_package( SDL_IMAGE REQUIRED)
#if ( SDL_IMAGE_FOUND )
#    include_directories( ${SDL_IMAGE_INCLUDE_DIRS} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${SDL_IMAGE_LIBRARIES})
#endif( SDL_IMAGE_FOUND )

#find_package( SDL_MIXER REQUIRED)
#if ( SDL_MIXER_FOUND )
#    include_directories( ${SDL_MIXER_INCLUDE_DIRS} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${SDL_MIXER_LIBRARIES})
#endif( SDL_MIXER_FOUND )

#find_package( SDL_SOUND REQUIRED)
#if ( SDL_SOUND_FOUND )
#    include_directories( ${SDL_SOUND_INCLUDE_DIR} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${SDL_SOUND_LIBRARIES})
#endif( SDL_SOUND_FOUND )

#find_package( SDL_TTF REQUIRED)
#if ( SDL_TTF_FOUND )
#    include_directories( ${SDL_TTF_INCLUDE_DIRS} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${SDL_TTF_LIBRARIES})
#endif( SDL_TTF_FOUND )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "bin/TutorialConfig.h.in"
        "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

set(SOURCE_FILES main.cpp)
add_executable(cmake_org_tutorial ${SOURCE_FILES})

# add the executable
#target_link_libraries (${EXTRA_LIBS})
target_link_libraries (cmake_org_tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS cmake_org_tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
        DESTINATION include)

include(CTest)


# does the application run
add_test (TutorialRuns cmake_org_tutorial 25)

# does the usage message work?
add_test (TutorialUsage cmake_org_tutorial)
set_tests_properties (TutorialUsage
        PROPERTIES
        PASS_REGULAR_EXPRESSION "Usage:.*number")

#define a macro to simplify adding tests, then use it
macro (do_test arg result)
    add_test (TutorialComp${arg} cmake_org_tutorial ${arg})
    set_tests_properties (TutorialComp${arg}
            PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# do a bunch of result based tests
do_test (4 "4 is 2")
do_test (9 "9 is 3")
do_test (5 "5 is 2.236")
do_test (7 "7 is 2.645")
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
do_test (0.0001 "0.0001 is 0.01")

# does this system provide the log and exp functions?
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
        "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${BUILD_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${BUILD_VERSION_MINOR}")
include (CPack)
# require version 3.10 or higher
cmake_minimum_required(VERSION 3.10)

#
# Project
#
#   - dictates the output executable filename
#
project(olcPack-GUI)

#
# C_CXX_SOURCES_DIR
#
#   - the place where your C/C++ source files are located
#
set(C_CXX_SOURCES_DIR "src")

#
# C_CXX_HEADERS_DIR
#
#   - the place where your C/C++ header files are located
#
set(C_CXX_HEADERS_DIR "include")

##########################################################################
# DO NOT EDIT BELOW THIS LINE UNLESS YOU KNOW WHAT YOU ARE DOING!!       #
##########################################################################

# Set C++ Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Source Files are Curated Here
file(
    GLOB_RECURSE SourceFiles
    "${C_CXX_SOURCES_DIR}/*.c"
    "${C_CXX_SOURCES_DIR}/*.cpp"
)

# Executable aka binary output
add_executable(${CMAKE_PROJECT_NAME} ${SourceFiles})

add_subdirectory(third_party/wxWidgets)
target_link_libraries(${CMAKE_PROJECT_NAME} wx::net wx::core wx::base)

# Apple Specifics
if (APPLE AND NOT EMSCRIPTEN)

    # Carbon
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${CARBON_LIBRARY})

    # GLUT
    # find_package(GLUT REQUIRED)
    # target_link_libraries(${CMAKE_PROJECT_NAME} ${GLUT_LIBRARIES})

endif (APPLE AND NOT EMSCRIPTEN)
    
# Linux Specifics
if (UNIX AND NOT APPLE AND NOT EMSCRIPTEN)

    # X11
    # find_package(X11 REQUIRED)
    # target_link_libraries(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES})

    # include_directories(${X11_INCLUDE_DIRS})

endif (UNIX AND NOT APPLE AND NOT EMSCRIPTEN)

# UNIX or UNIX-like (Linux, MacOS, MSYS2, Cygwin, etc)
if (UNIX)
    
    # Threads
    # if (NOT EMSCRIPTEN)
    #     find_package(Threads REQUIRED)
    #     target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads)
        
    #     include_directories(${Threads_INCLUDE_DIRS})
    # endif (NOT EMSCRIPTEN)
    
    # # PNG
    # if (EMSCRIPTEN)
    #     execute_process(COMMAND embuilder build libpng OUTPUT_QUIET)
    #     execute_process(COMMAND embuilder build zlib OUTPUT_QUIET)
    # endif (EMSCRIPTEN)
    
    # find_package(PNG REQUIRED)
    # target_link_libraries(${CMAKE_PROJECT_NAME} ${PNG_LIBRARIES})
    # include_directories(${PNG_INCLUDE_DIRS})

    # if (NOT APPLE AND NOT MINGW AND NOT CYGWIN)
    #     find_package(OpenAL REQUIRED)
    #     target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENAL_LIBRARY})
    #     include_directories(${OPENAL_INCLUDE_DIRS})
    #     set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DUSE_OPENAL")
    # endif (NOT APPLE AND NOT MINGW AND NOT CYGWIN)

endif (UNIX)

# Windows Specifics
if (WIN32 AND NOT EMSCRIPTEN)
    
    # We need to specify the output for each configuration to make it work
    # on Visual Studio solutions.
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/bin")

    if (MSVC)
        # set the startup project to the target executable instead of ALL_BUILD
        set_property(
            DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
            PROPERTY
            VS_STARTUP_PROJECT
            ${CMAKE_PROJECT_NAME}
        )
        
        # set working directory for Visual Studio Debugger
        set_target_properties(
            ${CMAKE_PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
        
        # set subsytem, console if HAS_TERMINAL is true. windows if not
        if (HAS_TERMINAL)
            target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
        else ()
            target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
        endif ()

    endif (MSVC)
    
    # prevent console launch when compiled with MinGW
    if (MINGW)
        if (NOT HAS_TERMINAL)
            target_link_libraries(${CMAKE_PROJECT_NAME} -mwindows)
        endif (NOT HAS_TERMINAL)
    endif (MINGW)
    
endif (WIN32 AND NOT EMSCRIPTEN)


# Not on Mac; Not with MSVC; Not with Emscripten
if (NOT APPLE AND NOT MSVC AND NOT EMSCRIPTEN)
    
    # C++ Filesystem
    target_link_libraries(${CMAKE_PROJECT_NAME} stdc++fs)

endif (NOT APPLE AND NOT MSVC AND NOT EMSCRIPTEN)

# set include directory
if (EXISTS "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}" AND IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}")
    include_directories("${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}")
endif (EXISTS "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}" AND IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}")



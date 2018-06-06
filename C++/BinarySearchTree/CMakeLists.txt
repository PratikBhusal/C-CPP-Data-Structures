cmake_minimum_required(VERSION 3.9.0)
project(LinkedList)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CLEAR_COMMAND "cls")
else()
    set(CLEAR_COMMAND "clear")
endif(CMAKE_SYSTEM_NAME STREQUAL "Windows")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release)


include_directories(include)
add_executable(main
    include/BinarySearchTree.hpp
    main.cpp
)# Executable name


# Switch build type to debug
add_custom_target(debug
    DEPENDS CMakeLists.txt
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=debug ..
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)

# Switch build type to release
add_custom_target(release
    DEPENDS ${CMAKE_SOURCE_DIR}/CMakeLists.txt
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=release ..
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)

# add custom target "run"
add_custom_target(run
    DEPENDS ${CMAKE_BUILD_TYPE}
    COMMAND ${CLEAR_COMMAND}
    COMMAND ${CMAKE_BUILD_TYPE}/main
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    VERBATIM
)

# add custom target "run"
add_custom_target(gdb
    DEPENDS debug
    COMMAND ${CLEAR_COMMAND}
    COMMAND gdb main
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    VERBATIM
    USES_TERMINAL
)

message(STATUS "Doxygen found? : ${DOXYGEN_FOUND}")

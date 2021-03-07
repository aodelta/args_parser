cmake_minimum_required(VERSION 3.12)

project(args_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Version
set(args_parser_MAJOR_VERSION 0)
set(args_parser_MINOR_VERSION 0)
set(args_parser_PATCH_VERSION 0)
set(args_parser_VERSION 
${args_parser_MAJOR_VERSION}.${args_parser_MINOR_VERSION}.${args_parser_PATCH_VERSION})


# Build Options
set(ARGS_PARSER_BUILD_STATIC OFF)
set(ARGS_PARSER_BUILD_SHARED ON)


# Retrieve sources file
file (GLOB args_parser_SOURCES "src/*.h")
if(WIN32)
    list(APPEND args_parser_SOURCES "src/Windows.cpp")
elseif("${CMAKE_SYSTEM}" MATCHES "Linux")
    list(APPEND args_parser_SOURCES "src/Linux.cpp")
endif()


# Build
if(ARGS_PARSER_BUILD_STATIC)
    add_library(args_parser STATIC ${args_parser_SOURCES})
elseif(ARGS_PARSER_BUILD_SHARED)
    add_library(args_parser SHARED ${args_parser_SOURCES})
endif()

set_target_properties(args_parser PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(args_parser
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/lib"
)

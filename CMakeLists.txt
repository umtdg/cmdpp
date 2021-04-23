cmake_minimum_required(VERSION 3.11)

set(LIBRARY_VERSION 1.0)
project(cmdpp VERSION ${LIBRARY_VERSION} LANGUAGES CXX)

option(CMDPP_BUILD_EXAMPLES "Build example applications" OFF)

# This is for future use. No tests right now.
option(CMDPP_BUILD_TESTS "Build tests for library" OFF)

include(cmake/utils.cmake)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)

	set(CMDPP_BUILD_EXAMPLES ON)
	set(CMDPP_BUILD_TESTS ON)

	# set(CMAKE_VERBOSE_MAKEFILE ON)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

config_compiler_and_linker()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMDPP_BUILD_INCLUDE_DIRS
	"${cmdpp_SOURCE_DIR}/include"
	"${cmdpp_SOURCE_DIR}")
include_directories(${CMDPP_BUILD_INCLUDE_DIRS})

cxx_library(cmdpp "${cxx_strict}" src/Cmd.cpp src/utils.cpp)

if (CMDPP_BUILD_EXAMPLES)
	cxx_executable(example1 examples cmdpp examples/example1.cpp)	
	cxx_executable(example2 examples cmdpp examples/example2.cpp)	
	cxx_executable(example3 examples cmdpp examples/example3.cpp)	
endif()

if (CMDPP_BUILD_TESTS)
	# For future use.
endif()


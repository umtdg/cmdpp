cmake_minimum_required(VERSION 3.11)

set(LIBRARY_VERSION 1.0)
project(cmdpp VERSION ${LIBRARY_VERSION} LANGUAGES CXX)

option(CMDPP_BUILD_EXAMPLES "Build example applications" OFF)

# This is for future use. No tests right now.
option(CMDPP_BUILD_TESTS "Build tests for library" OFF)

include(cmake/utils.cmake)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

config_compiler_and_linker()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMDPP_BUILD_INCLUDE_DIRS
	"${cmdpp_SOURCE_DIR}/include"
	"${cmdpp_SOURCE_DIR}")
include_directories(${CMDPP_BUILD_INCLUDE_DIRS})

cxx_library(cmdpp "${cxx_strict}" src/cmd.cpp src/utils.cpp src/readline.cpp)
target_link_libraries(cmdpp readline)

if (CMDPP_BUILD_EXAMPLES)
	cxx_executable(example1 examples cmdpp examples/example1.cpp)
	cxx_executable(example2 examples cmdpp examples/example2.cpp)
endif()

if (CMDPP_BUILD_TESTS)
	enable_testing()
	include(GoogleTest)
	add_subdirectory(test)
endif()


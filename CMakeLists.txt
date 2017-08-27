# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-lssl -lcrypto")

# Set global property (all targets are impacted)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

enable_testing()

# Set the output folder where your program will be created

# Include the directory where currently processed cmakefile is located.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# St where binary files from make will go to
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
# Enable verbose make output
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
add_executable(read_files Main.cc read_files.cc)
add_test(basic_test ${EXECUTABLE_OUTPUT_PATH}/read_files)

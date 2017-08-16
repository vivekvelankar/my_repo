# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name
#Project(readfile)

enable_testing()

# Set the output folder where your program will be created

# Include the directory where currently processed cmakefile is located.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# St where binary files from make will go to
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
# Enable verbose make output
set(CMAKE_VERBOSE_MAKEFILE TRUE)
add_executable(read_files Main.cc read_files.cc)

add_test(basic_test ${EXECUTABLE_OUTPUT_PATH}/read_files)
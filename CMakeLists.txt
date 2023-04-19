cmake_minimum_required (VERSION 3.5)

# name of project
project(PSS_Lab)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# set target direcory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

# add includes 
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add sub directories
add_subdirectory(src)
add_subdirectory(test)
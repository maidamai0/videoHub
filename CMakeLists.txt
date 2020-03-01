cmake_minimum_required(VERSION 3.10)

project(VideoHub CXX)

# compile commands
set(CMAKE_COMPILE_COMMANDS on)

# cmake module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(src)


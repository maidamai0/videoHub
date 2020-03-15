cmake_minimum_required(VERSION 3.10)

project(VideoHub CXX)

set(CMAKE_CXX_STANDARD 20)

# compile commands
set(CMAKE_COMPILE_COMMANDS on)

# third party
set(THIRD_PARTY
    doctest
    fmtlib/include
    tomlplusplus/include
)
include_directories(third_party)
foreach(lib ${THIRD_PARTY})
    include_directories(third_party/${lib})
endforeach()

# cmake module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CPack)

 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)


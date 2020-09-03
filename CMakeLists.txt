cmake_minimum_required(VERSION 3.10)

project(VideoHub)

set(CMAKE_CXX_STANDARD 17)

# compile commands
set(CMAKE_COMPILE_COMMANDS on)

# third party
add_compile_definitions(
    IMGUI_IMPL_OPENGL_LOADER_GLAD2
    STB_IMAGE_IMPLEMENTATION
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
link_libraries(
    glfw
    doctest::doctest
    fmt::fmt
    nlohmann_json nlohmann_json::nlohmann_json
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/examples)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include)
add_subdirectory(third_party)
link_libraries(imgui)

link_libraries(tiny-process-library)
include(CPack)

 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)


cmake_minimum_required(VERSION 3.10)

project(VideoHub)

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

add_compile_definitions(
    IMGUI_IMPL_OPENGL_LOADER_GLAD2
    STB_IMAGE_IMPLEMENTATION
)

find_package(glfw3 CONFIG REQUIRED)
link_libraries(glfw)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/examples)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include)
add_subdirectory(third_party)
link_libraries(imgui)

include(CPack)

 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# copy fonts
file(GLOB font_files ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/misc/fonts/*.ttf)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fonts)
file(COPY ${font_files} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fonts)

# copy icon
file(COPY video_hub.png DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)

add_subdirectory(src)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.toml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/settings.toml)


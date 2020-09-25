# for imgui, use glfw & OpenGL3
add_subdirectory(glad)

file(GLOB imgui_src  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples/imgui_impl_glfw.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples/imgui_impl_opengl3.cpp)

add_library(imgui ${imgui_src})
target_link_libraries(imgui glad)
add_subdirectory(tiny_process)
add_subdirectory(tracy)
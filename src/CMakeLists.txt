# set(Roboto-Medium ${PROJECT_SOURCE_DIR}/third_party/imgui/misc/fonts/Roboto-Medium.ttf)
# set(converter ${PROJECT_SOURCE_DIR}/tools/binary_to_compressed_c.exe)

# execute_process(COMMAND ${converter} -base85 ${Roboto-Medium} roboto_medium > ${CMAKE_CURRENT_SOURCE_DIR}/Roboto-Medium.hpp
#     OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/roboto_medium.hpp
# )

file(GLOB src *.cpp)
add_executable(${PROJECT_NAME} WIN32 ${src} file_icon.rc)
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/window_icon.lib)
add_subdirectory(unittest)
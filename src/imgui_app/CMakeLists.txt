get_filename_component(APP ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB src *.cpp)
add_executable(${APP} ${src})
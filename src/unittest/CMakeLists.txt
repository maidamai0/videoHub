get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB src *.cpp)
add_executable(${TARGET} ${src})
add_test(${TARGET}_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET})
file(GLOB SRC "*.cpp")

set(TARGET_NAME "video_hub")

add_executable(${TARGET_NAME} ${SRC})
target_link_libraries(${TARGET_NAME} view model)

install(TARGETS ${TARGET_NAME})

# Retrieve the absolute path to qmake and then use that path to find
# the windeployqt binary
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND "${WINDEPLOYQT_EXECUTABLE}" --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../  --dir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" --verbose 0 --no-compiler-runtime --no-translations --no-angle --no-opengl-sw "$<TARGET_FILE:${TARGET_NAME}>"
)


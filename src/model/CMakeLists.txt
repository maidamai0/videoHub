file(GLOB SRC "*.cpp")
file(GLOB HDR "*.h")

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_compile_definitions(VH_EXPORTDLL)

add_library(${TARGET} SHARED ${SRC} qmldir)

set_target_properties(${TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/model
)

### Copy qmldir from project source to binary dir
set(COPY_QMLDIR_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/qmldir $<TARGET_FILE_DIR:${TARGET}>/qmldir)
add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${COPY_QMLDIR_COMMAND}
    COMMENT "Copying qmldir to binary directory"
)

# move dll to bin directoy
set(MOVE_MODEL_PLUGIN_COMMAND ${CMAKE_COMMAND} -E rename $<TARGET_FILE:${TARGET}> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:${TARGET}>)
add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${MOVE_MODEL_PLUGIN_COMMAND}
    COMMENT "move model plugin to binary directory"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(QMLPLUGINDUMP_BIN qmlplugindump HINTS "${_qt_bin_dir}")
    set(GENERATE_QMLTYPES_COMMAND ${QMLPLUGINDUMP_BIN} -nonrelocatable ${TARGET} 1.0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/model/plugin.qmltypes)
    add_custom_command(TARGET ${TARGET}
        POST_BUILD
        COMMAND ${GENERATE_QMLTYPES_COMMAND}
        COMMENT "generating qmltypes"
    )
endif()

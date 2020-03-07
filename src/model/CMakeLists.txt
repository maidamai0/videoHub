project(model)

file(GLOB SRC "*.cpp")
file(GLOB HDR "*.h")

include(../../cmake/qmlplugin/QmlPlugin.cmake)
add_qmlplugin(
    ${PROJECT_NAME}
    URI model
    VERSION 1.0
    SOURCES ${SRC} ${HDR} qmldir
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../
)
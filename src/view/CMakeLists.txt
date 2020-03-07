file(GLOB_RECURSE QML_FILE "*.qml")
message(STATUS "QML_FILE is ${QML_FILE}")
add_custom_target(qml ${QML_FILE})
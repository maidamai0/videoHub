# Qt5 settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_COMPONENTS Core Qml Quick)

find_package(Qt5 COMPONENTS ${QT5_COMPONENTS} REQUIRED)

foreach(qt5lib ${QT5_COMPONENTS})
    link_libraries(Qt5::${qt5lib})
endforeach()

set(QML_IMPORT_PATH "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Qt Creator extra qml import paths")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_subdirectory(Model)
add_subdirectory(view)

add_subdirectory(app)


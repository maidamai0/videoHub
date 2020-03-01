# Qt5 settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_COMPONENTS Core Qml Quick)

find_package(Qt5 COMPONENTS ${QT5_COMPONENTS} REQUIRED)

foreach(qt5lib ${QT5_COMPONENTS})
    link_libraries(Qt5::${qt5lib})
endforeach()

add_executable(${PROJECT_NAME} main.cpp resource.qrc)

install(TARGETS ${PROJECT_NAME})

include(Windeployqt)

windeployqt(${PROJECT_NAME} bin)


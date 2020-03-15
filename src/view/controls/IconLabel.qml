import QtQuick 2.12
import QtQuick.Controls 2.12

import "../fonts"
import "../theme"

Rectangle {
    id: root
    signal clicked
    property alias fontIcon: content.text
    property alias fontFamily: content.font.family
    property bool checked: false

    color: "transparent"

    Text {
        id: content
        anchors.centerIn: parent
        font.family: FontAwesome.solid
        font.pixelSize: Theme.current.simpleButtonPixelSize
        font.weight: Font.Light
    }
}
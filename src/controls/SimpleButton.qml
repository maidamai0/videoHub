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

    states: [
        State {
            name: "checked"
            PropertyChanges {
                target: root
                color: "grey"
                opacity: 0.5
            }
        },
        State {
            name: "hovered"
            PropertyChanges {
                target: root
                color: "grey"
                opacity: 0.5
            }
        },
        State {
            name: "noromal"
            PropertyChanges {
                target: root
                color: "transparent"
                opacity: 1.0
            }
        }
    ]

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
            root.checked = !root.checked

            if (checked) {
                root.state = "checked"
            }
        }
        hoverEnabled: true
        onEntered: {
            root.state = "hovered"
        }

        onExited: {
            if (!checked) {
                root.state = "normal"
            }
        }
    }
}

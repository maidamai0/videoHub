import QtQuick 2.13
import QtQuick.Layouts 1.12

import "../controls"
import "../fonts"

Rectangle {
    id: root

    signal doubleClicked
    signal hide
    signal close

    height: 30
    color: "transparent"

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            root.doubleClicked()
        }
    }

    SimpleButton {
        id: hide
        anchors.right: close.left
        anchors.rightMargin: root.height
        width: root.height
        height: root.height
        fontIcon: Icons.faMinus
        onClicked: {
            root.hide()
        }
    }

    SimpleButton {
        id: close
        anchors.right: parent.right
        anchors.rightMargin: 10
        width: root.height
        height: root.height
        fontIcon: Icons.faTimes
        onClicked: {
            root.close()
        }
    }
}

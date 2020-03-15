import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../theme"

ListView {
    width: 500

    ListModel {
        id: view_model
        ListElement {
            key: "key"
            value: "value"
        }
        ListElement {
            key: "ke1y"
            value: "value1"
        }
        ListElement {
            key: "ke2y"
            value: "value2"
        }
        ListElement {
            key: "key3"
            value: "value3"
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Theme.current.colorBackground
        opacity: 0.2
    }

    delegate: Rectangle {
        width: parent.width
        height: 50

        Label {
            id: key
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: model.key
            font.pixelSize: 20
        }

        Label {
            id: value
            anchors.left: parent.left
            anchors.leftMargin: 80
            anchors.verticalCenter: parent.verticalCenter
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: model.value
            font.pixelSize: 20
        }

        Rectangle {
            id: line
            anchors.left: value.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 1
            color: "black"
        }
    }
    model: view_model
}

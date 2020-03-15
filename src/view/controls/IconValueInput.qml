import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../theme"
import "../fonts"

ListView {
    width: 500

    property string keyIcon: Icons.faLink

    ListModel {
        id: view_model
        ListElement {
            key: Icons.faLink
            value: "Enter a link to download"
        }
    }

    delegate: Rectangle {
        width: parent.width
        height: 50

        IconLabel {
            id: keyicon
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            fontIcon: keyIcon
        }

        Input {
            id: value
            anchors.left: keyicon.right
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            font.pixelSize: Theme.current.simpleButtonPixelSize
            placeholderText: model.value
            placeholderTextColor: "grey"
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

import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

import model 1.0

import "../theme"
import "../controls"
import "../fonts"

ScrollView {
    id: root
    anchors.fill: parent
    clip: true

    property ConfigModel model

    Label {
        id: network_section
        anchors.topMargin: 10
        anchors.top: parent.top

        text: qsTr("NetWork")
    }

    Rectangle {
        id: section_line
        anchors.top: network_section.bottom
        width: parent.width
        height: 2
        color: "grey"
    }

    RowLayout {
        id: proxy
        anchors.top: section_line.bottom
        width: parent.width
        Input {
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.leftMargin: 10
            Layout.topMargin: Theme.current.windowHeaderHeight
            Layout.preferredWidth: 200
            Layout.preferredHeight: Theme.current.simpleButtonWidth
            Layout.fillWidth: true
        }

        SimpleButton {
            Layout.alignment: Qt.AlignTop | Qt.AlignRight
            Layout.topMargin: Theme.current.windowHeaderHeight
            Layout.rightMargin: 10
            Layout.preferredHeight: Theme.current.simpleButtonWidth
            Layout.preferredWidth: Theme.current.simpleButtonWidth
            fontIcon: Icons.faNetworkWired
        }
    }
}

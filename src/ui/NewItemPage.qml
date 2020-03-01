import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

import "../theme"
import "../fonts"
import "../controls"

Rectangle {
    id:root
    implicitHeight: 200
    implicitWidth: 500
    color: "transparent"
    RowLayout {
        anchors.fill: parent
        TextField {
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.topMargin: Theme.current.windowHeaderHeight
            Layout.leftMargin: 10
            Layout.preferredHeight: Theme.current.windowNavigationWidth
            Layout.preferredWidth: parent.width -50
            Layout.fillWidth: true
            placeholderText: qsTr("Enter a link to download")

            background: Rectangle{
                implicitHeight: root.height
                implicitWidth: root.width
                radius: 2
                anchors.fill: parent
                color: enabled? Theme.current.colorInputBackground:Theme.current.colorInputBackground
                border.color: color
                border.width: Theme.current.widthInputBorder
            }
        }

        SimpleButton {
            Layout.alignment: Qt.AlignTop | Qt.AlignRight
            Layout.rightMargin: 10
            Layout.topMargin: Theme.current.windowHeaderHeight
            Layout.preferredHeight: Theme.current.windowNavigationWidth
            Layout.preferredWidth: Theme.current.windowNavigationWidth
            fontIcon: Icons.faCheck
        }
    }
}

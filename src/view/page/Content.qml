import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

import "../theme"
import "../fonts"
import "../controls"


Rectangle {
    color: "transparent"
    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id:left
            Layout.preferredWidth: 200
            Layout.preferredHeight: parent.height

            color: Theme.current.colorNavigationBar
        }

        Rectangle {
            Layout.preferredWidth: 500
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height
            color: "#2471A3"
            border.color: Theme.current.borderColor
            border.width: Theme.current.borderWidth
        }
    }
}

import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

import "../theme"
import "../fonts"

TextField {
    id: root

    background: Rectangle {
        implicitHeight: root.height
        implicitWidth: root.width
        radius: 2
        anchors.fill: parent
    }
}

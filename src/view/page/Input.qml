import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

import "../theme"
import "../fonts"
import "../controls"

TextField {
    id:rootvalue

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

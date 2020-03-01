import QtQuick 2.13
import QtQuick.Layouts 1.12

import "../controls"
import "../fonts"
import "../theme"

Rectangle {
    id: root

    signal newClicked
    signal doingClicked
    signal doneClicked
    signal configClicked

    readonly property int buttonSpacing: 10

    SimpleButton {
        id: new_item
        anchors.top: root.top
        anchors.topMargin: Theme.current.windowHeaderHeight
        width: root.width
        height: width
        fontIcon: Icons.faCloud
        onClicked: {
            newClicked()
        }
    }

    SimpleButton {
        id: doing
        anchors.top: new_item.bottom
        anchors.topMargin: buttonSpacing
        width: root.width
        height: width
        fontIcon: Icons.faDownload
        onClicked: {
            doingClicked()
        }
    }

    SimpleButton {
        id: done
        anchors.top: doing.bottom
        anchors.topMargin: buttonSpacing
        width: root.width
        height: width
        fontIcon: Icons.faHdd
        onClicked: {
            doneClicked()
        }
    }

    SimpleButton {
        id: config
        anchors.bottom: root.bottom
        anchors.bottomMargin: buttonSpacing
        width: root.width
        height: width
        fontIcon: Icons.faCog
        onClicked: {
            configClicked()
        }
    }
}

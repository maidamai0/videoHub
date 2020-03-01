import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13

import "./theme"
import "./fonts"
import "./ui"
import "./controls"

Window {
    id: root
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Video Hub")
    color: Theme.current.colorBackground
    flags: Qt.FramelessWindowHint

    property bool isMaximized: false

    SplitView {
        anchors.fill: parent

        handle: Rectangle {
            implicitHeight: parent.height
            implicitWidth: SplitHandle.pressed ? Theme.current.widthSplithandlePressed : Theme.current.widthSplithandleNormal
            color: SplitHandle.pressed ? Theme.current.colorSplithandlePressed : Theme.current.colorSplithandleNormal
        }

        Navigation {
            id: navigation
            SplitView.minimumHeight: parent.height
            SplitView.maximumHeight: parent.height
            SplitView.minimumWidth: Theme.current.windowNavigationWidth
            SplitView.maximumWidth: Theme.current.windowNavigationWidth
            color: Theme.current.colorNavigationBar

            onNewClicked: {
                stack_view.visible = !stack_view.visible
            }
        }

        NewItemPage {
            id: stack_view
            visible: false
            SplitView.minimumHeight: parent.height
            SplitView.maximumHeight: parent.height
            SplitView.preferredWidth: 500
            SplitView.minimumWidth: 0
            color: Theme.current.colorNavigationBar
        }

        Rectangle {
            id: content
            SplitView.preferredHeight: parent.height
            SplitView.minimumWidth: 200
            SplitView.fillWidth: true
            color: "transparent"

            Text {
                id: background
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Video Hub")
                font.pixelSize: 60
                font.bold: true
                color: Theme.current.colorFont
                opacity: 0.5
            }
        }
    }

    WindowHeader {
        id: header
        anchors.top: parent.top
        width: parent.width
        height: Theme.current.windowHeaderHeight
        color: "transparent"

        onHide: {
            root.hide()
        }

        onClose: {
            root.close()
        }

        onDoubleClicked: {
            if (root.isMaximized) {
                root.showNormal()
                root.isMaximized = false
            } else {
                root.showMaximized()
                root.isMaximized = true
            }
        }
    }

    Component.onCompleted: {
        root.showMaximized()
        root.isMaximized = true
    }
}

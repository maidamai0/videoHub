import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../theme"
import "../fonts"
import "../controls"

import model 1.0

Rectangle {
    id: root
    implicitHeight: 200
    implicitWidth: 500
    color: "transparent"

    RowLayout {
        anchors.fill: parent

        Input {
            id: value
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.topMargin: Theme.current.windowHeaderHeight
            Layout.leftMargin: 10
            Layout.preferredHeight: Theme.current.windowNavigationWidth
            Layout.preferredWidth: parent.width - 50
            Layout.fillWidth: true

            placeholderText: qsTr("Enter a link to download")

            onAccepted: {
                console.info("text is ", value.text)
                new_item_model.address = value.text
                console.info("NewItemModel.address is ", new_item_model.address)
                config_model.httpProxy = text
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

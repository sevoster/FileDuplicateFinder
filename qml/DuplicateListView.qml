import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4

ColumnLayout {
    property alias model: duplicateView.model

    Item {
        Layout.fillWidth: true
        Layout.preferredHeight: 20
        Layout.alignment: Qt.AlignHCenter
        Layout.margins: 10

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Duplicate Groups")
            font.bold: true
            font.pointSize: 15
        }
    }

    ListView {
        id: duplicateView
        Layout.alignment: Qt.AlignHCenter
        Layout.fillWidth: true
        Layout.fillHeight: true

        spacing: 10

        delegate: Column {
            id: duplicateGroupText
            width: parent.width
            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: "Group " + index + ":\n"
                font.bold: true
                font.pointSize: 7
            }
            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: duplicateGroup
            }
        }
    }
}

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
            visible: duplicateView.count > 0
        }
    }

    ListView {
        id: duplicateView
        Layout.fillWidth: true
        Layout.fillHeight: true

        clip: true

        spacing: 25

        delegate: Column {
            id: duplicateGroupText
            clip: true
            width: parent.width

            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: "Group " + index
                font.bold: true
                font.pointSize: 10
            }
            Item {
                width: parent.width
                height: 20
            }

            Repeater {
                model: duplicateGroup

                delegate: TextField {
                    width: duplicateGroupText.width
                    text: modelData
                    readOnly: true
                    selectByMouse: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }
}

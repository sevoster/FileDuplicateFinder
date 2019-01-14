import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4

ColumnLayout {
    property alias model: duplicateView.model
    property alias isRelativePath: isRelative.checked

    Item {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredHeight: 20
        Layout.margins: 10

        visible: duplicateView.count > 0

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Duplicate Groups")
            font.bold: true
            font.pointSize: 15
        }

        CheckBox {
            id: isRelative
            anchors.right: parent.right
            text: qsTr("Relative")
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
                text: leftFile
                font.bold: true
                font.pointSize: 10
            }
            Item {
                width: parent.width
                height: 20
            }

            Repeater {
                model: rightDuplicateGroup

                delegate: TextField {
                    width: duplicateGroupText.width
                    text: modelData
                    readOnly: true
                    selectByMouse: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
}

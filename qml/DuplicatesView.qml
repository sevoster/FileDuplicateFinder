import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ColumnLayout {
    property var duplicatesModel: null
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
        model: duplicateModel

        spacing: 25

        function getRowColor(rowIndex) {
            return rowIndex % 2 === 0 ? "#dddddd" : "white"
        }

        delegate: Row {
            id: duplicateGroupText
            clip: true
            width: parent.width

            property int modelIndex: index

            TextField {
                text: leftFile
                width: duplicateGroupText.width / 2
                readOnly: true
                selectByMouse: true
                style: TextFieldStyle {
                    background: Rectangle {
                        color: duplicateView.getRowColor(modelIndex)
                        border.width: 1
                    }
                }
            }

            Column {
                id: duplicateColumn
                width: duplicateGroupText.width / 2

                Repeater {
                    model: rightDuplicateGroup

                    delegate: TextField {
                        width: duplicateColumn.width
                        text: modelData
                        readOnly: true
                        selectByMouse: true
                        style: TextFieldStyle {
                            background: Rectangle {
                                color: duplicateView.getRowColor(modelIndex)
                                border.width: 1
                            }
                        }
                    }
                }
            }

        }
    }
}

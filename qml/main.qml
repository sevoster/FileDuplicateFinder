import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("File Duplicate Finder")

    style: ApplicationWindowStyle {
        background: Rectangle {
            color: "white"
        }
    }

    statusBar: StatusBar {
        id: appStatusBar
        Label {
            id: label

            Connections {
                target: myModel
                onSubmittedMessage: {
                    label.text = message
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 30

        StartForm {
            id: startForm
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            onStarted: {
                myModel.initFinder(algo)
                myModel.findDuplicates(directoryPath, isRecursive)
            }
        }

        DuplicateListView {
            id: duplicateListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: myModel
        }
    }
}

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
                target: duplicateModel
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
            comparatorsModel: duplicateModel.comparatorNames
            findersModel: duplicateModel.finderTypes
            onStarted: {
                duplicateModel.initFinder(chosenFinder, chosenComparator)
                duplicateModel.findDuplicates(leftDirectoryPath, rightDirectoryPath, isRecursive)
            }
        }

        DuplicatesView {
            id: duplicateListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            duplicatesModel: duplicateModel

            onIsRelativePathChanged: {
                duplicateModel.isRelative = isRelativePath
            }
        }
    }
}

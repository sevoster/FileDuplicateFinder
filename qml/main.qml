import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("File Duplicate Finder")

    ColumnLayout {
        anchors.fill: parent

        spacing: 30

        StartForm {
            id: startForm
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            onStarted: {
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

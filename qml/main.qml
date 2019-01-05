import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("File Duplicate Finder")

    ColumnLayout {
        anchors.fill: parent

        StartForm {
            id: startForm
            Layout.alignment: Qt.AlignHCenter
            onStarted: console.log("started process: " + directoryPath + " " + "Recursive: " + (isRecursive ? "YES" : "NO"))
        }
    }
}

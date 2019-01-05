import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

ColumnLayout {
    id: startForm

    property alias directoryPath: directoryPathText.text
    property alias isRecursive: recursive.checked

    signal started()

    spacing: 10

    FileDialog {
        id: fileDialog
        title: "Please choose a directory"
        selectFolder: true
        onAccepted: {
            directoryPathText.text = fileDialog.fileUrl
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        TextField {
            id: directoryPathText
            placeholderText: qsTr("Path to a directory")
        }

        Button {
            id: fileDialogBtn
            anchors.left: directoryPathText.right
            anchors.leftMargin: 10
            text: "Browse"
            onClicked: fileDialog.open()
        }
    }

    CheckBox {
        id: recursive
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Recursive")
        checked: false
    }

    Button {
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Start")
        onClicked: startForm.started()
    }
}

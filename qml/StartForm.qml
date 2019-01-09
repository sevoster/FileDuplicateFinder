import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

ColumnLayout {
    id: startForm

    property url directoryPath: ""
    property alias isRecursive: recursive.checked

    signal started()

    spacing: 10

    FileDialog {
        id: fileDialog
        title: "Please choose a directory"
        selectFolder: true
        onAccepted: {
            directoryPathText.text = fileDialog.fileUrl
            directoryPath = fileDialog.fileUrl
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        TextField {
            id: directoryPathText
            readOnly: true
            placeholderText: qsTr("Path to a directory")
        }

        Button {
            id: fileDialogBtn
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
        text: qsTr("Analyze")
        onClicked: startForm.started()
    }
}

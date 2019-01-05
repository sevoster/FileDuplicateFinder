import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

ColumnLayout {
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
            inputMethodHints: Qt.ImhUrlCharactersOnly
        }

        Button {
            anchors.left: directoryPathText.right
            anchors.leftMargin: 10
            id: fileDialogBtn
            text: "Browse"
            onClicked: fileDialog.open()
        }
    }

    CheckBox {
        Layout.alignment: Qt.AlignHCenter
        id: recursive
        text: qsTr("Recursive")
        checked: false
    }

    Button {
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Start")
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3

Row {
    property string labelText: "Directory"
    property string placeholder: "Path to directory"
    property string buttonText: "Browse"
    property string dialogTitle: "Please choose a directory"
    readonly property string directoryUrl: pathText.text

    spacing: 10

    Label {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        text: labelText
    }

    TextField {
        id: pathText
        selectByMouse: true
        placeholderText: placeholder
    }

    Button {
        id: button
        text: buttonText
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: dialogTitle
        selectFolder: true
        onAccepted: {
            pathText.text = fileDialog.fileUrl
        }
    }
}

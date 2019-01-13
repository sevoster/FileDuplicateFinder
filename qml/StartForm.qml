import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.4

ColumnLayout {
    id: startForm

    readonly property alias directoryPath: directoryPathText.text
    readonly property alias isRecursive: recursive.checked
    readonly property alias chosenComparator: comparatorsCombobox.currentText
    readonly property alias chosenFinder: findersCombobox.currentText
    property alias comparatorsModel: comparatorsCombobox.model
    property alias findersModel: findersCombobox.model

    signal started

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
            selectByMouse: true
        }

        Button {
            id: fileDialogBtn
            text: "Browse"
            onClicked: fileDialog.open()
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter

        Column {
            spacing: 10

            Label {
                text: qsTr("Finder:")
            }

            ComboBox {
                id: findersCombobox
            }

            Label {
                text: qsTr("Comparator:")
            }

            ComboBox {
                id: comparatorsCombobox
            }
        }

        CheckBox {
            id: recursive
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Recursive")
            checked: false
        }
    }

    Button {
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Analyze")
        onClicked: startForm.started()
    }
}

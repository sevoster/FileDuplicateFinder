import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

ColumnLayout {
    id: startForm

    readonly property alias leftDirectoryPath: leftDir.directoryUrl
    readonly property alias rightDirectoryPath: rightDir.directoryUrl
    readonly property alias isRecursive: recursive.checked
    readonly property alias chosenComparator: comparatorsCombobox.currentText
    readonly property alias chosenFinder: findersCombobox.currentText
    property alias comparatorsModel: comparatorsCombobox.model
    property alias findersModel: findersCombobox.model

    signal started

    spacing: 10

    RowLayout {
        Layout.alignment: Qt.AlignHCenter

        DirectoryChooser {
            id: leftDir
            labelText: qsTr("Left:")
        }

        DirectoryChooser {
            id: rightDir
            labelText: qsTr("Right:")
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter

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

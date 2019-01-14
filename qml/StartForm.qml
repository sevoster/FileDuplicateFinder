import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4 as Controls2

RowLayout {
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

    Column {
        Layout.alignment: Qt.AlignJustify

        spacing: 10

        DirectoryChooser {
            id: leftDir
            anchors.right: parent.right
            anchors.rightMargin: 20
            labelText: qsTr("Left:")
        }

        DirectoryChooser {
            id: rightDir
            anchors.right: parent.right
            anchors.rightMargin: 20
            labelText: qsTr("Right:")
        }
    }

    Column {
        Layout.alignment: Qt.AlignRight

        spacing: 8

        Label {
            text: qsTr("Finder:")
        }

        Controls2.ComboBox {
            id: findersCombobox
        }

        Label {
            text: qsTr("Comparator:")
        }

        Controls2.ComboBox {
            id: comparatorsCombobox
        }

        CheckBox {
            id: recursive
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Recursive")
            checked: false
        }

        Button {
            text: qsTr("Analyze")
            onClicked: startForm.started()
        }
    }
}

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Dialog {
    property alias input: textInput.text
    property alias labelText: label.text
    width: 200
    height: 80
    id: stringDialog
    standardButtons: StandardButton.Ok | StandardButton.Cancel
    onButtonClicked: ( buttonClicked === StandardButton.Ok ) ? accepted() : rejected()

    modality: Qt.ApplicationModal
    title: "Enter a name pls"
    Rectangle {
        color: "#CCCCFF"
        anchors.fill: parent
        implicitWidth: 300
        implicitHeight: 100
        Rectangle {
            anchors.centerIn: parent
            anchors.fill: parent
            Label {
                id:label
                anchors.top: parent.top
                text: "Enter a name pls"
                color: "navy"
            }
            Rectangle {
                width: 200
                height: 30
                border.color: "black"
                anchors.top : label.bottom
                border.width: 1
                TextInput {
                    anchors.fill: parent
                    id: textInput
                    width: 200
                    height: 30
                    Component.onCompleted: forceActiveFocus()
//                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.leftMargin: 4
                }
            }
        }
        Keys.onPressed: if (event.key === Qt.Key_R && (event.modifiers & Qt.ControlModifier)) filledDialog.click(StandardButton.Retry)
        Keys.onEnterPressed: filledDialog.accept()
        Keys.onEscapePressed: filledDialog.reject()
        Keys.onBackPressed: filledDialog.reject() // especially necessary on Android
    }
}

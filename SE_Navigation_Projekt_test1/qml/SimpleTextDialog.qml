import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Dialog {
    property alias input: textInput.text
    property alias labelText: label.text
    id: stringDialog
    standardButtons: "NoButton"
    //    onButtonClicked: ( buttonClicked === StandardButton.Ok ) ? accepted() : rejected()

    modality: Qt.WindowModal
    title: "Enter a name pls"
    Rectangle {
        color: "#EEEEFF"
        anchors.fill: parent
        implicitWidth: 300
        implicitHeight: 150
        Column  {
            padding: 10
            spacing: 20
            anchors.centerIn: parent
            anchors.fill: parent
            Label {
                id:label
                //                anchors.top: parent.top
                text: "Enter a name pls"
                color: "navy"
            }
            Rectangle {
                id: textRect
                width: 200
                height: 30
                border.color: "black"
                //                anchors.top : label.bottom
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
            Row {
                spacing: 10
                //                anchors.top : textRect.bottom
                Button {
                    id: acceptButton
                    text: "Ok"
                    onClicked: {
                        accepted()
                        close()
                    }
                }
                Button {
                    id: rejectButton
                    text: "Cancel"
                    onClicked: {
                        rejected()
                        close()
                    }
                }
            }
        }
//                Keys.onPressed: if (event.key === Qt.Key_R && (event.modifiers & Qt.ControlModifier)) filledDialog.click(StandardButton.Retry)
                Keys.onEnterPressed: filledDialog.accept()
                Keys.onEscapePressed: filledDialog.reject()
                Keys.onBackPressed: filledDialog.reject() // especially necessary on Android
    }
}

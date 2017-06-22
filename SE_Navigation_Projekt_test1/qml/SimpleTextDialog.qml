import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

/* SimpleTextDialog.qml
 * Dialog Popup zum speichern von Diversen Dingen.
 * Besitzt ein TextFeld zum eingeben eines Names oder Textes Generell, dessen
 * Inhalt in der aufrufenden Kompomnente verarbeitet werden kann.
 */
Dialog {
    property alias input: textInput.text
    property alias labelText: label.text
    id: stringDialog
    standardButtons: "NoButton"
    title: "Enter a name pls"
    Rectangle {
        color: "#EEEEFF"
        anchors.fill: parent
        implicitWidth: 220
        implicitHeight: 150
        Column  {
            padding: 10
            spacing: 20
            anchors.centerIn: parent
            anchors.fill: parent
            Label {
                id:label
                text: "Enter a name pls"
                color: "navy"
            }
            Rectangle {
                id: textRect
                width: 200
                height: 30
                border.color: "black"
                border.width: 1
                TextInput {
                    anchors.fill: parent
                    id: textInput
                    width: 200
                    height: 30
                    Component.onCompleted: forceActiveFocus()
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.leftMargin: 4
                    Keys.onEnterPressed: {textInput.text.trim(); accept();}
                    Keys.onEscapePressed: reject()
                    Keys.onBackPressed: reject()
                }
            }
            Row {
                width: 200
                height: 40
                spacing: 10
                HighlightButton {
                    id: acceptButton
                    width: parent.width * 0.5
                    height: parent.height
                    text: "Ok"
                    onClicked: {
                        textInput.text.trim()
                        accepted()
                        close()
                    }
                    contentItem: Image {
                        source: "qrc:/ok"
                        fillMode: Image.PreserveAspectFit
                    }
                }
                HighlightButton {
                    id: rejectButton
                    width: parent.width * 0.5
                    height: parent.height
                    text: "Cancel"
                    onClicked: {
                        rejected()
                        close()
                    }
                    contentItem: Image {
                        source: "qrc:/x"
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
                Keys.onEnterPressed: {textInput.text.trim(); accept();}
                Keys.onEscapePressed: reject()
                Keys.onBackPressed: reject()
    }
}

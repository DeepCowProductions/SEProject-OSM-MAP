import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0


Item {
    property alias settings: settingsObject
    property alias backButton: backButton

    Settings {
        id: settingsObject
    }

    Column{
        anchors.fill: parent
        Row  {
            id: buttonRow
            width: parent.width
            height: 50

            Button {
                id: backButton
                text: "back"
                width: parent.width * 0.5
                height: parent.height
            }

            Rectangle{
                width: parent.width * 0.5
                height: parent.height
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Settings"
                    color: "darkblue"
                    font.family: "Helvetica"
                    font.pointSize: 24
                }
            }            
        }

        HeaderSpacer {
            id: headerSpacer
        }


        Row {
            width: parent.width
            height: 50
            Rectangle{
                width: parent.width * 0.7
                height: parent.height
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Settings"
                    color: "navy"
                    font.pointSize: 14
                }
            }
        }


    }
    Component.onCompleted: {
        Keys.backPressed.connect(backButton.clicked)
        Keys.escapePressed.connect(backButton.clicked)
        forceActiveFocus()
    }
}

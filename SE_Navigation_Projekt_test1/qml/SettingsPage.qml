import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.utility 1.0


Item {
    property alias backButton: backButton

    signal configurationChanged ()
    onConfigurationChanged:  {
        console.log("saving settings from qml")
        // instert new options here:
        settings.useOfflineMap = cb1.checked
        settings.useNormalMapCache = cb2.checked

        settings.save()
    }

    Column{
        anchors.fill: parent
        Row  {
            id: buttonRow
            width: parent.width
            height: 50

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

            Button {
                id: backButton
                text: "back"
                width: parent.width * 0.5
                height: parent.height
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
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    text: "Use Offline Map"
                    color: "navy"
                    font.pointSize: 12
                }
            }

            CheckBox {
                id: cb1
                onCheckedChanged: configurationChanged()
                checked: settings.useOfflineMap
            }
        }


        Row {
            width: parent.width
            height: 50
            Rectangle{
                width: parent.width * 0.7
                height: parent.height
                Text{
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    text: "Use Map Cache"
                    color: "navy"
                    font.pointSize: 12
                }
            }

            CheckBox {
                id: cb2
                onCheckedChanged: configurationChanged()
                checked: settings.useNormalMapCache
            }
        }


        Row {
            width: parent.width
            height: 50
            Rectangle{
                width: parent.width * 0.7
                height: parent.height
                Text{
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    text: "<Setting Item here>"
                    color: "navy"
                    font.pointSize: 12
                }
            }

            CheckBox {
                id: cb3
                onCheckedChanged: configurationChanged()

            }
        }

        Row {
            width: parent.width
            height: 50
            Rectangle{
                width: parent.width * 0.7
                height: parent.height
                Text{
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    text: "Offline Directory"
                    color: "navy"
                    font.pointSize: 12
                }
            }

            TextEdit {
                id: offlineDirectory
                text: "<Path>"
            }
        }


    }
    Component.onCompleted: {
        Keys.backPressed.connect(backButton.clicked)
        Keys.escapePressed.connect(backButton.clicked)
        forceActiveFocus()

    }
}

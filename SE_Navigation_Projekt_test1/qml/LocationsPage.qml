import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.models 1.0

Item {
    id: locationPage

    property alias backButton: backButton
    property alias viewPlacesButtonAlias: viewPlacesButton
    property alias viewRoadsButtonAlias: viewRoadsButton
    //    signal mapRequest(double latitude, double longitude)

    Column {
        id: locationsMainColumn
        anchors.fill : parent

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
                    text: "Locations"
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

        }

        Rectangle {
            width: parent.width
            height: 50
            //            border.color: "lightgray"
            //            border.width: 1
            Row {
                anchors.fill: parent
                padding: 1
                spacing: 4
                Button {
                    id: viewPlacesButton
                    width: parent.width * 0.5
                    height: parent.height
                    text: "View my Saved Places"
                }
                Button {
                    id: viewRoadsButton
                    width: parent.width * 0.5
                    height: parent.height
                    text: "View my Saved Roads"
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 50
            //            border.color: "lightgray"
            //            border.width: 1
            Row {
                anchors.fill: parent
                padding: 1
                spacing: 4
            }
        }

        Rectangle {
            width: parent.width
            height: 50
            //            border.color: "lightgray"
            //            border.width: 1
            Row {
                anchors.fill: parent
                padding: 1
                spacing: 4
            }
        }



    }
    // end main Column

}

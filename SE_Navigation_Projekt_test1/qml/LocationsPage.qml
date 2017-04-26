import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.tools.settings 1.0

Page {
    id: locationPage
    property alias placesModel: pLacesListView.model
    property alias testButton1: scrapIt
    property alias testButton2: saveIt
    property alias testButton3: readIt

    property int listWidth: locationPage.width - 0.1
    property int listHeight: locationPage.height * 0.55

    property alias locationsBackButton: locationsBackButton


    signal mapRequest(double latitude, double longitude)

    header: TabBar {
        TabButton {
            id: locationsPageLabel
            text: "Locations"
        }

        TabButton {
            id: locationsBackButton
            text: "Back"
            onClicked: {
                console.log ("default hanlder for mapPageBackButton")

            }
        }
    }

    Component{
        id: highLightComp
        Rectangle{
            y: pLacesListView.currentItem.y
            height: 30
            width: pLacesListView.width
            border.color: "black"
            border.width: 3
            color: "gray"
            opacity: 0.1
        }
    }

    Component{
        id: placesDelegate
        Item{
            id: delegateRect
            height: 30
            width: listRect.width
            Row{
                id: delegateRow
                height: parent.height
                Rectangle{
                    width: pLacesListView.width * 0.4
                    height: 30
                    color: "transparent"
                    border.width: 1
                    border.color: "lightgray"
                    Text{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignHCenter
                        text: " " + name
                        color: "black"
                    }

                }
                Rectangle{
                    width: pLacesListView.width * 0.2
                    height: 30
                    color: "transparent"
                    border.width: 1
                    border.color: "lightgray"
                    Text{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignHCenter
                        text: " " + latitude
                        color: "black"
                    }
                }
                Rectangle{
                    width: pLacesListView.width * 0.2
                    height: 30
                    color: "transparent"
                    border.width: 1
                    border.color: "lightgray"
                    Text{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignHCenter
                        text: " " + longitude
                        color: "black"
                    }
                }
                Rectangle{
                    width: pLacesListView.width * 0.2
                    height: 30
                    color: "transparent"
                    border.width: 1
                    border.color: "lightgray"
                    Text{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignHCenter
                        text: " " + savedAtDate
                        color: "black"
                    }

                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    pLacesListView.currentIndex = index

                }
                onDoubleClicked: {
                    mapRequest(latitude, longitude)
                }
            }
        }
    }

    Column{
        id: listColumn
        anchors.fill: parent
        Row{
            id: headerRow
            height: 30
            Rectangle{
                width: pLacesListView.width * 0.4
                height: 30
                color: "white"
                border.width: 1
                border.color: "gray"
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "name"
                    color: "black"
                }
            }
            Rectangle{
                width: pLacesListView.width * 0.2
                height: 30
                color: "white"
                border.width: 1
                border.color: "gray"
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Latitude"
                    color: "black"
                }

            }
            Rectangle{
                width: pLacesListView.width * 0.2
                height: 30
                color: "white"
                border.width: 1
                border.color: "gray"
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Longitude"
                    color: "black"
                }
            }
            Rectangle{
                width: pLacesListView.width * 0.2
                height: 30
                color: "white"
                border.width: 1
                border.color: "gray"
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "date"
                    color: "black"
                }
            }
        }
        Rectangle{
            id:listRect
            color: "white"
            width: listWidth
            height: listHeight

            ListView{
                id: pLacesListView
                anchors.fill: parent
                snapMode: ListView.SnapToItem
                clip: true

                highlight: highLightComp
                highlightFollowsCurrentItem: false

                delegate: placesDelegate
            }
        }
        Button {
            id: scrapIt
            text: "scrap it"
        }
        Button {
            id: saveIt
            text: "save it"
        }
        Button {
            id: readIt
            text: "read it"
        }

    }


}

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6

Item {
    property alias toggleTrackingButton: toggleTrackingButton
    property alias toggleRecordRouteButton: toggleRecordRouteButton
    property alias centerOnMeButton: centerOnMeButton
    property alias settingsPageButton: settingsPageButton
    property alias locationPageButton: locationPageButton

    property bool followPerson
    property bool recordRoute

    function toggleFollow () {
        followPerson = !followPerson
    }
    function toggleRecordRoute () {
        recordRoute =!recordRoute
    }

    function upDateMarker (newCoord) {
        map.clearMapItems()
        marker.coordinate = newCoord
        map.addMapItem(marker)
    }

    function setToState (value) {
        console.log("setting mapState to "+value)
        mapPageTabbar.currentIndex = value
    }

    signal testSignal123 ()

    PositionSource {
        id: positionSource
        updateInterval: 10
        active: valid
        onPositionChanged: {
            var coord = position.coordinate;
            console.log("Coordinate from positionSource:", coord.longitude, coord.latitude);
            if (followPerson) {
                upDateMarker(coord)
                map.center =  positionSource.position.coordinate
            }
        }
    }

    MapQuickItem {
        id: marker
        sourceItem: Image {
            id:image
            source: "../res/marker.png"
        }
        anchorPoint.x: image.width/2
        anchorPoint.y: image.width
        smooth: false
        opacity: 0.8
    }

    GeocodeModel {
        id: geocodeModel
        plugin: map.plugin
        onLocationsChanged:
        {
            if (count == 1) {
                map.center.latitude = get(0).coordinate.latitude
                map.center.longitude = get(0).coordinate.longitude
            }
            upDateMarker(get(0).coordinate)
        }
    }

    Address {
        id :fromAddress
        street: "Hochstraße 16"
        city: "Iserlohn"
        country: "Germany"
        state : ""
        postalCode: ""
    }


    Plugin {
        id: osmPlugin
        name: "osm"
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }
    Item {
        anchors.fill: parent
        Row  {
            anchors.top: parent.top
            id: buttonRow
            width: parent.width
            height: 50
            spacing: 4
            Button {
                id: settingsPageButton
                text: "settingsPageButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                onClicked: {
                    console.log ("default hanlder for settingsPageButton ")
                }
            }
            Button {
                id: toggleTrackingButton
                text: "toggleTrackingButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                onClicked: {
                    console.log ("default hanlder for toggleTrackingButton")
                    toggleFollow()
                }
            }
            Button {
                id: centerOnMeButton
                text: "centerOnMeButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                onClicked: {
                    console.log ("default hanlder for centerOnMeButton")
                    //                geocodeModel.query = fromAddress
                    //                geocodeModel.update()
                    map.center = positionSource.position.coordinate
                    upDateMarker(positionSource.position.coordinate)
                }
            }
            Button {
                id: toggleRecordRouteButton
                text: "back"
                width: (parent.width-16) * 0.2
                height: parent.height
                //            text: map.center.map.center.latitude
                onClicked: {
                    console.log ("default hanlder for toggleRecordRouteButton ")
                    toggleRecordRoute()
                    // TBI
                    //                geocodeModel.query = fromAddress
                    //                geocodeModel.update()
                }
            }

            Button {
                id: locationPageButton
                text: "locationPageButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                onClicked: {
                    console.log ("default hanlder for locationPageButton ")
                }
            }
        }
        Rectangle {
            anchors.top: buttonRow.bottom
            width: parent.width
            height: parent.height - buttonRow.height
            Map {
                id : map
                anchors.fill: parent
                plugin: osmPlugin
                center: positionSource.position.coordinate
                zoomLevel: 10
            }
        }
    }
}

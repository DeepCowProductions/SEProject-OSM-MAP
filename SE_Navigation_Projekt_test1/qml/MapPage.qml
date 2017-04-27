import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6

Page {
    property alias mapPageTabbar: mapPageTabbar
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

    header: TabBar {
        id: mapPageTabbar
        currentIndex: 1
        TabButton {
            id: settingsPageButton
            text: "settingsPageButton"
            onClicked: {
                console.log ("default hanlder for settingsPageButton ")
            }
        }
        TabButton {
            id: toggleTrackingButton
            text: "toggleTrackingButton"
            onClicked: {
                console.log ("default hanlder for toggleTrackingButton")
                toggleFollow()
            }
        }
        TabButton {
            id: centerOnMeButton
            text: "centerOnMeButton"
            onClicked: {
                console.log ("default hanlder for centerOnMeButton")
                //                geocodeModel.query = fromAddress
                //                geocodeModel.update()
                map.center = positionSource.position.coordinate
                upDateMarker(positionSource.position.coordinate)
            }
        }
        TabButton {
            id: toggleRecordRouteButton
            text: "toggleRecordRouteButton"
            //            text: map.center.map.center.latitude
            onClicked: {
                console.log ("default hanlder for toggleRecordRouteButton ")
                toggleRecordRoute()
                // TBI
//                geocodeModel.query = fromAddress
//                geocodeModel.update()
            }
        }
        TabButton {
            id: locationPageButton
            text: "locationPageButton"
            onClicked: {
                console.log ("default hanlder for locationPageButton ")
            }
        }
    }

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

    Rectangle {
        anchors.fill: parent
        Map {
            id : map
            anchors.fill: parent
            plugin: osmPlugin
            center: positionSource.position.coordinate
            zoomLevel: 10
        }
    }
}

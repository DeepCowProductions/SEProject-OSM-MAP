import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6

Page {
    property alias mapPageTabbar: mapPageTabbar
    property alias trackPositionButton: trackPositionButton
    property alias trackRouteButton: trackRouteButton
    property alias settingsPageButton: settingsPageButton
    property alias locationPageButton: locationPageButton

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
            id: trackPositionButton
            text: "trackPositionButton"
            onClicked: {
                console.log ("default hanlder for trackPositionButton")
                geocodeModel.query = fromAddress
                geocodeModel.update()
            }
        }
        TabButton {
            id: trackRouteButton
            text: "trackRouteButton"
            //            text: map.center.map.center.latitude
            onClicked: {
                console.log ("default hanlder for trackRouteButton ")
                //                geocodeModel.query = fromAddress
                //                geocodeModel.update()
                //                map.clearMapItems()
                marker.coordinate = positionSource.coordinate
                //                map.addMapItem(marker)
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
        active: true

        onPositionChanged: {
            var coord = src.position.coordinate;
            console.log("Coordinate:", coord.longitude, coord.latitude);
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
        coordinate: map.center
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
            marker.coordinate = get(0).coordinate
            map.addMapItem(marker)
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

    Column{
        Label {
            id:debugWindow
            text:""
        }

        Map {
            id : map
            anchors.fill: parent
            plugin: osmPlugin
            center: positionSource.position.coordinate
            zoomLevel: 10

            property MapCircle circle
        }
    }
}

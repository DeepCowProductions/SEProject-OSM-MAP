import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
//import fhswf.se.tools.settings 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    PositionSource {
        id: positionSource
    }

//    Settings {
//        id: settings
//    }

//    Component {
//        id: pointDelegate

//        MapCircle {
//            id: point
//            radius: 5000
//            color: "#4400FF"
//            border.color: "#4400FF"
//            border.width: 22
//            smooth: false
//            opacity: 0.5
//            center: locationData.coodinate
//        }
//    }

//    MapItemView {
//        model: geocodeModel
//        delegate: pointDelegate
//    }



    MapQuickItem {
        id: marker
        sourceItem: Image {
            id:image
            source: "res/marker.png"
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


    Address {
        id :fromAddress2
        street: "Zimmerstraße 16"
        city: "Iserlohn"
        country: "Germany"
        state : ""
        postalCode: ""
    }


    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 1
        interactive: false
        Page {
            Label {
                id: la
                text: qsTr("First custum page")
                anchors.centerIn: parent
            }
            Button {
                anchors.top: la.bottom
                id: testButton
                text: "test"
                onPressed:  {
                    geocodeModel.query = fromAddress
                    geocodeModel.update()
                }
            }
            Button {
                anchors.top: testButton.bottom
                id: testButton2
                text: "test2"
                onPressed:  {
                    geocodeModel.query = fromAddress2
                    geocodeModel.update()
                }
            }
        }

        Page {

            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
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

            Map {
                id : map
                anchors.fill: parent
                plugin: osmPlugin
                center: positionSource.position.coordinate
                zoomLevel: 10

                property MapCircle circle

            }

        }

        Page {
            Label {
                text: qsTr("Third page")
                anchors.centerIn: parent
            }
            Image {
                id: ima
                source: "res/marker.png"
            }
        }

    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
            onPressed: {
                swipeView.setCurrentIndex(0);
            }
        }
        TabButton {
            text: qsTr("Second")
            onPressed: {
                swipeView.setCurrentIndex(1);
            }
        }
        TabButton {
            text: qsTr("Third")
            onPressed: {
                swipeView.setCurrentIndex(2);
            }
        }
    }
}

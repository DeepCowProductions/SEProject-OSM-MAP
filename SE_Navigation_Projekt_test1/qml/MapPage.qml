import QtQuick 2.7
import QtQuick.Dialogs 1.2
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

    property var currentPosition: positionSource.valid ? positionSource.position.coordinate : map.center

    property var postest: QtPositioning.coordinate(0.1,0.3)

    property bool followPerson
    property bool recordRoute

    property alias path: polylineItem.path
    property alias polyline: polylineItem

    function toggleFollow () {
        followPerson = !followPerson
    }

    function toggleRecordRoute () {
        recordRoute =!recordRoute
    }

    function clearPath () {
        while (polyline.pathLength() > 0) {
            polylineItem.removeCoordinate(0)
        }
    }

    function updatePath (newPath) {
        map.removeMapItem(polyline)
        path = newPath
        map.addMapItem(polyline)
    }

    function upateLocationMarker (newCoord) {
        map.removeMapItem(locationMarker)
        locationMarker.coordinate = newCoord
        map.addMapItem(locationMarker)
    }

    function updateCurrenPosttionMarker (newCoord) {
        map.removeMapItem(currentPositionMarker)
        currentPositionMarker.coordinate = newCoord
        map.addMapItem(currentPositionMarker)
    }

    function setToState (value) {
        console.log("setting mapState to "+value)
        mapPageTabbar.currentIndex = value
    }

    signal testSignal123 ()
    signal saveTiles(variant center, int zoomlevel);

    PositionSource {
        id: positionSource
        updateInterval: 10
        active: valid
        onPositionChanged: {
            var coord = position.coordinate;
            console.log("Coordinate from positionSource:", coord.longitude, coord.latitude);
            if (followPerson) {
                upateLocationMarker(coord)
                map.center =  positionSource.position.coordinate
            }
            if (recordRoute) {
                coordList[coordCount] = positionSource.position.coordinate
                coordCount++
                console.log("Recorded Coordinate list:" + coordList)
            }
        }
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        onTriggered: {
            polyline.addCoordinate(map.center)
//            updatePath()
//            marker.coordinate = map.center
//            map.addMapItem(marker)
            console.log(polylineItem.pathLength())
            console.log("Recorded Coordinate list:" + path)
        }
        onRunningChanged: {
            if (!timer.running) {
                saveMsgWithTextDialog.createObject(map)
            }
        }
    }

    MapPolyline {
        id: polylineItem
        line.width: 2
        line.color: 'red'
    }

    Image {
        id:image
        source: "../res/marker.png"
    }
    MapQuickItem {
        id: locationMarker
        sourceItem: image
        anchorPoint.x: image.width/2
        anchorPoint.y: image.width
        smooth: false
        opacity: 0.8
    }

    MapQuickItem {
        id: currentPositionMarker
        sourceItem: image
        anchorPoint.x: image.width/2
        anchorPoint.y: image.width
        smooth: false
        opacity: 0.8
    }

//    GeocodeModel {
//        id: geocodeModel
//        plugin: map.plugin
//        onLocationsChanged:
//        {
//            if (count == 1) {
//                map.center.latitude = get(0).coordinate.latitude
//                map.center.longitude = get(0).coordinate.longitude
//            }
//            upateLocationMarker(get(0).coordinate)
//        }
//    }

//    Address {
//        id :fromAddress
//        street: "Hochstraße 16"
//        city: "Iserlohn"
//        country: "Germany"
//        state : ""
//        postalCode: ""
//    }


    Plugin {
        id: osmPlugin
        name: "osm"
        // specify plugin parameters if necessary
         PluginParameter {
             name: "osm.mapping.offline.directory"
             value: "/home/maik/Schreibtisch/OSM-Data/"
         }
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
                background: Rectangle {
                    implicitWidth: toggleTrackingButton.width
                    implicitHeight: toggleTrackingButton.height
                    color: followPerson ? "lightgreen" : "#E0E0E0"
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
                    upateLocationMarker(positionSource.position.coordinate)
                }
            }
            Button {
                id: toggleRecordRouteButton
                text: "toggleRecordRouteButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                //            text: map.center.map.center.latitude
                onClicked: {
                    console.log ("default hanlder for toggleRecordRouteButton ")
                    toggleRecordRoute()
                    // for testing on Desktop:
                    timer.running ? timer.stop() : timer.start()

                    // TBI
                }
                background: Rectangle {
                    implicitWidth: toggleTrackingButton.width
                    implicitHeight: toggleTrackingButton.height
                    color: recordRoute ? "lightgreen" : "#E0E0E0"
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
        HeaderSpacer {
            id: headerSpacer
            anchors.top: buttonRow.bottom
        }

        Rectangle {
            anchors.top: headerSpacer.bottom
            width: parent.width
            height: parent.height - buttonRow.height -headerSpacer.height
            Map {
                id : map
                anchors.fill: parent
                plugin: osmPlugin
                center: positionSource.position.coordinate
                zoomLevel: 10
            }
        }
        Component{
            id: saveMsgWithTextDialog
            SimpleTextDialog {
                title: "Do you want to save this route?"
                labelText: "Enter a name to save"
                onAccepted: {
                    console.log("accepted")
                    console.log(input)
                    console.log(path)
                    roadsModel.addItem(input,path)
                    clearPath()
                    console.log(input)
                    visible = false
                    updatePath()
                    map.forceActiveFocus()
                }
                onRejected: {
                    console.log("Rejected")
                    console.log(polyline.path)
                    // only temp
                    updatePath(roadsModel.getCoordsAtIndex(3))
                    // ...
                    visible = false
                    map.forceActiveFocus()
                }
                Component.onCompleted: visible = true
            }
        }
        Button{
            id: saveButton
            text: "Save Data"
            onClicked: saveTiles(map.center, map.zoomLevel)
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    // Only Temporary
    Component.onCompleted: {
        map.addMapItem(polyline)
    }
}

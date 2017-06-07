import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6


Item {
    property alias toggleTrackingButton: toggleTrackingButton
    property alias toggleRecordRouteButton: toggleRecordRouteButton
    property alias centerOnMeButton: centerOnMeButton
    property alias settingsPageButton: settingsPageButton
    property alias locationPageButton: locationPageButton
    property alias path: polylineItem.path
    property alias polyline: polylineItem
    property alias map: map

    property var currentPosition: positionSource.valid ? positionSource.position.coordinate : map.center
    property var postest: QtPositioning.coordinate(0.1,0.3)

    property bool followPerson
    onFollowPersonChanged: {
        console.log("followPerson changed, new value is: " + followPerson)
        if (!followPerson) {
            //            map.removeMapItem(currentPositionMarker)
        }
    }
    property bool saveButtonEnabled: true

    property bool recordRoute
    onRecordRouteChanged: {
        console.log("racordroute changed, new value is: " + recordRoute)
        if(!recordRoute) {
            console.log("opening save dialog...")
            saveMsgWithTextDialog.createObject(map)
        }
    }

    function toggleFollow () {
        console.log("toggle follow")
        followPerson = !followPerson
    }

    function toggleRecordRoute () {
        console.log("toggle Record Route")
        recordRoute =!recordRoute
    }

    function clearPath () {
        console.log("clearing path")
        //        map.removeMapItem(polyline)
        while (polyline.pathLength() > 0) {
            polylineItem.removeCoordinate(0)
        }
        //        map.addMapItem(polyline)
        polyline.visible = false
        //        polyline.update()
    }

    function updatePath (newPath) {
        console.log("updating path")
        map.removeMapItem(polyline)
        if ( typeof(newPath) == "undefined" || !newPath ) {
            console.log("updatePath: no new path defined")
        }else{
            console.log("new path: " + newPath)
            path = newPath
        }
        map.addMapItem(polyline)
        polyline.visible = true
    }

    function updateLocationMarker (newCoord) {
        console.log("update Loaction marker")
        map.removeMapItem(locationMarker)
        locationMarker.coordinate = newCoord
        map.addMapItem(locationMarker)
    }

    function updateCurrenPosttionMarker (newCoord) {
        console.log("update current location marker")
        map.removeMapItem(currentPositionMarker)
        currentPositionMarker.coordinate = newCoord
        map.addMapItem(currentPositionMarker)
    }

    signal mapRequestPosition (var coord)
    onMapRequestPosition: {
        if(followPerson) {
            toggleFollow()
        }
        updateLocationMarker(coord)
        map.center = coord
        map.zoomLevel = 8
    }

    signal mapRequestRoute(var coords)
    onMapRequestRoute: {
        if(recordRoute) {
            toggleRecordRoute()
        }
        clearPath()
        updatePath(coords)
    }
    signal saveTiles(variant center,string fileProvider, int zoomlevel);

    PositionSource {
        id: positionSource
        updateInterval: 10
        active: valid
        Component.onCompleted: {
            console.log("Position source loaded")
        }
        onPositionChanged: {
            if (Qt.platform.os == "android") {
                var coord = position.coordinate;
                console.log("Coordinate from positionSource:", coord.longitude, coord.latitude,coord.altitude);
                if (followPerson) {
                    upateLocationMarker(coord)
                    map.center =  positionSource.position.coordinate
                }
                if (recordRoute) {
                    polyline.addCoordinate(coord)
                    console.log("Recorded Coordinate list:" + coordList)
                    console.log(polylineItem.pathLength())
                    updatePath()
                }
            }
        }
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        Component.onCompleted: {
            console.log("Timer loaded")
        }
        onTriggered: {
            if (recordRoute) {
                polyline.addCoordinate(map.center)
                updatePath()
                //            marker.coordinate = map.center
                //            map.addMapItem(marker)
                console.log(polylineItem.pathLength())
                console.log("Recorded Coordinate list:" + path)
            }
            if (followPerson) {
                updateCurrenPosttionMarker(map.center)
            }
        }
    }

    MapPolyline {
        id: polylineItem
        line.width: 2
        line.color: 'red'
        Component.onCompleted: {
            console.log("PlayLine loaded")
        }
    }

    Image {
        id:image
        source: "../res/marker.png"
        Component.onCompleted: {
            console.log("Image loaded")
        }
    }
    Image {
        id:image2
        source: "../res/marker.png"
    }
    MapQuickItem {
        id: locationMarker
        sourceItem: image
        anchorPoint.x: image.width/2
        anchorPoint.y: image.width
        smooth: false
        opacity: 0.8
        Component.onCompleted: {
            console.log("LocationMarker loaded")
        }
    }

    MapQuickItem {
        id: currentPositionMarker
        sourceItem: image2
        anchorPoint.x: image.width/2
        anchorPoint.y: image.width
        smooth: false
        opacity: 0.8
        Component.onCompleted: {
            console.log("CurrentPositionMarker loaded")
        }
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
            value: "/home/maik/Schreibtisch/OSM-Data"
        }
        Component.onCompleted: {
            console.log("OsmPlugin loaded")
            //             console.log(osmPlugin.OfflineMappingFeature.)
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
            HighlightButton {
                id: settingsPageButton
                text: "settingsPageButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                Component.onCompleted: {
                    console.log("Settingsbutton loaded")
                }

                onClicked: {
                    console.log ("default hanlder for settingsPageButton ")
                }
                contentItem: Image {
                    source: "qrc:/settings"
                    fillMode: Image.PreserveAspectFit
                }
            }
            HighlightButton {
                id: toggleTrackingButton
                text: "toggleTrackingButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                onClicked: {
                    console.log ("default hanlder for toggleTrackingButton")
                    toggleFollow()
                    if (Qt.platform.os != "android") {
                        // TEMP only for desktop
                        if (timer.running) {
                            timer.stop()
                        }else {
                            timer.start()
                        }
                    }
                }
                contentItem: Image {
                    source: "qrc:/targetInf"
                    fillMode: Image.PreserveAspectFit
                }

                activeCondition: followPerson
            }
            HighlightButton {
                id: centerOnMeButton
                text: "centerOnMeButton"

                width: (parent.width-16) * 0.2
                height: parent.height
                function toggleSaveButton () {
                    saveButton.enabled = !saveButton.enabled
                   }
                onClicked: {
                    console.log ("default hanlder for centerOnMeButton")
                    //                geocodeModel.query = fromAddress
                    //                geocodeModel.update()
                    map.center = positionSource.position.coordinate
                    upateLocationMarker(positionSource.position.coordinate)
                    toggleSaveButton()
                    updateLocationMarker(positionSource.position.coordinate)
                }
                contentItem: Image {
                    source: "qrc:/target"
                    fillMode: Image.PreserveAspectFit
                }

            }



            HighlightButton {
                id: toggleRecordRouteButton
                text: "toggleRecordRouteButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                //            text: map.center.map.center.latitude
                onClicked: {
                    console.log ("default hanlder for toggleRecordRouteButton ")
                    toggleRecordRoute()
                    // TEMP only for desktop
                    if (Qt.platform.os != "android") {
                        if (timer.running) {
                            timer.stop()
                        }else {
                            timer.start()
                        }
                    }
                }
                contentItem: Image {
                    source: "qrc:/track"
                    fillMode: Image.PreserveAspectFit
                }
                activeCondition: recordRoute
            }

            HighlightButton {
                id: locationPageButton
                text: "locationPageButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                onClicked: {
                    console.log ("default hanlder for locationPageButton ")
                }
                contentItem: Image {
                    source: "qrc:/directions"
                    fillMode: Image.PreserveAspectFit
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
                    console.log("saveDialog accepted")
                    console.log("input is: " + input)
                    console.log("path to save s : " + path)
                    console.log("qml: call roadsModel.addItem(...)")
                    roadsModel.addItem(input,path)
                    // TODO: option to keep path displayed???
                    clearPath()
                    visible = false
                    //                    updatePath()
                    map.forceActiveFocus()
                }
                onRejected: {
                    console.log("Rejected")
                    console.log("This path will be gone: " + polyline.path)
                    visible = false
                    clearPath()
                    //                    updatePath()
                    //                    map.removeMapItem(polyline)
                    //                    map.addMapItem(polyline)
                    map.forceActiveFocus()
                }
                Component.onCompleted: visible = true
            }
        }
        RoundHighlightButton{
            id: saveButton
            enabled: saveButtonEnabled
            text: "Save Data"
            //            onClicked: appWindow.saveTiles(map.center, map.zoomLevel)
            onClicked: saveTiles(map.center, "korona.geog.uni-heidelberg.de", map.zoomLevel)
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: (parent.width -16)  * 0.2
            height: (parent.height - 8) * 0.1

            Component.onCompleted: {
                console.log("Save Button erstellt")
            }
            contentItem: Image {
                source: "qrc:/file"
                fillMode: Image.PreserveAspectFit
            }
            radius: 9000
        }
    }

    // Only Temporary
    Component.onCompleted: {
        map.addMapItem(polyline)
    }
}

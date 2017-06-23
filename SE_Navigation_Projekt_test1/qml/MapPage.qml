import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtPositioning 5.8
import QtLocation 5.8
import Qt.labs.platform 1.0

/* MapPage.qml
 * Zentrales Item dieser App und im prinzip Hauptfenster.
 * Im Zentrum befindet sich ein Qt QMl Map Item mit osmPlugin.
 * Buttonhandler der oberen Buttonbar und ein par der RoundButtons sind in der main.qml implmentiert.
 * Besitzte zwei * zwei States um Routeen aufzuzeichen und/oder Standort verfolgen zu lassen. (Seperat steuerbar)
 */
Item {
    property alias toggleTrackingButton: toggleTrackingButton
    property alias toggleRecordRouteButton: toggleRecordRouteButton
    property alias centerOnMeButton: centerOnMeButton
    property alias settingsPageButton: settingsPageButton
    property alias locationPageButton: locationPageButton
    property alias saveButton: saveButton
    property alias helpPageButton: infoButton
    property alias path: polylineItem.path
    property alias polyline: polylineItem
//    property alias map: map
    property alias plugin: osmPlugin
    property alias posSrc: positionSource

    property var map
    property real bearing: map ? map.bearing : 0

    property var nullPos: QtPositioning.coordinate(10,10)
    property real fakedirection: 0
    property int currentValue: 0
    property int amount: 100
    property bool showProgressBar: false
    property bool posSrcValid: positionSource.valid && positionSource.name != "geoclue" /*geoclue for desktop geoService usually not working */

    property var pos: positionSource.valid ? positionSource.position : nullPos
    property var posCoord: positionSource.valid ? positionSource.position.coordinate : (map ? map.center : nullPos)

    property bool followPerson
    property bool recordRoute
    property bool saveButtonEnabled: true

    signal mapRequestPosition (var coord)
    signal mapRequestRoute(var coords)
    signal saveTiles(variant center,string fileProvider, int zoomlevel, int depth);

    function createPlugin(dir) {
        return Qt.createQmlObject(
           'import QtLocation 5.8;
            Plugin {
                id: osmPlugin
                name: "osm"
                PluginParameter{ name: "osm.mapping.offline.directory"; value: "' + dir +'"}
           }'
                    ,mapInstance, "dynamic plugin")
    }

    function connectMap(dir)
    {
        var plugin = createPlugin(dir)

        var zoomLevel = null
        var center = null
        if (map) {
            map.clearMapItems()
            zoomLevel = map.zoomLevel
            center = map.center
            map.destroy()
        }

        map = mapComponent.createObject(mapParent);
        map.plugin = plugin;

        if (zoomLevel != null) {
            map.zoomLevel = zoomLevel
            map.center = center
        } else {
            map.zoomLevel = (map.maximumZoomLevel - map.minimumZoomLevel)/2
        }

//        mapItem.forceActiveFocus()
    }


    // translatePosError: übersetzt integer enum PositionSource.errors in lesbare strings
    function translatePosError(value) {
        var c = "";
        switch (value) {
        case PositionSource.AccessError :
            c = "No privileges to get geo position"
            break;
        case PositionSource.ClosedError :
            c = "position service closed or shutdown"
            break;
        case PositionSource.NoError :
            c = "position service running withour errors"
            break;
        case PositionSource.UnknownSourceError :
            c = "unkown error while getting geo position"
            break;
        case PositionSource.SocketError :
            c = "unable to connect to nmea-backend socket"
            break;
        }
        return c;
    }

    // toggleFollow: schalte permante verfolgung ein und aus
    function toggleFollow () {
        console.log("toggle follow")
        followPerson = !followPerson
        toggleTimer()
    }

    // toggleRecordRoute: schalte aufnahme der routen verfolgung ein und aus
    function toggleRecordRoute () {
        console.log("toggle Record Route")
        if (!recordRoute)
            clearPath()
        recordRoute =!recordRoute
        toggleTimer()
    }

    // toggleTimer: schaltet den timer bei bedarf aus
    function toggleTimer() {
        if (timer.running) {
            if (recordRoute || followPerson) {
                console.log("timer needed, keeping it running")
            }else{
                console.log("timer not needed, stopping")
                timer.stop()
            }
        } else {
            if (followPerson || recordRoute ) {
                console.log("timer needed, starting ")
                timer.start()
            }else{
                console.log("timer not needed , keeping it off")
            }
        }
    }

    // clearPath: löscht alle items aus MapPolyline.path
    function clearPath () {
        console.log("clearing path")
        //        map.removeMapItem(polyline)
        while (polyline.pathLength() > 0) {
            polylineItem.removeCoordinate(0)
        }
        polyline.visible = false
    }

    // updatePath: aktualisiert den angezeigten pfad auf der Karte
    function updatePath (newPath) {
        if (!map) return;
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

    // updateLocationMarker: aktualisiert den rote marker auf der Karte
    function updateLocationMarker (newCoord) {
        if (!map) return;
        console.log("update Loaction marker")
        map.removeMapItem(locationMarker)
        locationMarker.coordinate = newCoord
        map.addMapItem(locationMarker)
    }
    // updateCurrenPositionMarker: aktualisiert den schwazen pfeil auf der Karte
    function updateCurrenPositionMarker (newCoord) {
        if (!map) return;
        console.log("update current location marker")
        map.removeMapItem(currentPositionMarker)
        currentPositionMarker.coordinate = newCoord
        map.addMapItem(currentPositionMarker)
    }
    // updatePinPositionMarker: aktualisiert den blauen marker auf der Karte
    function updatePinPositionMarker (newCoord) {
        if (!map) return;
        console.log("update current pin marker")
        map.removeMapItem(pinPositionMarker)
        pinPositionMarker.coordinate = newCoord
        map.addMapItem(pinPositionMarker)
    }

    onFollowPersonChanged: {
        console.log("followPerson changed, new value is: " + followPerson)
        if (!followPerson) {
        }
    }

    onRecordRouteChanged: {
        console.log("racordroute changed, new value is: " + recordRoute)
        if(!recordRoute) {
            console.log("opening save dialog...")
            saveMsgOnRecordToggle.createObject(map)
        }
    }

    onMapRequestPosition: {
        if(followPerson) {
            toggleFollow()
        }
        updateLocationMarker(coord)
        if (map)
        map.center = coord
    }

    onMapRequestRoute: {
        if(recordRoute) {
            toggleRecordRoute()
        }
        clearPath()
        updatePath(coords)
    }

    PositionSource {
        id: positionSource
        updateInterval: 10
        Component.onCompleted: {
            console.log("Position source loaded")
            console.log("PositionSOurece is : " + valid + ", name: " + name)
            if (posSrcValid) start()
            console.log("PositionSOurece is after start() : " + valid + " and " + active)
        }
        onPositionChanged: {
            console.log("PositionChanged, new pos is: " +  positionSource.position.coordinate )
            if (posSrcValid) updateCurrenPositionMarker(positionSource.position.coordinate)
        }
    }

    Timer {
        id: timer
        interval: 400
        repeat: true
        onTriggered: {
            //            console.log("timer Timeout: recordroute is " + recordRoute + ", followPerson is " + followPerson)
            if (posSrcValid) {
                var coord = pos.coordinate
//                console.log("Coordinate from positionSource:", coord.longitude, coord.latitude,coord.altitude);
                if (followPerson) {
                    updateCurrenPositionMarker(coord)
                    if (map) map.center = positionSource.position.coordinate
                }
                if (recordRoute) {
                    if (typeof(coord) != 'undefined' && coord && !isNaN(coord.longitude) && !isNaN(coord.latitude)) {
                        polyline.addCoordinate(coord)
                        console.log("Recorded Coordinate list:" + path)
                        console.log(polylineItem.pathLength())
                        updatePath()
                    }else {
                        console.log("current coord is NaN")
                    }
                }
            }else {
                if (followPerson) {
                    updateCurrenPositionMarker(map.center)
                }
                if (recordRoute) {
                    polyline.addCoordinate(map.center)
                    updatePath()
                    console.log(polylineItem.pathLength())
                    console.log("Recorded Coordinate list:" + path)
                }
            }
        }
    }

    MapPolyline {
        id: polylineItem
        line.width: 2
        line.color: 'red'
    }

    MapQuickItem {
        id: currentPositionMarker
        sourceItem:  Image {
            property real rl: Math.sqrt(((width*scale*width*scale)/ 4 )+ ((height*scale*height*scale) / 4))
            id:markerImage1
            source: "qrc:/navdot"
            scale: 0.7
            rotation: (posSrcValid && positionSource.position.directionValid) ? positionSource.position.direction - bearing :  fakedirection -bearing
        }
        anchorPoint.x: Math.cos (((markerImage1.rotation+45)/360)*2*Math.PI)* markerImage1.rl
        anchorPoint.y: Math.sin (((markerImage1.rotation+45)/360)*2*Math.PI)* markerImage1.rl
        smooth: false
        opacity: 0.8
    }

    MapQuickItem {
        id: locationMarker
        sourceItem:     Image {
            id:markerImage2
            source: "../res/marker.png"
        }
        anchorPoint.x: sourceItem.width/2
        anchorPoint.y: sourceItem.height
        smooth: false
        opacity: 0.8
    }

    MapQuickItem {
        id: pinPositionMarker
        sourceItem:     Image {
            id:markerImage3
            source: "../res/marker3.png"
        }
        anchorPoint.x: (sourceItem.width)/2
        anchorPoint.y: sourceItem.height
        smooth: false
        opacity: 0.8
    }
    Component {
        id: mapComponent
        Map {
            anchors.fill: parent
            center: pos.coordinate
            zoomLevel: 10
            Component.onCompleted: center = pos.coordinate
            onErrorChanged: console.log(errorString)
        }
    }

    Plugin {
        id: osmPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.offline.directory"
            value: /*"file://" +*/ settings.offlineDirectory
//            value: "/home/student/.local/share/FH-SWF/SE-Projekt-Mobile-Navigation"
            Component.onCompleted: {
                console.log(name + ", " +  value)
                console.log(settings.offlineDirectory)
                console.log("/home/student/.local/share/FH-SWF/SE-Projekt-Mobile-Navigation")
                value = settings.offlineDirectory
            }
        }
        Component.onCompleted: {
            console.log(osmPlugin.parameters[0].value)
            console.log(settings.offlineDirectory)
            console.log("OsmPlugin loaded")
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
                onClicked: {
                    console.log ("default hanlder for centerOnMeButton")
                    if (posSrcValid) {
                        if (map) map.center = positionSource.position.coordinate
                        updateCurrenPositionMarker(positionSource.position.coordinate)
                    }
                    else {
                        updateCurrenPositionMarker(map.center)
                    }
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
                onClicked: {
                    console.log ("default hanlder for toggleRecordRouteButton ")
                    toggleRecordRoute()
                }
                contentItem: Image {
                    source: "qrc:/rec2"
                    fillMode: Image.PreserveAspectFit
                }
                activeCondition: recordRoute
            }

            HighlightButton {
                id: locationPageButton
                text: "locationPageButton"
                width: (parent.width-16) * 0.2
                height: parent.height
                contentItem: Image {
                    source: "qrc:/explore"
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
            height: parent.height - buttonRow.height - headerSpacer.height
            id: mapParent
//            Map {
//                id : map
//                anchors.fill: parent
//                center: pos.coordinate
//                zoomLevel: 10
//                Component.onCompleted: center = pos.coordinate
//                onErrorChanged: console.log(errorString)
//            }
        }
        RoundHighlightButton{
            id: saveButton
            enabled: saveButtonEnabled
            text: "Save Data"
            onClicked: {
                saveTilesDialogComp.createObject(map)
            }
            activeCondition: !enabled
            activeColor: "#df6253"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            contentItem: Image {
                source: "qrc:/file"
                fillMode: Image.PreserveAspectFit
            }
            radius: 9000
        }
        RoundHighlightButton{
            id: pinButton
            text: "Save Data"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            contentItem: Image {
                source: "qrc:/pindrop"
                fillMode: Image.PreserveAspectFit
            }
            radius: 9000
            onClicked: {
                if (!map) return;
                locationPin.setCoordinateEx(map.center)
                updatePinPositionMarker(locationPin.coordinateEx())
            }
        }
        RoundHighlightButton{
            id: locatepinButton
            text: "Save Data"
            anchors.bottom: pinButton.top
            anchors.right: parent.right
            contentItem: Image {
                source: "qrc:/locatePin"
                fillMode: Image.PreserveAspectFit
            }
            radius: 9000
            onClicked: {
                if (!map) return;
                updatePinPositionMarker(locationPin.coordinateEx())
                map.center = locationPin.coordinateEx()
            }
        }
        RoundHighlightButton{
            id: infoButton
            text: "Save Data"
            anchors.bottom: saveButton.top
            anchors.left: parent.lefre
            contentItem: Image {
                source: "qrc:/helpoutline"
                fillMode: Image.PreserveAspectFit
            }
            radius: 9000
        }
        CustomProgressBar {
            id: progressBar
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.6
            height: parent.height * 0.05
            minnValue: 0
            value: currentValue
            maxValue: amount
            isActive: showProgressBar
        }
        Component{
            id: saveMsgOnRecordToggle
            SimpleTextDialog {
                title: "Do you want to savee this route?"
                labelText: "Enter a name to save \n  not saving will delete this route!"
                onAccepted: {
                    console.log("input is: " + input)
                    console.log("path to save s : " + path)
                    console.log("qml: call roadsModel.addItem(...)")
                    routesModel.addItem(input,path)
                    clearPath()
                    visible = false
                    //                    updatePath()
                    if (map) map.forceActiveFocus()
                }
                onRejected: {
                    console.log("Rejected")
                    console.log("This path will be gone: " + polyline.path)
                    visible = false
                    clearPath()
                    if (map) map.forceActiveFocus()
                }
                Component.onCompleted: visible = true
            }
        }
        Component{
            id: saveTilesDialogComp
            SaveTilesDialog {
                minZoom: map ? map.zoomLevel : 1
                screenWidth: appWindow.width
                screenHeight: appWindow.height

                onAccepted: {
                    visible = false
                    if (!map) return;
                    map.forceActiveFocus()
                    saveTiles(map.center, "korona.geog.uni-heidelberg.de", map.zoomLevel,( zoomleveldepth-minZoom))
                    showProgressBar = true
                    console.log(map.center+", " + "korona.geog.uni-heidelberg.de"+", " + map.zoomLevel +", "+ ( zoomleveldepth-minZoom))
                }
                onRejected: {
                    visible = false
                    showProgressBar = false
                    if (!map) return;
                    map.forceActiveFocus()
                }
                Component.onCompleted: visible = true
            }
        }
    }
}

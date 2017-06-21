import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.models 1.0
import fhswf.se.nav.offlinemanager 1.0

ApplicationWindow {
    property alias mainStack: mainStack
    property alias settings : settingsObject
    property alias offlineManager: tileManagerObject

    property variant mapInstance
    property variant locationsInstance
    property variant roadsInstance
    property variant placesInstance
    property variant settingsInstance
    property variant helpInstance

    signal saveTiles(variant coordinates, string tilesProvider, int zoomlevel, int depth, int width, int height);
    signal downloadFinished();
    signal updateProgressBar(int currentValue, int amount);
    signal clearDirectory(string directory);

    function pathLength(cords) {
        if (cords.length <2)
            return 0;
        var c = 0
        for (var i=0;i<cords.length-1; i++) {
            c = c + distanceTo(cords[i].latitude,cords[i].longitude,cords[i+1].latitude,cords[i+1].longitude,"K")
        }
        return c
    }

    function distanceTo(lat1, lon1, lat2, lon2, unit) {
          var rlat1 = Math.PI * lat1/180
          var rlat2 = Math.PI * lat2/180
          var rlon1 = Math.PI * lon1/180
          var rlon2 = Math.PI * lon2/180
          var theta = lon1-lon2
          var rtheta = Math.PI * theta/180
          var dist = Math.sin(rlat1) * Math.sin(rlat2) + Math.cos(rlat1) * Math.cos(rlat2) * Math.cos(rtheta);
          dist = Math.acos(dist)
          dist = dist * 180/Math.PI
          dist = dist * 60 * 1.1515
          if (unit==="K") { dist = dist * 1.609344 }
          if (unit==="N") { dist = dist * 0.8684 }
          return dist
    }

    function initApp() {
        console.log("invoke initApp -  creating mapItem - started")
        //        placesModelInstance = placesModelComp.createObject();
        mapInstance = mapPageComp.createObject(mainStack);
        console.log("invoke initApp -  creating mapItem - created dynamic items")
        mainStack.push(mapInstance)
        //        settingsInstance = settingsPageComp.createObject(mainStack);
        //        mainStack.push(settingsInstance)
        //        mainStack.pop()
        mapInstance.forceActiveFocus()
        console.log("invoke initApp -  creating mapItem - finished")
    }

    id: appWindow
    visible: true
    width: 360
    height: 640
    title: qsTr("SE Projekt - Mobile Navigation")

    onDownloadFinished: {
        console.log("Tiles saved in Offline directory!");
        mapInstance.saveButtonEnabled = true;
        console.log(mapInstance.saveButtonEnabled);
        if(settingsInstance)
            settingsInstance.offlineDirectorySize.text = Math.round((offlineManager.calculateUsedSpace("offline") / 1024 / 1024)*100) / 100
        if(mapInstance.showProgressBar)
            mapInstance.showProgressBar = false
    }
    onUpdateProgressBar: {
        mapInstance.currentValue = currentValue
        mapInstance.amount = amount
        currentValue === amount ? mapInstance.showProgressBar = false : mapInstance.showProgressBar = true
    }

    Settings {
        id: settingsObject
    }

    TileManager{
        id: tileManagerObject
    }

    StackView {
        id: mainStack
        anchors.fill: parent

        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 200
            }
        }
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 200
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 200
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 200
            }
        }

        initialItem: Item {
            id: initPage
            //            anchors.fill: parent
            Label {
                anchors.fill: parent
                text: "Loading... "
            }
        }
    }

    Component {
        id: locationsPageComp
        LocationsPage{
            id: locationsPage
            backButton.onClicked: {
                mainStack.pop(mapInstance)
                mapInstance.forceActiveFocus()
            }
            saveThisLocationButton.onClicked: {
                saveLocationDialog.createObject(locationsInstance.mainCol)
            }
            saveThisRouteButton.onClicked: {
                if (mapInstance.recordRoute)
                    saveRouteDialog.createObject(locationsInstance.mainCol)
            }
            showPinButton.onClicked: {
                mapInstance.updateLocationMarker(locationPin.coordinateEx())
                mainStack.pop(mapInstance)
                mapInstance.forceActiveFocus()
            }
            clearMapItemsButton.onClicked: {
                mapInstance.map.clearMapItems()
                mainStack.pop(mapInstance)
                mapInstance.forceActiveFocus()
            }

            viewPlacesButton.onClicked: {
                if (!placesInstance) {
                    console.log("creating new instance of item")
                    placesInstance = placesPageComp.createObject(mainStack);
                    placesInstance.model = placesModel
                }
                else{
                    console.log("item instance already here...")
                }
                console.log("adding instance of item to mainStack")
                mainStack.push(placesInstance)
                placesInstance.forceActiveFocus()

            }
            viewRoadsButton.onClicked: {
                if (!roadsInstance) {
                    console.log("creating new instance of item")
                    roadsInstance = roadsPageComp.createObject(mainStack);
                    roadsInstance.model = routesModel
                }
                else{
                    console.log("item instance already here...")
                }
                console.log("adding instance of item to mainStack")
                mainStack.push(roadsInstance)
                roadsInstance.forceActiveFocus()
            }

            Component.onCompleted: console.log("locationsPage complete")
        }
    }

    Component {
        id: roadsPageComp
        RoutesView {
            id: roadsPage
            backButton.onClicked: {
                mainStack.pop()
                locationsInstance.forceActiveFocus()
            }
            onMapRequest: {
                console.log("coords:" + array)
                mapInstance.mapRequestRoute(array)
                mainStack.pop(mapInstance)
                mapInstance.map.center = array[0]
                mapInstance.map.zoomLevel = 10
            }

            Component.onCompleted: console.log("raodsView complete")
        }
    }

    Component {
        id: placesPageComp
        PlacesView {
            id: placesPage

            backButton.onClicked: {
                mainStack.pop()
                locationsInstance.forceActiveFocus()
            }
            onMapRequest: {
                console.log(longitude + ", " + latitude)
                mapInstance.mapRequestPosition(QtPositioning.coordinate(longitude, latitude))
                mainStack.pop(mapInstance)
            }

            Component.onCompleted: console.log("raodsView complete")
        }
    }

    Component {
        id: mapPageComp
        MapPage {
            id: mapPage
            onSaveTiles: {
                 console.log("before, efore" + mapInstance.saveButtonEnabled)
                mapInstance.saveButtonEnabled = false;
                appWindow.saveTiles(center, fileProvider, zoomlevel, depth, appWindow.width, appWindow.height);
                console.log("before" + mapInstance.saveButtonEnabled)

                console.log("after<" + mapInstance.saveButtonEnabled)
            }
            settingsPageButton.onClicked: {
                if (!settingsInstance) {
                    console.log("creating new instance of item")
                    settingsInstance = settingsPageComp.createObject(mainStack);
                                    }
                else{
                    console.log("item instance already here...")
                }
                console.log("adding instance of item to mainStack")
                mainStack.push(settingsInstance)
                settingsInstance.forceActiveFocus()
            }
            locationPageButton.onClicked: {
                if (!locationsInstance) {
                    console.log("creating new instance of item")
                    locationsInstance = locationsPageComp.createObject(mainStack);
                }
                else{
                    console.log("item instance already here...")
                }
                console.log("adding instance of item to mainStack")
                mainStack.push(locationsInstance)
                locationsInstance.forceActiveFocus()
            }
            helpPageButton.onClicked: {
                if (!helpInstance) {
                    console.log("creating new instance of item")
                    helpInstance = helpPageComp.createObject(mainStack);
                }
                else{
                    console.log("item instance already here...")
                }
                console.log("adding instance of item to mainStack")
                mainStack.push(helpInstance)
                helpInstance.forceActiveFocus()
            }

            Component.onCompleted: console.log("mapPage complete")
        }
    }

    Component {
        id: settingsPageComp
        SettingsPage {
            id: settingsPage
            backButton.onClicked: {
                settingsPage.configurationChanged()
                if(settings.offlineDirectory !== mapInstance.plugin.parameters[0].value){
                    mainStack.pop(mapInstance)
                    initApp()
                }

                mainStack.pop(mapInstance)
                mapInstance.forceActiveFocus()
            }
            onDeleteDirectory: {
                console.log("Clear directory " + directory)
                clearDirectory(directory)
            }

            Component.onCompleted: console.log("finished Settingspage")
        }
    }
    Component {
        id: helpPageComp
        HelpPage {
            id: helpPage
            backButton.onClicked: {
                mainStack.pop(mapInstance)
                mapInstance.forceActiveFocus()
            }
            Component.onCompleted: console.log("helpPage complete")
        }
    }

    Component{
        id: saveLocationDialog
        SimpleTextDialog {
            title: "Save this Location"
            labelText: "Enter a name to save"
            onAccepted: {
//                placesModel.addItem(input,mapInstance.currentPosition)
                placesModel.addItem(input,mapInstance.map.center)
                visible = false
                mainStack.forceActiveFocus()
            }
            onRejected: {
                visible = false
                mainStack.forceActiveFocus()
            }
            Component.onCompleted: visible = true
        }
    }
    Component{
        id: saveRouteDialog
        SimpleTextDialog {
            title: "Save recorded Route"
            labelText: "Enter a name to save"
            onAccepted: {
//                placesModel.addItem(input,mapInstance.currentPosition)
                console.log("saveDialog accepted")
                console.log("input is: " + input)
                console.log("path to save s : " + path)
                console.log("qml: call roadsModel.addItem(...)")
                routesModel.addItem(input,path)
                // TODO: option to keep path displayed???
                // here we want the recording to stay active
//                clearPath()
                visible = false
                mainStack.forceActiveFocus()
            }
            onRejected: {
                console.log("Rejected")
                console.log("This path will be gone: " + polyline.path)
                visible = false
//                clearPath()
                mainStack.forceActiveFocus()
            }
            Component.onCompleted: visible = true
        }
    }

    PlacesModel {
        id: placesModel
    }
    RoutesModel {
        id: routesModel
    }
    LocationPin {
        id: locationPin
    }
}

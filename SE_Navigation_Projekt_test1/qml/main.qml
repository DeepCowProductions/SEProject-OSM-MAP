import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.models 1.0

ApplicationWindow {
    //    property alias mapAlias: map
    //    property alias loactionsAlias: locations
    //    property alias settingsAlias: settings
    property alias mainStack: mainStack

    property variant mapInstance
    property variant locationsInstance
    property variant roadsInstance
    property variant placesInstance
    property variant settingsInstance

    signal saveTiles(variant coordinates, string tilesProvider, int zoomlevel, int depth, int width, int height);
    property alias settings : settingsObject

    signal enableButton();

    onEnableButton: {
        console.log("Tiles saved in Offline directory!");
        mapInstance.saveButtonEnabled = true;
        console.log(mapInstance.saveButtonEnabled);
    }
    function test () {
        console.log("test2")
    }

    id: appWindow
    visible: true
    width: 360
    height: 640
    title: qsTr("SE Projekt - Mobile Navigation")

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


    Settings {
        id: settingsObject
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
                saveLocationDialog.createObject(mapInstance)
            }
            saveThisRouteButton.onClicked: {
                if (mapInstance.recordRoute)
                    saveRouteDialog.createObject(mapInstance)
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
            displayOnMapButton.onClicked: {

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
            displayOnMapButton.onClicked: {

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
                appWindow.saveTiles(center, fileProvider, zoomlevel, 2, appWindow.width, appWindow.height);
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
            Component.onCompleted: console.log("mapPage complete")
        }

    }

    Component {
        id: settingsPageComp
        SettingsPage {
            id: settingsPage
            backButton.onClicked: {
                mainStack.pop(mapInstance)
                mapInstance.forceActiveFocus()
            }
            Component.onCompleted: console.log("settingsPage complete")
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

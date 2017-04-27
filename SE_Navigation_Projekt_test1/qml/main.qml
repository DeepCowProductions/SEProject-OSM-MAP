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


    id: appWindow
    visible: true
    width: 360
    height: 640
    title: qsTr("SE Projekt - Mobile Navigation")

    function initApp(value) {
        console.log("invoke initApp -  creating mapItem")
        //        placesModelInstance = placesModelComp.createObject();
        mapInstance = mapPageComp.createObject(mainStack);
        settingsInstance = settingsPageComp.createObject(mainStack);
        mainStack.push(mapInstance)
        mapInstance.forceActiveFocus()
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
        LocationsPage {
            id: locationsPage
            locationsBackButton.onClicked: {
                mainStack.pop(mapInstance)
                mapInstance.setToState(1)
            }
            viewPlacesButtonAlias.onClicked: {
                if (!placesInstance) {
                    console.log("creating new instance of item")
                    placesInstance = placesPageComp.createObject(mainStack);
                    placesInstance.model = placesModel
                }
                else{
                    console.log("item instance already here...")
                }
                placesInstance.setToState(0)
                console.log("adding instance of item to mainStack")
                mainStack.push(placesInstance)

            }
            viewRoadsButtonAlias.onClicked: {
                if (!roadsInstance) {
                    console.log("creating new instance of item")
                    roadsInstance = roadsPageComp.createObject(mainStack);
                    roadsInstance.model = roadsModel
                }
                else{
                    console.log("item instance already here...")
                }
                roadsInstance.setToState(0)
                console.log("adding instance of item to mainStack")
                mainStack.push(roadsInstance)
            }

            Component.onCompleted: console.log("locationsPage complete")
        }
    }

    Component {
        id: roadsPageComp
        RoadsView {
            id: roadsPage
            locationsBackButton.onClicked: {
                mainStack.pop(mapInstance)
                mapInstance.setToState(1)
            }
            testButton1.onClicked: {
                roadsModel.clearList()
            }
            testButton2.onClicked: {
                roadsModel.writeUserData()
            }
            testButton3.onClicked: {
                roadsModel.readUserData()
            }
            backToLocationsButton.onClicked: {
                mainStack.pop()
            }
            onMapRequest: {
                console.log("coords:" + array)
            }

            Component.onCompleted: console.log("raodsView complete")
        }
    }

    Component {
        id: placesPageComp
        PlacesView {
            id: placesPage
            locationsBackButton.onClicked: {
                mainStack.pop(mapInstance)
                mapInstance.setToState(1)
            }
            testButton1.onClicked: {
                placesModel.clearList()
            }
            testButton2.onClicked: {
                placesModel.writeUserData()
            }
            testButton3.onClicked: {
                placesModel.readUserData()
            }
            backToLocationsButton.onClicked: {
                mainStack.pop()
            }
            onMapRequest: {
                console.log(latitude + ", " + longitude)
            }

            Component.onCompleted: console.log("raodsView complete")
        }
    }

    Component {
        id: mapPageComp
        MapPage {
            id: mapPage
            onTestSignal123: {
                console.log("mapComponent recieved test Signal")
            }
            settingsPageButton.onClicked: {
                mainStack.push(settingsInstance)
            }
            locationPageButton.onClicked: {
                if (!locationsInstance) {
                    console.log("creating new instance of item")
                    locationsInstance = locationsPageComp.createObject(mainStack);
                }
                else{
                    console.log("item instance already here...")
                }
                locationsInstance.setToState(0)
                console.log("adding instance of item to mainStack")
                mainStack.push(locationsInstance)
            }
            Component.onCompleted: console.log("mapPage complete")
        }

    }
    Component {
        id: settingsPageComp
        SettingsPage {
            id: settingsPage

            Component.onCompleted: console.log("settingsPage complete")
        }
    }

    PlacesModel {
        id: placesModel
    }
    RoadsModel {
        id: roadsModel
    }
}

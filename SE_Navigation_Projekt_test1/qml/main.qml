import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6

ApplicationWindow {
//    property alias mapAlias: map
//    property alias loactionsAlias: locations
//    property alias settingsAlias: settings
    property alias mainStack: mainStack

    property variant mapInstance
    property variant locationsInstance
    property variant settingsInstance

    id: appWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("SE Projekt - Mobile Navigation")

    function initApp(value) {
        console.log("invoke initApp -  creating mapItem")
        mapInstance = mapPageComp.createObject(mainStack);
        locationsInstance = locationsPageComp.createObject(mainStack);
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
                mainStack.pop()
                mapInstance.setToState(1)
            }
            Component.onCompleted: console.log("locationsPage complete")
        }

    }
    Component {
        id: mapPageComp
        MapPage {
//            id: mapPage
            onTestSignal123: {
                console.log("mapComponent recieved test Signal")
            }
            settingsPageButton.onClicked: {
                mainStack.push(settingsInstance)
            }
            locationPageButton.onClicked: {
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

}

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6

Page {

    property alias locationsBackButton: locationsBackButton
    header: TabBar {
        TabButton {
            id: locationsPageLabel
            text: "Locations"
        }

        TabButton {
            id: locationsBackButton
            text: "Back"
            onClicked: {
                console.log ("default hanlder for mapPageBackButton")
                console.log(settingsInstance.settings.home)
                settingsInstance.settings.home = "Hemer"
                console.log(settingsInstance.settings.home)
            }
        }

    }

}

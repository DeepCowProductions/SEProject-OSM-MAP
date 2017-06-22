import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.models 1.0

/* PlacesView.qml
 * Listenfenster zu ranzeige und verwaltung von vom Nutzer gespeicherten Standorten.
 * Besitzt ein ListView mit Delegate und greift auf das model placesModel zu.
 * Der status editMode gibt an wie sich die unterren drei Buttons verhalten sollen und
 * steuert dessen Aussehen wenn der Nutzer editierrt oder löschen will.
 * Buttonhandler sind hier mit ausnahme des backButton lokal implentiert.
 */
Item {
    id: placesPage
    property alias model: pLacesListView.model
    property alias listView: pLacesListView

    property alias backButton: backButton
    property alias deleteLocationButton: deleteLocation
    property alias editLocationButton: editLocation
    property alias displayOnMapButton: displayOnMap

    property bool firstItem : true
    property int  editMode: 0

    signal mapRequest(double latitude, double longitude)

    Component{
        id: highLightComp
        Rectangle{
            y: pLacesListView.currentItem.y
            height: 30
            width: pLacesListView.width
            border.color: "black"
            border.width: 3
            color: "gray"
        }
    }

    Component{
        id: itemDelegate
        Item{
            id: delegateRect
            height: 30
            width: listRect.width
            Row{
                id: delegateRow
                height: parent.height
                Rectangle{
                    width: pLacesListView.width * 0.6
                    height: 30
                    color: mouseArea.itemColor
                    border.width: 1
                    border.color: "lightgray"
                    Text{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        text: " " + name
                        color: "black"
                        horizontalAlignment: Text.AlignLeft
                    }
                }

                Rectangle{
                    width: pLacesListView.width * 0.4
                    height: 30
                    color: mouseArea.itemColor
                    border.width: 1
                    border.color: "lightgray"
                    Text{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        text: " " + savedAtDate
                        color: "black"
                    }

                }
            }
            HighlightMouseArea{
                id:mouseArea
                anchors.fill: parent
                onClicked: {
                    pLacesListView.currentIndex = index
                    infoPanelName.info = name
                    infoPanelLati.info = Math.round(latitude*10000)/10000 + "°"
                    infoPanelLongi.info = Math.round(longitude*10000)/10000 +"°"
                    infoPanelDate.info = savedAtDate
                    editMode = 0
                }
                onDoubleClicked: {
                    mapRequest(longitude, latitude)
                }
                Component.onCompleted: {
                    if (firstItem) {
                        pLacesListView.currentIndex = index
                        infoPanelName.info = name
                        infoPanelLati.info = Math.round(latitude*10000)/10000 + "°"
                        infoPanelLongi.info = Math.round(longitude*10000)/10000 +"°"
                        infoPanelDate.info = savedAtDate
                        firstItem = false
                    }
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        Row  {
            id: buttonRow
            width: parent.width
            height: 50
            spacing: 4
            Rectangle{
                width: parent.width * 0.6
                height: parent.height
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "My Places"
                    color: "darkblue"
                    font.family: "Helvetica"
                    font.pointSize: 24
                }
            }
            HighlightButton {
                id: backButton
                text: "back"
                width: parent.width * 0.4
                height: parent.height
                contentItem: Image {
                    source: "qrc:/back"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

        HeaderSpacer {
            id: headerSpacer
        }
        Rectangle {
            width: parent.width
            height: parent.height - headerSpacer.height - buttonRow.height
            Column {
                id: mainItemColumn
                width: placesPage.width
                height: parent.height
                Column{
                    id: listColumn
                    width: parent.width
                    height: parent.height - infoPanel.height

                    Row{
                        id: headerRow
                        height: 30
                        width: parent.width
                        Rectangle{
                            width: pLacesListView.width * 0.6
                            height: 30
                            color: "white"
                            border.width: 1
                            border.color: "gray"
                            Text{
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: "Name"
                                color: "navy"
                            }
                        }

                        Rectangle{
                            width: pLacesListView.width * 0.4
                            height: 30
                            color: "white"
                            border.width: 1
                            border.color: "gray"
                            Text{
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: "Date"
                                color: "navy"
                            }
                        }
                    }
                    Rectangle{
                        id:listRect
                        color: "white"
                        height: parent.height -30
                        width: parent.width - 0.1

                        ListView{
                            id: pLacesListView
                            anchors.fill: parent
                            snapMode: ListView.SnapToItem
                            clip: true
                            highlightFollowsCurrentItem: true
                            delegate: itemDelegate
                            focus: true
                            onCurrentItemChanged: console.log(model.getName(pLacesListView.currentIndex) + ' selected')
                        }
                    }
                }
                Column {
                    id: infoPanel
                    width: parent.width
                    height: 160

                    HeaderSpacer {
                    }

                    Rectangle {
                        width: parent.width
                        height: 50
                        Column {
                            anchors.fill: parent
                            Row {
                                width: parent.width
                                height: parent.height * 0.5
                                padding: 1
                                spacing: 4
                                Rectangle{
                                    width: parent.width * 0.2
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        text: "Name: "
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }
                                Rectangle{
                                    width: parent.width * 0.8
                                    height: parent.height
                                    TextInput{
                                        readOnly: editMode != 1
                                        property string info
                                        id: infoPanelName
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: info + " "
                                        color: "black"
                                        font.pointSize: 12
                                        onAccepted: {
                                            editMode = 0
                                            placesModel.changeItemName(listView.currentIndex,infoPanelName.text)
                                            listView.update()
                                        }
                                    }
                                    border.color: editMode == 1 ? "lightblue" : "transparent"
                                    border.width: editMode == 1 ? 1 : 0
                                }
                            }
                            Row{
                                width: parent.width
                                height: parent.height * 0.5
                                padding: 1
                                spacing: 4

                                Rectangle{
                                    width: parent.width *  0.2
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Saved At :"
                                        color: "navy"
                                        font.pointSize: 7
                                    }
                                }
                                Rectangle{
                                    width: parent.width *  0.8
                                    height: parent.height
                                    Text{
                                        property string info
                                        id: infoPanelDate
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: info
                                        color: "black"
                                        font.pointSize: 7
                                    }
                                }
                            }
                        }
                    }
                    HeaderSpacer {
                        height: 1
                    }
                    Rectangle {
                        width: parent.width
                        height: 50
                        Column {
                            anchors.fill: parent
                            Row{
                                width: parent.width
                                height: parent.height
                                padding: 1
                                spacing: 4
                                Rectangle{
                                    width: parent.width *  0.2
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Lati:"
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }

                                Rectangle{
                                    width: parent.width *  0.3
                                    height: parent.height
                                    TextEdit{
                                        readOnly: true
                                        property string info
                                        id: infoPanelLati
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: info
                                        color: "black"
                                        font.pointSize: 12
                                    }
                                }

                                Rectangle{
                                    width: parent.width *  0.2
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Longi:"
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }
                                Rectangle{
                                    width: parent.width *  0.3
                                    height: parent.height
                                    TextEdit{
                                        readOnly: true
                                        property string info
                                        id: infoPanelLongi
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: info
                                        color: "black"
                                        font.pointSize: 12
                                    }
                                }
                            }
                        }
                    }
                    HeaderSpacer {
                        height: 1
                    }
                    Row {
                        width: parent.width - 10
                        height: 47
                        padding: 1
                        spacing: 4
                        HighlightButton {
                            id: deleteLocation
                            width: parent.width * 0.333
                            height: parent.height
                            text: "delete"
                            contentItem: Image {
                                source: editMode != 0 ? "qrc:/x" : "qrc:/delete"
                                fillMode: Image.PreserveAspectFit
                            }
                            onClicked: {
                                if (listView.count != 0)
                                switch (editMode) {
                                case 0:
                                    editMode = 2
                                    break;
                                case 1:
                                    editMode = 0
                                    infoPanelName.text = placesModel.getName(listView.currentIndex)
                                    break;
                                case 2:
                                    editMode = 0
                                    break;
                                }
                            }
                        }
                        HighlightButton {
                            id: editLocation
                            width: parent.width * 0.333
                            height: parent.height
                            text: "edit"
                            contentItem: Image {
                                source: editMode != 0 ? "qrc:/ok" : "qrc:/edit"
                                fillMode: Image.PreserveAspectFit
                            }
                            onClicked: {
                                if (listView.count != 0)
                                switch (editMode) {
                                case 0:
                                    editMode = 1
                                    infoPanelName.forceActiveFocus()
                                    break;
                                case 1:
                                    editMode = 0
                                    placesModel.changeItemName(listView.currentIndex,infoPanelName.text)
                                    listView.update()
                                    break;
                                case 2:
                                    editMode = 0
                                    placesModel.deleteItem(listView.currentIndex)
                                    break;
                                }
                            }
                        }
                        HighlightButton {
                            id: displayOnMap
                            width: parent.width * 0.333
                            height: parent.height
                            text: "display on map"
                            contentItem: Image {
                                source: "qrc:/target"
                                fillMode: Image.PreserveAspectFit
                            }
                            onClicked: {
                                mapRequest(placesModel.getLatiAtIndex(listView.currentIndex), placesModel.getLongiAtIndex(listView.currentIndex))
                            }
                        }

                    }
                    HeaderSpacer {
                        height: 1
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        Keys.backPressed.connect(backButton.clicked)
        Keys.escapePressed.connect(backButton.clicked)
        forceActiveFocus()
    }
}


import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.models 1.0

Item {
    id: roadsPage
    property alias model: roadsListView.model
    property alias listView: roadsListView

    property alias backButton: backButton
    property alias deleteRouteButton: deleteRoute
    property alias editRouteButton: editRoute
    property alias displayOnMapButton: displayOnMap

    property bool inEditMode: false

    signal mapRequest(variant array)

    Component{
        id: highLightComp
        Rectangle{
            y: roadsListView.currentItem.y
            height: 30
            width: roadsListView.width
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
                    width: roadsListView.width * 0.6
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
                    width: roadsListView.width * 0.4
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
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    roadsListView.currentIndex = index
                    infoPanelName.info = name
                    infoPanelLength.info = pathLength(roadsListView.model.getCoordsAtIndex(index))
                    infoPanelNumber.info = roadsListView.model.getCoordsAtIndex(index).length
                    infoPanelDate.info = savedAtDate
                    //                    infoPanelPos.info = ""

                }
                onDoubleClicked: {
                    mapRequest(roadsListView.model.getCoordsAtIndex(index))
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
                    text: "My Routes"
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
                width: roadsPage.width
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
                            width: roadsListView.width * 0.6
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
                            width: roadsListView.width * 0.4
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
                            id: roadsListView
                            anchors.fill: parent
                            snapMode: ListView.SnapToItem
                            clip: true

                            //                                highlight: highLightComp
                            highlightFollowsCurrentItem: false

                            delegate: itemDelegate
//                            highlight: Rectangle {
//                                color: 'grey'
//                                Text {
//                                    anchors.centerIn: parent
//                                    text: 'Hello ' + model.get(list.currentIndex).name
//                                    color: 'white'
//                                }
//                            }
                            focus: true
                            onCurrentItemChanged: console.log(model.get(roadsListView.currentIndex).name + ' selected')
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
                                    TextEdit{
                                        readOnly: !inEditMode
                                        property string info
                                        id: infoPanelName
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: info + " "
                                        color: "black"
                                        font.pointSize: 12
                                    }
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
                            //                            Row {
                            //                                width: parent.width
                            //                                height: parent.height * 0.5
                            //                                padding: 1
                            //                                spacing: 4
                            //                                Rectangle{
                            //                                    width: parent.width * 0.4
                            //                                    height: parent.height
                            //                                    Text{
                            //                                        anchors.leftMargin: 10
                            //                                        anchors.fill: parent
                            //                                        verticalAlignment: Text.AlignVCenter
                            //                                        horizontalAlignment: Text.AlignVCenter
                            //                                        text: "Position: "
                            //                                        color: "navy"
                            //                                        font.pointSize: 7
                            //                                    }
                            //                                }
                            //                                Rectangle{
                            //                                    width: parent.width * 0.6
                            //                                    height: parent.height
                            //                                    Text{
                            //                                        property string info
                            //                                        id: infoPanelPos
                            //                                        anchors.leftMargin: 10
                            //                                        anchors.fill: parent
                            //                                        verticalAlignment: Text.AlignVCenter
                            //                                        horizontalAlignment: Text.AlignVCenter
                            //                                        text: info + " "
                            //                                        color: "black"
                            //                                        font.pointSize: 7
                            //                                    }
                            //                                }
                            //                            }
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
                                        text: "# Points:"
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }

                                Rectangle{
                                    width: parent.width *  0.3
                                    height: parent.height
                                    TextEdit{
                                        readOnly: !inEditMode
                                        property string info
                                        id: infoPanelNumber
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
                                        text: "Length:"
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }
                                Rectangle{
                                    width: parent.width *  0.3
                                    height: parent.height
                                    TextEdit{
                                        readOnly: !inEditMode
                                        property string info
                                        id: infoPanelLength
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
                            id: deleteRoute
                            width: parent.width * 0.333
                            height: parent.height
                            text: "delete"
                            contentItem: Image {
                                source: inEditMode ? "qrc:/x" : "qrc:/delete"
                                fillMode: Image.PreserveAspectFit
                            }
                            onClicked: {
                                if (inEditMode) {
                                    inEditMode = false
                                }
                            }
                        }
                        HighlightButton {
                            id: editRoute
                            width: parent.width * 0.333
                            height: parent.height
                            text: "edit"
                            contentItem: Image {
                                source: inEditMode ? "qrc:/ok" : "qrc:/edit"
                                fillMode: Image.PreserveAspectFit
                            }
                            onClicked: {
                                if (inEditMode) {
                                    inEditMode = false
                                }
                                else {
                                    inEditMode = true
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
                                //TODO
//                                mapRequest(listView.currentIndex.getCoords())
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

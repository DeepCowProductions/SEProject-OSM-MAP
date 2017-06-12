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
    property alias testButton1: scrapIt
    property alias testButton2: saveIt
    property alias testButton3: readIt
    property alias listView: roadsListView

    property int listWidth: roadsPage.width - 0.1
    property int listHeight: roadsPage.height * 0.55

    property alias backButton: backButton
    property alias backToLocationsButton: backToLocationsButton
    property alias savePlaceButton: saveRoadButton

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
            opacity: 0.1
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
                width: parent.width * 0.5
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
                width: parent.width * 0.5
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
//            Flickable {
//                anchors.fill: parent
//                contentHeight: roadsPage.height
//                contentWidth: roadsPage.width
//                boundsBehavior: Flickable.StopAtBounds
//                clip: true
//                ScrollBar.vertical: ScrollBar { }
                Column {
                    id: mainItemColumn
                    width: roadsPage.width

                    Rectangle {
                        id: buttons
                        width: parent.width
                        //            anchors.top: title.bottom
                        height: 50
                        //                border.color: "lightgray"
                        //                border.width: 1
                        Row {
                            anchors.fill: parent
                            padding: 1
                            spacing: 4
                            HighlightButton {
                                id: saveRoadButton
                                width: parent.width * 0.60
                                height: parent.height
                                text: "Save currently tracked Road"
                            }
                            HighlightButton {
                                id: backToLocationsButton
                                width: parent.width * 0.4
                                height: parent.height
                                text: "Back to Locations"
                            }
                        }
                    }

                    Column{
                        id: listColumn
                        //                anchors.fill: parent
                        //            anchors.top: buttons.bottom
                        Row{
                            id: headerRow
                            height: 30
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
                            width: listWidth
                            height: listHeight

                            ListView{
                                id: roadsListView
                                anchors.fill: parent
                                snapMode: ListView.SnapToItem
                                clip: true

                                highlight: highLightComp
                                highlightFollowsCurrentItem: false

                                delegate: itemDelegate
                            }
                        }
                        Button {
                            id: scrapIt
                            text: "scrap it"
                        }
                        Button {
                            id: saveIt
                            text: "save it"
                        }
                        Button {
                            id: readIt
                            text: "read it"
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

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0
import fhswf.se.nav.models 1.0

Item {
    id: locationPage
    property alias backButton: backButton
    property alias viewPlacesButtonAlias: viewPlacesButton
    property alias viewRoadsButtonAlias: viewRoadsButton
    //    signal mapRequest(double latitude, double longitude)

    Column {
        id: locationsMainColumn
        anchors.fill : parent

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
                    text: "Locations"
                    color: "darkblue"
                    font.family: "Helvetica"
                    font.pointSize: 24
                }
            }
            HighlightButton {
                id: backButton
                text: "Back"
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
            Flickable {
                anchors.fill: parent
//                contentHeight: locationPage.height - headerSpacer.height - buttonRow.height
                contentWidth: locationPage.width
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                ScrollBar.vertical: ScrollBar { }
                Column {
                    id: mainItemColumn
                    width: locationPage.width
                    Rectangle {
                        width: parent.width
                        height: 50
                        //            border.color: "lightgray"
                        //            border.width: 1
                        Column {
                            anchors.fill: parent
                            Row {
                                width: parent.width
                                height: parent.height * 0.5
                                padding: 1
                                spacing: 4
                                Rectangle{
                                    width: parent.width * 0.4
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        text: "Current Position: "
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }
                                Rectangle{
                                    width: parent.width * 0.6
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        text: mapInstance.postest +" "
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
                                    width: parent.width *  0.3
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Latitude:"
                                        color: "navy"
                                        font.pointSize: 7
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
                                        text: mapInstance.postest.latitude + "°"
                                        color: "black"
                                        font.pointSize: 7
                                    }
                                }

                                Rectangle{
                                    width: parent.width *  0.3
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Longitude:"
                                        color: "navy"
                                        font.pointSize: 7
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
                                        text: mapInstance.postest.longitude +"°"
                                        color: "black"
                                        font.pointSize: 7
                                    }
                                }
                            }
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: 50
                        //            border.color: "lightgray"
                        //            border.width: 1
                        Row {
                            anchors.fill: parent
                            padding: 1
                            spacing: 4
                            HighlightButton {
                                id: saveThisLocationButton
                                width: parent.width
                                height: parent.height
                                text: "save this Location"
//                                contentItem: Image {
//                                    source: "qrc:/file"
//                                    fillMode: Image.PreserveAspectFit
//                                }
                                contentItem : Item {
                                        id: button
                                        width: parent.width
                                        height: parent.height
                                        Image {
                                            id: visualImage
                                            anchors.top: parent.top
                                            anchors.left: parent.left
                                            anchors.right: parent.right
                                            anchors.bottom: buttontext.top
                                            source: "qrc:/file"
                                            fillMode: Image.PreserveAspectFit
                                        }
                                        Text {
                                            id: buttontext
                                            anchors.left: parent.left
                                            anchors.right: parent.right
                                            anchors.bottom: parent.bottom
                                            text: "save this Location"
                                        }
                                    }
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 50
                        //            border.color: "lightgray"
                        //            border.width: 1
                        Row {
                            anchors.fill: parent
                            padding: 1
                            spacing: 4
                            HighlightButton {
                                id: viewPlacesButton
                                width: parent.width
                                height: parent.height
                                text: "View my Saved Places"
                            }

                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: 50
                        //            border.color: "lightgray"
                        //            border.width: 1
                        Column {
                            anchors.fill: parent
                            Row {
                                padding: 1
                                spacing: 4
                                width: parent.width
                                height: parent.height * 0.5
                                Rectangle{
                                    width: parent.width * 0.7
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        text: "Currently tracking a Route: "
                                        color: "navy"
                                        font.pointSize: 12
                                    }
                                }
                                Rectangle{
                                    width: parent.width * 0.3
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        text: mapInstance.recordRoute ? "YES" : "NO"
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
                                    width: parent.width *  0.3
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Number of Points Saved:"
                                        color: "navy"
                                        font.pointSize: 7
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
                                        text: mapInstance.path.length
                                        color: "black"
                                        font.pointSize: 7
                                    }
                                }

                                Rectangle{
                                    width: parent.width *  0.3
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                        text: "Length:"
                                        color: "navy"
                                        font.pointSize: 7
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
                                        text: mapInstance.path.length + " km"
                                        color: "black"
                                        font.pointSize: 7
                                    }
                                }
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 50
                        //            border.color: "lightgray"
                        //            border.width: 1
                        Row {
                            anchors.fill: parent
                            padding: 1
                            spacing: 4
                            HighlightButton {
                                id: viewRoadsButton
                                width: parent.width
                                height: parent.height
                                text: "View my Saved Roads"
                            }
                        }
                    }



                }
                // end main Column

                Component.onCompleted: {
                    Keys.backPressed.connect(backButton.clicked)
                    Keys.escapePressed.connect(backButton.clicked)
                    forceActiveFocus()
                }

            }
        }

    }
}

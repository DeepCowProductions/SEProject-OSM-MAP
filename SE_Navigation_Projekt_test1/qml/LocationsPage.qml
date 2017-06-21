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
    property alias viewPlacesButton: viewPlacesButton
    property alias saveThisRouteButton: saveThisRouteButton
    property alias viewRoadsButton: viewRoadsButton
    property alias saveThisLocationButton: saveThisLocationButton
    property alias mainCol: mainCol
    //    signal mapRequest(double latitude, double longitude)

    property alias clearMapItemsButton: clearMapItem
    property alias showPinButton: showPin

    Column {
        id: locationsMainColumn
        anchors.fill : parent

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
                    text: "Position"
                    color: "darkblue"
                    font.family: "Helvetica"
                    font.pointSize: 24
                }
            }
            HighlightButton {
                id: backButton
                text: "Back"
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
            id: mainCol
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
                                        text: "Current position: "
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
                                        text: mapInstance.pos.coordinate +" "
                                        color: "black"
                                        font.pointSize: 10
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
                                        text: mapInstance.pos.coordinate.latitude + "°"
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
                                        text: mapInstance.pos.coordinate.longitude +"°"
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
                                text: "save this location"
                                contentItem : Item {
                                    width: parent.width
                                    height: parent.height
                                    Image {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.bottom: parent.bottom
                                        source: "qrc:/file"
                                        width: parent.width * 0.2
                                        fillMode: Image.PreserveAspectFit
                                    }
                                    Text {
                                        anchors.right: parent.right
                                        anchors.bottom: parent.bottom
                                        anchors.top: parent.top
                                        width: parent.width * 0.8
                                        text: "Save this location"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
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
                                text: "View my saved places"
                                contentItem : Item {
                                    width: parent.width
                                    height: parent.height
                                    Image {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.bottom: parent.bottom
                                        source: "qrc:/list"
                                        width: parent.width * 0.2
                                        fillMode: Image.PreserveAspectFit
                                    }
                                    Text {
                                        anchors.right: parent.right
                                        anchors.bottom: parent.bottom
                                        anchors.top: parent.top
                                        width: parent.width * 0.8
                                        text: "View my saved places"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
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
                                        text: "Currently tracking a route: "
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
                                        text: "Number of points saved:"
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
                                        text: "Km:"
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
                                        text: pathLength(mapInstance.path)
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
                                id: saveThisRouteButton
                                width: parent.width
                                height: parent.height
                                text: "save this route"
                                contentItem : Item {
                                    width: parent.width
                                    height: parent.height
                                    Image {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.bottom: parent.bottom
                                        source: "qrc:/file"
                                        width: parent.width * 0.2
                                        fillMode: Image.PreserveAspectFit
                                    }
                                    Text {
                                        anchors.right: parent.right
                                        anchors.bottom: parent.bottom
                                        anchors.top: parent.top
                                        width: parent.width * 0.8
                                        text: "Save this route"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
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
                                contentItem : Item {
                                    width: parent.width
                                    height: parent.height
                                    Image {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.bottom: parent.bottom
                                        source: "qrc:/list"
                                        width: parent.width * 0.2
                                        fillMode: Image.PreserveAspectFit
                                    }
                                    Text {
                                        anchors.right: parent.right
                                        anchors.bottom: parent.bottom
                                        anchors.top: parent.top
                                        width: parent.width * 0.8
                                        text: "View my saved routes"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
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
                        Column {
                            anchors.fill: parent
                            Row {
                                padding: 1
                                spacing: 4
                                width: parent.width
                                height: parent.height * 0.5
                                Rectangle{
                                    width: parent.width * 0.4
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        text: "Pinned location: "
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
                                        text: locationPin.coordinateEx().toString()
                                        color: "black"
                                        font.pointSize: 10
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
                                        text: locationPin.coordinateEx().latitude
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
                                        text: locationPin.coordinateEx().longitude
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
                                id: showPin
                                width: parent.width
                                height: parent.height
                                text: "Show On Map"
                                contentItem : Item {
                                    width: parent.width
                                    height: parent.height
                                    Image {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.bottom: parent.bottom
                                        source: "qrc:/locatePin"
                                        width: parent.width * 0.2
                                        fillMode: Image.PreserveAspectFit
                                    }
                                    Text {
                                        anchors.right: parent.right
                                        anchors.bottom: parent.bottom
                                        anchors.top: parent.top
                                        width: parent.width * 0.8
                                        text: "Show pin on map"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
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
                                id: clearMapItem
                                width: parent.width
                                height: parent.height
                                text: "Clear map items"
                                contentItem : Item {
                                    width: parent.width
                                    height: parent.height
                                    Image {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.bottom: parent.bottom
                                        source: "qrc:/x"
                                        width: parent.width * 0.2
                                        fillMode: Image.PreserveAspectFit
                                    }
                                    Text {
                                        anchors.right: parent.right
                                        anchors.bottom: parent.bottom
                                        anchors.top: parent.top
                                        width: parent.width * 0.8
                                        text: "Clear map items"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
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
                                        text: "PositionSource/GPS status: "
                                        color: "navy"
                                        font.pointSize: 10
                                    }
                                }
                            }

                            Row{
                                width: parent.width
                                height: parent.height * 0.5
                                padding: 1
                                spacing: 4
                                Rectangle{
                                    width: parent.width
                                    height: parent.height
                                    Text{
                                        anchors.leftMargin: 10
                                        anchors.fill: parent
                                        text: mapInstance.translatePosError(mapInstance.posSrc.sourceError)
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignVCenter
                                        color: "navy"
                                        font.pointSize: 7
                                    }
                                }

                            }
                        }

                    }


                }
                // end main Column
            }
        }
    }
    Component.onCompleted: {
        Keys.backPressed.connect(backButton.clicked)
        Keys.escapePressed.connect(backButton.clicked)
        forceActiveFocus()
    }
}

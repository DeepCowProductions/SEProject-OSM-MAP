import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

/* SaveTilesDialog.qml
 * Dialog Popup zum speichern von Kartenausschnitten.
 * Besitzt einen Slider um den Zoomlevel auszuwählen (limit auf x+5).
 * Berechnet nach silder.valueChanged die anzahl der Tiles.
 */
Dialog {
    property alias zoomleveldepth: slider.value
    property int tileCount
    property int totalSize: tileCount * 0.060
    property int maxZoom: (minZoom + 5) >= 18 ?  18: ( minZoom + 5)
    property int minZoom: 1
    property int defaultZoom: 2
    property int screenWidth
    property int screenHeight
    id: saveTilesDialog
    standardButtons: "NoButton"

    title: "Confirm Download"
    Rectangle {
        color: "#EEEEFF"
        anchors.fill: parent
        implicitWidth: 220
        implicitHeight: 200
        Column  {
            padding: 5
            spacing: 10
            anchors.centerIn: parent
            anchors.fill: parent
            Label {
                id:label
                text: "Download currently visible Map"
                color: "navy"
            }
            Row {
                id: tileCounterRow
                width: 200
                height: 30
                Text {
                    width: parent.width *0.4
                    height: parent.height
                    text: "Zoomlevel"
                    verticalAlignment: Text.AlignVCenter
                }
                Slider {
                    width: parent.width *0.5
                    height: parent.height
                    id: slider
                    from: minZoom
                    to: maxZoom
                    value: defaultZoom
                    stepSize: 1
                    snapMode: Slider.SnapAlways
                    onValueChanged: {
                        var count =  Math.floor((screenHeight / 256) +1)
                        console.log(screenHeight +", "+ count)
                        count = count * Math.floor((screenWidth / 256)+1 )
                        console.log(screenWidth +", " + Math.floor((screenWidth / 256)+1 )+ ", "+ count)
                        var range = zoomleveldepth - minZoom +1
                        var res = 0
                        for (var i = 0 ; i<range; i++ ){
                            res = res + Math.pow(4,i)
                        }
                        tileCount = count * res
                    }
                    onPositionChanged: {
                       var range = to - from
                       zoomlevelDisplay.text = minZoom + "+" + Math.round(( range * position ))
                    }
                    Component.onCompleted: slider.value = defaultZoom
                }

                Text {
                    id: zoomlevelDisplay
                    width: parent.width *0.1
                    height: parent.height
                    text: slider.value
                    verticalAlignment: Text.AlignVCenter
                }

            }
            Row {
                width: 200
                height: 30
                Text {
                    width: parent.width *0.8
                    height: parent.height
                    text: "Number of Tiles:"
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    width: parent.width *0.2
                    height: parent.height
                    text: tileCount
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Row {
                width: 200
                height: 30
                Text {
                    width: parent.width *0.8
                    height: parent.height
                    text: "aprox req. Memory: "
                }
                Text {
                    width: parent.width *0.2
                    height: parent.height
                    text: totalSize + " MB"
                }
            }
            Row {
                width: 200
                height: 40
                spacing: 10
                HighlightButton {
                    id: acceptButton
                    width: parent.width * 0.5
                    height: parent.height
                    text: "Ok"
                    onClicked: {
                        accepted()
                        close()
                    }
                    contentItem: Image {
                        source: "qrc:/ok"
                        fillMode: Image.PreserveAspectFit
                    }
                }
                HighlightButton {
                    id: rejectButton
                    width: parent.width * 0.5
                    height: parent.height
                    text: "Cancel"
                    onClicked: {
                        rejected()
                        close()
                    }
                    contentItem: Image {
                        source: "qrc:/x"
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
                Keys.onEnterPressed: accept()
                Keys.onEscapePressed: reject()
                Keys.onBackPressed: reject()
    }
}

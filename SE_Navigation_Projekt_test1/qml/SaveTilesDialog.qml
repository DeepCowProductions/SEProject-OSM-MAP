import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Dialog {
    property int zoomleveldepth
    property int tileCount: 123
    property int totalSize: 321
    property int maxZoom: 10
    property int minZoom: 1
    property int defaultZoom
    id: saveTilesDialog
    standardButtons: "NoButton"
    //    onButtonClicked: ( buttonClicked === StandardButton.Ok ) ? accepted() : rejected()

    modality: Qt.WindowModal
    title: "Enter a name pls"
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
                //                anchors.top: parent.top
                text: "Save currently visible Map"
                color: "navy"
            }
            Row {
                id: tileCounterRow
                width: 200
                height: 30
                Text {
                    width: parent.width *0.4
                    height: parent.height
                    //                    horizontalAlignment: TextInput.AlignHCenter
                    text: "Zoomlevel"
                    verticalAlignment: Text.AlignVCenter
                }
                Slider {
                    width: parent.width *0.5
                    height: parent.height
                    id: slider
                    //                    horizontalAlignment: TextInput.AlignHCenter
                    from: minZoom
                    to: maxZoom
                    value: defaultZoom
                    stepSize: 1
                    snapMode: Slider.SnapAlways
                    onValueChanged: {

                    }
                    onPositionChanged: {
                       var range = to - from
                       zoomlevelDisplay.text = Math.round(( range * position )) + 1
                    }
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
                    //                    horizontalAlignment: TextInput.AlignHCenter
                    text: "Number of Tiles:"
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    width: parent.width *0.2
                    height: parent.height
                    //                    horizontalAlignment: TextInput.AlignHCenter
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
                    //                    horizontalAlignment: TextInput.AlignHCenter
                    text: "Required Memory:"
                }
                Text {
                    width: parent.width *0.2
                    height: parent.height
                    //                    horizontalAlignment: TextInput.AlignHCenter
                    text: totalSize
                }
            }
            Row {
                spacing: 10
                //                anchors.top : textRect.bottom
                Button {
                    id: acceptButton
                    text: "Ok"
                    onClicked: {
                        accepted()
                        close()
                    }
                }
                Button {
                    id: rejectButton
                    text: "Cancel"
                    onClicked: {
                        rejected()
                        close()
                    }
                }
            }
        }
//                Keys.onPressed: if (event.key === Qt.Key_R && (event.modifiers & Qt.ControlModifier)) filledDialog.click(StandardButton.Retry)
                Keys.onEnterPressed: filledDialog.accept()
                Keys.onEscapePressed: filledDialog.reject()
                Keys.onBackPressed: filledDialog.reject() // especially necessary on Android
    }
}

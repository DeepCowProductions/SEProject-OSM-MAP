import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: spacer
    width: parent.width
    height: 10
    color: "transparent"
    property alias progressBar: progressBar
    property alias isActive: progressBar.barActive
    property alias progress: progressBar.value
    property alias maxValue: progressBar.to
    property alias minnValue: progressBar.from
    property alias value: progressBar.value
    ProgressBar {
        property bool barActive: false
        id: progressBar
        anchors.fill: parent
        from: 0
        to: 100
        value: 50
        visible: barActive

        background: Rectangle {
            implicitWidth: spacer.implicitWidth
            implicitHeight: spacer.implicitHeight
            border.width: 2
            border.color: "white"
            color: "#e6e6e6"
            radius: 3
        }

        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 4

            Rectangle {
                width: progressBar.visualPosition * parent.width
                height: spacer.height
                border.width: 2
                border.color: "white"
                radius: 2
                color: "#17a81a"
                Text {
                    anchors.fill: parent
                    wrapMode: Text.NoWrap
                    text: "Downloading Tile: " + progressBar.value + " of " + progressBar.to
                    font.pointSize: (spacer.height ) * 0.5
                    leftPadding: 2

                }
            }
        }
    }
}

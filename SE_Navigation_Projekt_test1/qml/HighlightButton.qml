import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

Button {
    property color activeColor : "lightgreen"
    property color backgroundColor: "#E0E0E0"
    property color hoverColor: "lightblue"
    property bool activeCondition: false
    property color pressedColor: "#A2A2EE"
    id: button
    text: "HighlightButton"

    background: Rectangle {
        implicitWidth: button.width
        implicitHeight: button.height
        color: pressed ? pressedColor : aColor
    }
    property color bColor:  activeCondition ? activeColor : backgroundColor
    property color aColor:  hovered ? hoverColor : bColor

}

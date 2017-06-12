import QtQuick 2.7

MouseArea {
    property color activeColor : "lightgreen"
    property color backgroundColor: "white"
    property color hoverColor: "lightblue"
    property bool activeCondition: false
    property color itemColor :  pressed ? pressedColor : aColor
    property var bColor:  activeCondition ? activeColor : backgroundColor
    property bool mouseInArea : false
    property color pressedColor: "#A2A2EE"
    property color aColor:  mouseInArea ? hoverColor : bColor

    id: mArea
    hoverEnabled: true
    onEntered: {
        mouseInArea = true
    }
    onExited: {
        mouseInArea = false
    }
}

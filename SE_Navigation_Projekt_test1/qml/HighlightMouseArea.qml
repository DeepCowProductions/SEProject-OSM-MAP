import QtQuick 2.7

MouseArea {
    property color activeColor : "lightgreen"
    property color backgroundColor: "white"
    property color hoverColor: "lightblue"
    property bool activeCondition: false
    property color itemColor :  mouseInArea ? hoverColor : bColor
    property var bColor:  activeCondition ? activeColor : backgroundColor
    property bool mouseInArea : false

    id: mArea
    hoverEnabled: true
    onEntered: {
        mouseInArea = true
    }
    onExited: {
        mouseInArea = false
    }
}

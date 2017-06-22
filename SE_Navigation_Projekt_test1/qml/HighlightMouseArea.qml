import QtQuick 2.7

/* HighlightMouseArea.qml
 * Schoene version einer mouseArea.
 * Besitzt properties um 4 Farben darzustellen.
 * activeColor wird angezeigt wenn activeCondition auf true steht,
 * hoverColor wenn der Mousezeiger über der Area ist und
 * pressedColor wenn die Area gedrückt wird.
 * Falls nichts davon zutrifft wird backgroundColor angezeigt
 * Auf itemColor kann zugegriffen werden um die obige Farbconfiguration auf ein Item zu übertragen.
 * Die mouseArea an sich ist Farblos!
 */
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

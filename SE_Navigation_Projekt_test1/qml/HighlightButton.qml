import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

Button {
    property color activeColor : "lightgreen"
    property color backgroundColor: "#E0E0E0"
    property color hoverColor: "lightblue"
    property bool activeCondition: false

    id: button
    text: "HighlightButton"

    background: Rectangle {
        implicitWidth: button.width
        implicitHeight: button.height
        color: button.hovered ? hoverColor : button.bColor
    }
    property var bColor:  activeCondition ? activeColor : backgroundColor
}

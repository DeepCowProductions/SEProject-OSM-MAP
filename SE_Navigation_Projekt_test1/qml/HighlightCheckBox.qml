import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

CheckBox {

    property color backgroundColor: "white"
    property color hoverColor: "lightblue"
    property color pressedColor: "#A2A2EE"
    property color aColor:  hovered ? hoverColor : backgroundColor

    id:checkBox

    background: Rectangle {
        color: pressed ? pressedColor : aColor
    }

}

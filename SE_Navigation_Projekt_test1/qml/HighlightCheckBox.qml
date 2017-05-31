import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

CheckBox {

    property color backgroundColor: "white"
    property color hoverColor: "lightblue"

    id:checkBox

    background: Rectangle {
        color: checkBox.hovered ? hoverColor : backgroundColor
    }
}

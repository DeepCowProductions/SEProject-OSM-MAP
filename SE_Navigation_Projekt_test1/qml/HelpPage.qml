import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 2.1

Item {
    property alias backButton: backButton
    id: topParent

    Column{
        id:mainColumn
        anchors.fill: parent
        //            width: topParent.width
        //            height: topParent.height
        Row  {
            id: buttonRow
            width: parent.width
            height: 50
            spacing: 4
            Rectangle{
                width: parent.width * 0.6
                height: parent.height
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Help"
                    color: "darkblue"
                    font.family: "Helvetica"
                    font.pointSize: 24
                }
            }

            HighlightButton {
                id: backButton
                text: "Back"
                width: parent.width * 0.4
                height: parent.height
                contentItem: Image {
                    source: "qrc:/back"
                    fillMode: Image.PreserveAspectFit
                }
            }

        }

        HeaderSpacer {
            id: headerSpacer
        }

        Rectangle {
            width: parent.width
            height: parent.height - headerSpacer.height - buttonRow.height
            Flickable {
                anchors.fill: parent
                contentHeight: mainItemColumn.height
                contentWidth: mainItemColumn.width
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                ScrollBar.vertical: ScrollBar { }
                Column {
                    id: mainItemColumn
                    width: topParent.width
                    Row {
                        width: parent.width
                        height: 50

                        Rectangle{
                            width: parent.width
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: qsTr("Plugin Info")
                                color: "navy"
                                font.pointSize: 18
                            }
                        }
                    }
                    HeaderSpacer{
                        height: 1
                    }
                    Row {
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            Text{
                                wrapMode: TextField.Wrap
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: mapInstance.plugin.parameters[0].name
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                    }
                    Row {
                        width: parent.width
                        height: 100
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            TextField{
                                wrapMode: TextField.Wrap
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: mapInstance.plugin.parameters[0].value
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                    }
                    Row {
                        width: parent.width
                        height: 150
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            ListView {
                                width: parent.width
                                height: parent.height

                                FolderListModel {
                                    id: folderModel
                                    folder: "file://"+mapInstance.plugin.parameters[0].value
                                }

                                Component {
                                    id: fileDelegate
                                    Text { text: fileName }
                                }

                                model: folderModel
                                delegate: fileDelegate
                            }
                        }
                    }

                    HeaderSpacer{
                        height: 1
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        Keys.backPressed.connect(backButton.clicked)
        Keys.escapePressed.connect(backButton.clicked)
        forceActiveFocus()
    }
}

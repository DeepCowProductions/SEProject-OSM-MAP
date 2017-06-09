import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0


Item {
    property alias backButton: backButton
    id: topParent

    signal configurationChanged ()
    onConfigurationChanged:  {
        console.log("saving settings from qml")
        // instert new options here:
        settings.useOfflineMap = cb1.checked
        settings.useNormalMapCache = cb2.checked
        settings.offlineDirectory = offlineDirectory.text
        settings.maxOfflineMapSize = sizeOfOfflineDirectory.text * 1000000
        settings.save()
    }

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
                width: parent.width * 0.5
                height: parent.height
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Settings"
                    color: "darkblue"
                    font.family: "Helvetica"
                    font.pointSize: 24
                }
            }

            HighlightButton {
                id: backButton
                text: "Back"
                width: parent.width * 0.5
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
                            width: parent.width * 0.7
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: "Use Offline Map"
                                color: "navy"
                                font.pointSize: 12
                            }
                        }

                        HighlightCheckBox {
                            id: cb1
                            onCheckedChanged: configurationChanged()
                            checked: settings.useOfflineMap
                        }
                    }


                    Row {
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: "Use Map Cache"
                                color: "navy"
                                font.pointSize: 12
                            }
                        }

                        HighlightCheckBox {
                            id: cb2
                            onCheckedChanged: configurationChanged()
                            checked: settings.useNormalMapCache
                        }
                    }

                    Row {
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: "Max Storage Size(in MB)"
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        TextField {
                            id: sizeOfOfflineDirectory
                            width: parent.width * 0.25
                            inputMask: "9999"
                            text: settings.maxOfflineMapSize / 1000000
                            placeholderText: "Size in MB"
                            onEditingFinished: configurationChanged()
                        }
                    }
                    Row {
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: "Offline Directory"
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        TextField {
                            id: offlineDirectory
                            width: parent.width * 0.25
                            text: settings.offlineDirectory
                            placeholderText: "Path"
                            onEditingFinished: configurationChanged()
                        }
                    }

                    Row {
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: "Current offline size(in MB)"
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        TextField {
                            id: currentlyUsedSize
                            width: parent.width * 0.25
                            text: Math.round(((settings.usedOfflineDirectorySize / 1024) /1024) * 100) / 100
                            placeholderText: ""
                        }
                    }
                    Row {
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width * 0.7
                            height: parent.height
                        }
                    }


                }
                Component.onCompleted: {
                    Keys.backPressed.connect(backButton.clicked)
                    Keys.escapePressed.connect(backButton.clicked)
                    forceActiveFocus()
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

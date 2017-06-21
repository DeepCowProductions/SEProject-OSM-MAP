import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtPositioning 5.6
import QtLocation 5.6
import fhswf.se.nav.settings 1.0


Item {
    property alias backButton: backButton
    id: topParent

    signal deleteDirectory(string directory);
    signal configurationChanged ()

    onConfigurationChanged:  {
        console.log("saving settings from qml")
        // instert new options here:
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
                width: parent.width * 0.6
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
                                text: qsTr("Offline directory")
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
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: qsTr("Path to OfflineDirectory")
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        TextField {
                            id: pathToOfflineDirecory
                            width: parent.width * 0.25
                            text: settings.offlineDirectory
                            //                            enabled: false
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
                                text: qsTr("Max storage size(in MB)")
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        TextField {
                            id: sizeOfOfflineDirectory
                            width: parent.width * 0.25
                            inputMask: "9999"
                            text: settings.maxOfflineMapSize / 1000000
                            placeholderText: qsTr("Size in MB")
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
                                text: qsTr("Current offline size(in MB)")
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
                    ButtonGroup{
                        id: storageGroup
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
                                text: qsTr("SD-Card")
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        RadioButton{
                            id: sdCard
                            ButtonGroup.group: storageGroup
                            //                                checked: settings.
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
                                text: qsTr("Device storage")
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        RadioButton{
                            id: deviceStorage
                            ButtonGroup.group: storageGroup
                            checked: true
                            //                                checked: settings.
                        }
                    }
                    Row{
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width
                            height:  parent.height
                            Button{
                                id: clearOfflineDirectory
                                anchors.leftMargin: 10
                                anchors.rightMargin: 10
                                anchors.topMargin: 5
                                anchors.bottomMargin: 5

                                width: parent.width
                                anchors.fill: parent
                                text: qsTr("Clear offline directory")
                                onClicked: deleteDirectory("offline")
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
                            width: parent.width
                            height: parent.height
                            Text{
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: qsTr("Cache directory")
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
                                anchors.leftMargin: 10
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                text: qsTr("Current cache size(in MB)")
                                color: "navy"
                                font.pointSize: 12
                            }
                        }
                        TextField {
                            id: currentlyCacheUsedSize
                            width: parent.width * 0.25
                            text: Math.round(((settings.usedOfflineDirectorySize / 1024) /1024) * 100) / 100
                            placeholderText: ""
                        }
                    }
                    Row{
                        width: parent.width
                        height: 50
                        Rectangle{
                            width: parent.width
                            height:  parent.height
                            Button{
                                id: clearCacheDirectory
                                anchors.leftMargin: 10
                                anchors.rightMargin: 10
                                anchors.topMargin: 5
                                anchors.bottomMargin: 5

                                width: parent.width
                                anchors.fill: parent
                                text: qsTr("Clear Cache directory")
                                onClicked: {
                                    deleteDirectory("cache")
                                    deleteDirectory("genericcache")
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
        }
    }
    Component.onCompleted: {
        Keys.backPressed.connect(backButton.clicked)
        Keys.escapePressed.connect(backButton.clicked)
        forceActiveFocus()
    }
}

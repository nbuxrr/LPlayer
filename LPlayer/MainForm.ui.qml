import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480
    property alias btn_next: btn_next
    property alias btn_play: btn_play
    property alias btn_pre: btn_pre

    RowLayout {
        id: rowLayout1
        anchors.fill: parent

        ListView {
            id: listView1
            x: 0
            y: 0
            width: 110
            height: 160
            visible: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }
            }
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }

        ColumnLayout {
            id: vl_mianarea
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Rectangle {
                id: player
                width: 200
                height: 200
                color: "#000000"
                border.width: 0
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            RowLayout {
                id: hl_progress
                width: 100
                height: 100

                Slider {
                    id: sld_playprogress
                    Layout.fillWidth: true
                }

                Label {
                    id: lbl_playtime
                    text: qsTr("时间")
                }

                Button {
                    id: btn_speed
                    text: qsTr("速度")
                }
            }

            RowLayout {
                id: hl_playctrls
                height: 50
                Layout.fillWidth: true

                Button {
                    id: btn_pre
                    text: "<-"
                }

                Button {
                    id: btn_play
                    text: qsTr("Play")
                }

                Button {
                    id: btn_next
                    text: qsTr("->")
                }

                Button {
                    id: btn_novoice
                    text: qsTr("音量")
                }

                Slider {
                    id: sld_voice
                    width: 50
                }

                Button {
                    id: btn_fullscreen
                    text: qsTr("全屏")
                }


            }




        }
    }
}

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480
    property alias btn_next: btn_next
    property alias btn_play: btn_play
    property alias btn_pre: btn_pre
    property alias btn_list: btn_list
    property alias lst_files: lst_files
    
    RowLayout {
        id: hl_client
        anchors.fill: parent

        // 播放列表
        ListView {
            id: lst_files
            x: 0
            y: 0
            width: 120
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

            // 播放画面
            Rectangle {
                id: player
                color: "#000000"
                border.width: 0
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            
            // 进度控制
            RowLayout {
                id: hl_progress
                Layout.fillWidth: true
                Layout.fillHeight: true
                Slider {
                    id: sld_playprogress
                    Layout.fillWidth: true
                }

                Label {
                    id: lbl_playtime
                    //Layout.fillWidth: true
                    text: qsTr("00:59:59")
                }
            }

            // 播放控制
            RowLayout {
                id: hl_playctrls
                height: 50
                Layout.fillWidth: true

                Button {
                    id: btn_list
                    Layout.fillWidth: true
                    text: qsTr("列表")
                    Layout.maximumWidth: 60
                }

                Button {
                    id: btn_pre
                    Layout.fillWidth: true
                    text: "<-"
                    Layout.maximumWidth: 60
                }

                Button {
                    id: btn_play
                    Layout.fillWidth: true
                    text: qsTr("播放")
                    Layout.maximumWidth: 60                    
                }

                Button {
                    id: btn_next
                    Layout.fillWidth: true
                    text: qsTr("->")
                    Layout.maximumWidth: 60                    
                }

                Rectangle {
                    id: space
                    height: 0
                    border.width: 0                    
                    Layout.fillWidth: true
                }
                
                Button {
                    id: btn_novoice
                    Layout.fillWidth: true
                    text: qsTr("静音")
                    Layout.maximumWidth: 60                    
                }

                Slider {
                    id: sld_voice
                    Layout.fillWidth: true
                    Layout.maximumWidth: 100                    
                }

                Button {
                    id: btn_speed
                    Layout.fillWidth: true
                    text: qsTr("速度")
                    Layout.maximumWidth: 60                    
                }

                Button {
                    id: btn_fullscreen
                    Layout.fillWidth: true
                    text: qsTr("全屏")
                    Layout.maximumWidth: 60                    
                }




            }




        }
    }
}

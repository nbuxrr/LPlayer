import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
//import QtMultimedia 5.4
import vlc.qml.Controls 1.0
import QtQuick.Controls.Styles 1.4

Item {
    width: 640
    height: 480
  
    property alias lst_files: lst_files
    property alias vlcplayer: vlcplayer
    property alias sld_playprogress: sld_playprogress
    property alias ma_sld_palyprogress: ma_sld_palyprogress
    property alias btn_list: btn_list
    property alias btn_pre: btn_pre
    property alias btn_play: btn_play
    property alias btn_next: btn_next
    property alias btn_novoice: btn_novoice
    property alias sld_voice: sld_voice
    property alias btn_speed: btn_speed
    property alias ma_player: ma_player
    property alias btn_file: btn_file
    property alias lbl_lasttime: lbl_lasttime

    RowLayout {
        id: hl_client
        anchors.fill: parent

        // 播放列表
        ListView {
            id: lst_files
            x: 0
            y: 0
            width: 120
            visible: false
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
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
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

				QMLVLCItem {
					id: vlcplayer
					Layout.fillHeight: true
					Layout.fillWidth: true
					anchors.fill: parent

                    MouseArea{
                        id: ma_player;
                        anchors.fill: parent;
                        hoverEnabled: true;

                        onEntered: rt_playctrls.visible = btn_list.visible = true;
                        onExited:  rt_playctrls.visible = btn_list.visible = false;

                        Button {
                            id: btn_list;
                            opacity: 0.4;
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.left: parent.left;
                            width: 10;
                            height: 100;
                            text: qsTr(">");
                        }


                        // 播放控制
                        Rectangle {
                            id: rt_playctrls;
                            radius: 5;
                            width: parent.width - 40;
                            height: 50;
                            opacity: 0.8;
                            color: "gray";
                            anchors.horizontalCenter: parent.horizontalCenter;
                            anchors.bottom: parent.bottom;
                            anchors.bottomMargin: 5;


							// 进度控制
							MouseArea
							{
								id: ma_sld_palyprogress;
								width: parent.width;
								height: 10;
								anchors.verticalCenter: parent.top;

								Slider {
									id: sld_playprogress;
									width: parent.width;
									height: parent.height;
									anchors.top: parent.top;
									minimumValue: 0;
									maximumValue: 1000000;
									stepSize: 1.0

									style: SliderStyle {
										groove: Rectangle {
											implicitWidth: 200
											implicitHeight: 3
											color: "white"
											radius: 2;

											Rectangle {
												anchors.left: parent.left;
												anchors.top: parent.top;
												anchors.bottom: parent.bottom;
												radius: 2;
												width: parent.width * control.value/control.maximumValue;
												color: "#1FA8DE";
											}
										}

										handle: Rectangle {
											id: hdl_block;
											anchors.centerIn: parent
											color: control.pressed ? "white" : "lightgray"
											border.color: "white"
											border.width: 2
											implicitWidth: (control.pressed || control.hovered)? 16:12
											implicitHeight: (control.pressed || control.hovered)? 16:12
											radius: (control.pressed || control.hovered)? 8:6
										}
									}
								}
							}

                            Button {
                                id: btn_play;
                                width: pressed? 35:(hovered? 45:40);
                                height: pressed? 35:(hovered? 45:40);
                                anchors.centerIn: parent;
                                checkable: true;
                                checked: true;
								iconSource: checked? "rsc/btn_play_pause.png" : "rsc/btn_play_play.png"
                                tooltip: checked? "播放":"暂停";

								style: ButtonStyle {
									background: Rectangle {
										color: "transparent"
										border.width: 0
									}
								}
                            }

                            Button {
                                id: btn_pre;
                                width: pressed? 25:(hovered? 35:30);
                                height: pressed? 25:(hovered? 35:30);
                                anchors.right: btn_play.left;
                                anchors.verticalCenter: btn_play.verticalCenter;
								iconSource: "rsc/btn_pre.png";
                                //tooltip: "<-";

								style: ButtonStyle {
									background: Rectangle {
										color: "transparent"
										border.width: 0
									}
								}
                            }

                            Button {
                                id: btn_file;
                                width: pressed? 30:(hovered? 35:30);
                                height: pressed? 30:(hovered? 35:30);

								anchors.left: sld_voice.right;
                                anchors.leftMargin: 20
                                anchors.verticalCenter: btn_play.verticalCenter;
								iconSource: "rsc/btn_file.png"
                                tooltip: "打开";

								style: ButtonStyle {
									background: Rectangle {
										color: "transparent"
										border.width: 0;
									}
								}
                            }

                            Button {
                                id: btn_next;
								width: pressed? 25:(hovered? 35:30);
                                height: pressed? 25:(hovered? 35:30);
                                anchors.left: btn_play.right;
                                anchors.verticalCenter: btn_play.verticalCenter;
								iconSource: "rsc/btn_next.png";
                                //tooltip: qsTr("->");
								
								style: ButtonStyle {
									background: Rectangle {
										color: "transparent"
										border.width: 0
									}
								}
                            }

                            Button {
                                id: btn_novoice
                                width: 20;
                                height: 20;
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.verticalCenter: btn_play.verticalCenter;
                                checkable: true
                                checked: false
                                iconSource: btn_novoice.checked? "rsc/btn_voice_off.png" : "rsc/btn_voice_on.png"
                                tooltip: "静音"

								style: ButtonStyle {
									background: Rectangle {
										color: "transparent"
										border.width: 0
									}
								}
                            }

                            Slider {
                                id: sld_voice;
                                width: 50;
                                height: 3;
                                anchors.left: btn_novoice.right;
                                anchors.leftMargin: 5;
                                anchors.verticalCenter: btn_play.verticalCenter;
                                updateValueWhileDragging: true;
                                value: 100;
                                minimumValue: 0;
                                maximumValue: 300;
                                stepSize: 1.0

                                style: SliderStyle {
                                    groove: Rectangle {
                                        implicitWidth: 80
                                        implicitHeight: 3
                                        color: "white"
                                        radius: 2
                                    }

                                  handle: Rectangle {
                                      anchors.centerIn: parent
                                      color: control.pressed ? "white" : "lightgray"
                                      border.color: "white"
                                      border.width: 2
                                      implicitWidth: (control.pressed || control.hovered)? 12:10
                                      implicitHeight: (control.pressed || control.hovered)? 12:10
                                      radius: (control.pressed || control.hovered)? 6:5
                                  }
                              }
                            }

                            Button {
                                id: btn_speed
                                width: 20
                                height: 20
                                anchors.right: parent.right;
                                anchors.rightMargin: 50
                                anchors.verticalCenter: btn_play.verticalCenter;
                                tooltip: "速度"

								style: ButtonStyle {
									background: Rectangle {
										color: "transparent"
										border.width: 0
									}
								}
                            }

                            Label {
                                  id : lbl_lasttime;
                                  anchors.top : ma_sld_palyprogress.bottom;
                                  anchors.right : ma_sld_palyprogress.right;
                                  anchors.rightMargin: 2
								  color: "white"
                                  text : "00:00:00"
                            }
                        }
                    }
                }
            }
        }
    }
}

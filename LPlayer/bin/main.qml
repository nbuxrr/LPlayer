import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: app_wnd
    visible: true
    width: 416
    height: 234
    title: qsTr("好好学习 天天向上")
    minimumWidth: 416
    minimumHeight: 234

    /*
    menuBar: MenuBar {
        Menu {
            title: qsTr("文件")
            MenuItem {
                text: qsTr("&打开")
                onTriggered: file_dlg.open();
            }
            MenuItem {
                text: qsTr("退出")
                onTriggered: Qt.quit();
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("测试弹出窗口")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
    */
        
    MainForm {
        id: main_form
        anchors.fill: parent
        property variant previousPosition;

        // 按钮响应函数
        btn_file.onClicked: onBtnOpenFile();
        btn_list.onClicked: onBtnShowList();
        btn_pre.onClicked: onBtnPre();
        btn_play.onClicked: onBtnPlay();
        btn_next.onClicked: onBtnNext();
        btn_novoice.onClicked: onBtnNoVoice();
        sld_voice.onValueChanged: onSldVolumeValueChanged();
        vlcplayer.onSigPlayingProgressRefresh: onPlayingRefresh(iProgress, iLength, qstrCurTime, qstrLastTime);
        sld_playprogress.onPressedChanged: vlcplayer.setPlayPos(sld_playprogress.value);

        ma_player.onPressed:
        {
            console.log("onPressed");
            previousPosition = Qt.point(ma_player.mouseX, ma_player.mouseY);
        }

        ma_player.onPositionChanged:
        {
            console.log("OnPositionChanged", app_wnd.x, app_wnd.y, previousPosition.x, previousPosition.y);

            if (ma_player.pressedButtons == Qt.LeftButton && app_wnd.visibility != 5)
            {
                app_wnd.x = app_wnd.x + ma_player.mouseX - previousPosition.x;
                app_wnd.y = app_wnd.y + ma_player.mouseY - previousPosition.y;
            }
        }

        ma_player.onDoubleClicked:
        {
            console.log("onDoubleClicked");
            if (app_wnd.visibility != 5)
            {
                app_wnd.showFullScreen();
            }
            else
            {
                app_wnd.showNormal();
            }
        }

        function onBtnShowList()
        {
            lst_files.visible = !lst_files.visible;
            btn_list.text = lst_files.visible? qsTr("<") : qsTr(">");
        }
        
        function onBtnOpenFile() {file_dlg.open();}

        function onBtnPre(){}
      
        function onBtnPlay()
        {
            vlcplayer.setPause(btn_play.checked);
        }

        function onBtnNext(){}

        function onBtnNoVoice()
        {
            vlcplayer.setVolume(btn_novoice.checked? 0 : sld_voice.value);
        }

        function onSldVolumeValueChanged()
        {
            vlcplayer.setVolume(sld_voice.value);

            if (sld_voice.value == 0 && !btn_novoice.checked) {
                btn_novoice.checked = true;
            } else if (sld_voice.value != 0 && btn_novoice.checked) {
                btn_novoice.checked = false;
            }
        }

        function onPlayingRefresh(iProgress, iLength, qstrCurTime, qstrLastTime)
        {
            sld_playprogress.maximumValue = iLength;
            sld_playprogress.value = iProgress;
            lbl_lasttime.text = qstrLastTime;
        }

        function onBtnSpeed(){}
        function onBtnFullScreen(){}

        function play(FilePath)
        {
            console.log("播放文件：", FilePath); 
            vlcplayer.playFile(FilePath);
            btn_play.checked = false;
        }
    }

    FileDialog
    {
        id: file_dlg
        title: "选择文件"
        property string strFilePath: ""
        property string strFileName: ""

        onAccepted: {
            strFilePath = file_dlg.fileUrls[0].toString();
            console.log("选择了1: ", file_dlg.fileUrls[0].toString());
            main_form.play(strFilePath);
        }
        onRejected: {
            console.log("取消了选择");
        }
    }
}

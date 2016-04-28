import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: app_wnd
    visible: true
    width: 640
    height: 480
    title: qsTr("好好学习 天天向上")
    minimumWidth: 320
    minimumHeight: 240

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

        // 按钮响应函数
        btn_list.onClicked: onBtnShowList()
        btn_pre.onClicked: onBtnPre()
        btn_play.onClicked: onBtnPlay()
        btn_next.onClicked: onBtnNext()

        function onBtnShowList()
        {
            lst_files.visible = !lst_files.visible

            if (lst_files.visible)
            {
                btn_list.text = qsTr("<")
                width += lst_files.width;
                height += lst_files.height;
            }
            else
            {
                btn_list.text = qsTr(">")
                width -= lst_files.width;
                height -= lst_files.height;
            }
            
        }
        

        function onBtnPlay(){file_dlg.open();}
        function onBtnPre(){}
        function onBtnNext(){}
        function onBtnNoVoice(){}
        function onSldVoice(){}
        function onBtnSpeed(){}
        function onBtnFullScreen(){}

        function play(FilePath)
        {
            console.log("播放文件：", FilePath);
            mediaPlayer.stop();
            mediaPlayer.source = FilePath;
            mediaPlayer.play();
            btn_play.text = qsTr("暂停");
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
            console.log("选择了1: ", file_dlg.fileUrls[0].toString())
            main_form.play(strFilePath);
        }
        onRejected: {
            console.log("取消了选择")
        }
    }
}

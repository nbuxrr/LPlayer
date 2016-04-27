import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("好好学习 天天向上")

    /*
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
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
        anchors.fill: parent
        btn_play.onClicked: play(qsTr("FileName"))
        //btn_next.onClicked: messageDialog.show(qsTr("下一个"))
        //btn_pre.onClicked: messageDialog.show(qsTr("前一个"))
        btn_list.onClicked: lst_files.visible = !lst_files.visible
    
        function onBtnPlay(){}
        function onBtnPre(){}
        function onBtnNext(){}
        function onBtnNoVoice(){}
        function onSldVoice(){}
        function onBtnSpeed(){}
        function onBtnFullScreen(){}

        function play(FileName) 
        {
            if (btn_play.text == qsTr("播放"))
            {
                btn_play.text = qsTr("暂停");                
            }
            else
            {
                btn_play.text = qsTr("播放");      
            }
        }
    
    }


}

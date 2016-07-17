//*************************************************************************
//	filename: main.cpp    create-time: 2016-7-17 15:30:25
//	author: xurr
//	note: LPlayer播放器，基于QML + C++ + VLC实现的一个播放器Demo		
//*************************************************************************
#include "AppLPlayer.h"
#include <QtQml>
#include <QMessageBox>
#include "QMLVLCItem.h"

CAppLPlayer *g_app = NULL;

int main(int argc, char *argv[])
{
    CAppLPlayer app(argc, argv);
	qInstallMessageHandler(customMessageHandler);
	qmlRegisterType<CQMLVLCItem>("vlc.qml.Controls", 1, 0, "QMLVLCItem");
	qRegisterMetaType<string>("string");

	g_app = &app;
	
	if (!g_app->InitApp())
	{
		QMessageBox::warning(NULL, "LPalyer", "App init failed!", QMessageBox::Close, QMessageBox::Close);
		return 0;
	}

	QString qstrQmlFile;
	g_app->GetMainQmlPath(qstrQmlFile);

	QQmlApplicationEngine qmlEngine;
	qmlEngine.load(qstrQmlFile);
	QList<QObject*> qlstObjs = qmlEngine.rootObjects();
	
	if (qlstObjs.size() <= 0)
	{
		QMessageBox::warning(NULL, "LPalyer", "Load UI failed!", QMessageBox::Close, QMessageBox::Close);
		return 0;
	}
		
	return app.exec();
}
#include "AppLPlayer.h"
#include <Qtqml/QQmlApplicationEngine>
#include <QDebug>
#include <QFile>
#include <QTime> 
#include <QtQml>
#include "QMLVLCItem.h"
#include "CommFunc.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


CAppLPlayer *g_app = NULL;

int main(int argc, char *argv[])
{
    CAppLPlayer app(argc, argv);
	g_app = &app;

	qInstallMessageHandler(customMessageHandler);
	CommFunc::SetExecDir(QCoreApplication::applicationDirPath().toStdString());
    QTRACE("当前文件路径: %s\n", QCoreApplication::applicationDirPath().toStdString().c_str());

    qmlRegisterType<CQMLVLCItem>("vlc.qml.Controls", 1, 0, "QMLVLCItem");

    QString qstrQmlFile(CommFunc::GetExecDir());

#ifdef WIN32
    qstrQmlFile += "/main.qml";
    qstrQmlFile.replace("/", "\\");
#else
    qstrQmlFile = "main.qml";
#endif

    QQmlApplicationEngine engine;
	engine.load(qstrQmlFile);

	QList<QObject*> qlstObjs = engine.rootObjects();
	
	if (qlstObjs.size() <= 0)
	{
		return 0;
	}
	
	return app.exec();
}


void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	string strLevel;

	switch (type)
	{
	case QtDebugMsg:
		strLevel = "Debug:";
		break;
	case QtWarningMsg:
		strLevel = "Warning:";
		break;
	case QtCriticalMsg:
		strLevel = "Critical:";
		break;
	case QtFatalMsg:
		strLevel = "Fatal:";
		abort();
		break;
	}

	QTRACE("%s %s %s	%s - %d - %s\n"
		, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toLocal8Bit().constData()
		, strLevel.c_str()
		, msg.toLocal8Bit().constData()
		, QString(context.file).toLocal8Bit().constData(), context.line, context.function);
}

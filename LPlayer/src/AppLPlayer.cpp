/************************************************************************/
/* 
*/
/************************************************************************/
#include "AppLPlayer.h"
#include <QTextCodec>
#include <QTime>
#include "vlc/libvlc.h"


CAppLPlayer::CAppLPlayer(int &argc, char **argv, int iflag/* = ApplicationFlags*/)
: QApplication(argc, argv, iflag)
, m_pVlcInstance(NULL)
{
	m_pVlcInstance = libvlc_new(0, NULL);
}


CAppLPlayer::~CAppLPlayer()
{
	QTRACE("TRACE: %s\n", __FUNCTION__);

	libvlc_release(m_pVlcInstance);
}

bool CAppLPlayer::InitApp()
{
	CommFunc::SetAppFileDir(QCoreApplication::applicationDirPath().toStdString());
	QTRACE("程序所在目录: %s\n", QCoreApplication::applicationDirPath().toStdString().c_str());

	return true;
}

const QString& CAppLPlayer::GetMainQmlPath(QString &qstrQmlFile)
{
#ifdef WIN32
	qstrQmlFile = (CommFunc::GetAppFileDir() + "/main.qml").c_str();
	qstrQmlFile.replace("/", "\\");
#else
	qstrQmlFile = "main.qml";
#endif

	return qstrQmlFile;
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


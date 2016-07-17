#ifndef _APPLPLAYER_H_
#define _APPLPLAYER_H_

#include <QtWidgets/QApplication>
#include "CommFunc.h"

struct libvlc_instance_t;


class CAppLPlayer : public QApplication
{
public:
	CAppLPlayer(int &argc, char **argv, int iflag = ApplicationFlags);
	virtual ~CAppLPlayer();

	bool InitApp();
	const QString& GetMainQmlPath(QString &qstrQmlFile);

public:
	libvlc_instance_t *m_pVlcInstance;
};

extern CAppLPlayer *g_app;
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // _APPLPLAYER_H_




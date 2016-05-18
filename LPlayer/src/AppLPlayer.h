#ifndef _APPLPLAYER_H_
#define _APPLPLAYER_H_

#include <QtWidgets/QApplication>
#include "vlc/libvlc.h"

class CAppLPlayer : public QApplication
{
public:
	CAppLPlayer(int &argc, char **argv, int iflag = ApplicationFlags);
	virtual ~CAppLPlayer();

public:
	libvlc_instance_t *m_pVlcInstance;

};

extern CAppLPlayer *g_app;

#endif // _APPLPLAYER_H_




/************************************************************************/
/* 
*/
/************************************************************************/
#include "AppLPlayer.h"
#include "vlc/libvlc.h"



CAppLPlayer::CAppLPlayer(int &argc, char **argv, int iflag/* = ApplicationFlags*/)
: QApplication(argc, argv, iflag)
, m_pVlcInstance(NULL)
{
	m_pVlcInstance = libvlc_new(0, NULL);

}


CAppLPlayer::~CAppLPlayer()
{
	libvlc_release(m_pVlcInstance);
}



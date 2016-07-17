//*************************************************************************
//	filename: QMLVLCItem.cpp    create-time: 2016-5-8 10:36:00
//	author: nbuxrr
//	note: 使用VLC播放的QML组件	
//*************************************************************************
#include "QMLVLCItem.h"
#include "AppLPlayer.h"
#include "vlc/libvlc.h"
#include "vlc/libvlc_media.h"
#include "vlc/libvlc_media_player.h"
#include <QPainter>

#define FRAME_WIDTH 1080
#define FRAME_HEIGHT 720
#define FRAME_BUF_SIZE (FRAME_WIDTH * FRAME_HEIGHT * 4)

CQMLVLCItem::CQMLVLCItem(QQuickItem *parent/* = NULL*/)
: QQuickPaintedItem(parent)
, m_pVLCMediaPlayer(NULL)
, m_pFrameDecodeBuf(NULL)
, m_pFrameDrawBuf(NULL)
, m_iFrameWidth(-1)
, m_iFrameHeight(-1)
{
	m_pFrameDecodeBuf = new uchar[FRAME_BUF_SIZE];
	memset(m_pFrameDecodeBuf, 0, FRAME_BUF_SIZE);
	m_pFrameDrawBuf = new uchar[FRAME_BUF_SIZE];
	memset(m_pFrameDrawBuf, 0, FRAME_BUF_SIZE);
	
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(SlotTimeOut()));
}


CQMLVLCItem::~CQMLVLCItem()
{
	if (m_pVLCMediaPlayer != NULL)
	{
		libvlc_media_player_stop(m_pVLCMediaPlayer);
		libvlc_media_player_release(m_pVLCMediaPlayer);	// 释放播放器 Free the media_player
	}

	if (m_pFrameDecodeBuf != NULL)
	{
		delete []m_pFrameDecodeBuf;
		m_pFrameDecodeBuf = NULL;
	}
}

void CQMLVLCItem::paint(QPainter *painter)
{
	if (m_iFrameWidth != -1	&& m_iFrameHeight != -1)
	{
		m_FrameMutex.lock();
		memcpy(m_pFrameDrawBuf, m_pFrameDecodeBuf, FRAME_BUF_SIZE);
		m_FrameMutex.unlock();

		QRect rct(0, 0, width(), height());
		QTRACE("windows w = %d, h = %d\n", rct.width(), rct.height());
		
		double fwr = (double)rct.width() / (double)m_iFrameWidth;
		double fhr = (double)rct.height() / (double)m_iFrameHeight;

		if (fwr - fhr > 0.00000001)
		{
			int iNewW = fhr * m_iFrameWidth;
			rct.setX((rct.width() - iNewW) / 2);
			rct.setWidth(iNewW);
		}
		else
		{
			int iNewH = fwr * m_iFrameHeight;
			rct.setY((rct.height() - iNewH) / 2);
			rct.setHeight(iNewH);
		}

		painter->drawImage(rct, QImage(m_pFrameDrawBuf, FRAME_WIDTH, FRAME_HEIGHT, QImage::Format_RGBA8888));
	}
}

void CQMLVLCItem::playFile(const QString &qstrFile)
{
	QTRACE("%s\n", __FUNCTION__);
	SetCurPath(qstrFile);
	play();
}

void CQMLVLCItem::SetCurPath(const QString &qstrPath)
{
	QString qstrtmp = qstrPath;

#ifdef WIN32
	qstrtmp.replace("/", "\\");
	qstrtmp.replace("file:\\\\\\", "file:///");
#endif

	m_strMediaPath = qstrtmp.toStdString();
}

void CQMLVLCItem::play()
{
	QTRACE("%s\n", __FUNCTION__);

	if (m_timer.isActive())
	{
		m_timer.stop();
	}

	if (m_strMediaPath.empty())
	{
		QTRACE("current file path is empty\n");
		return;
	}

	if (m_pVLCMediaPlayer != NULL)
	{
		libvlc_media_player_stop(m_pVLCMediaPlayer);
		libvlc_media_player_release(m_pVLCMediaPlayer);	// 释放播放器 Free the media_player
	}

	//libvlc_media_t *tmpMedia = libvlc_media_new_location (g_app->m_pVlcInstance, "file:///F:\\movie\\cuc_ieschool.flv");  
	//libvlc_media_t *tmpMedia = libvlc_media_new_location (g_app->m_pVlcInstance, "screen://");  //Screen Capture  
	//libvlc_media_t *tmpMedia = libvlc_media_new_path(g_app->m_pVlcInstance, m_strMediaPath.c_str());
	libvlc_media_t *tmpMedia  = libvlc_media_new_location(g_app->m_pVlcInstance, m_strMediaPath.c_str());

	if (tmpMedia != NULL)
	{
		m_pVLCMediaPlayer = libvlc_media_player_new_from_media(tmpMedia);
		libvlc_media_release(tmpMedia);		/* No need to keep the media now */
		
		if (m_pVLCMediaPlayer != NULL)
		{
			memset(m_pFrameDecodeBuf, 0, FRAME_BUF_SIZE);
			memset(m_pFrameDrawBuf, 0, FRAME_BUF_SIZE);
			update();

			libvlc_video_set_callbacks(m_pVLCMediaPlayer, CQMLVLCItem::CallBackLock, CQMLVLCItem::CallBackUnLock, CQMLVLCItem::CallBackDisplay, this);
			libvlc_video_set_format(m_pVLCMediaPlayer, "RGBA", FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH * 4);

			m_iFrameWidth = -1;
			m_iFrameHeight = -1;
			m_timer.start(45);
			libvlc_media_player_play(m_pVLCMediaPlayer);
		} 
		else
		{
			QTRACE("err: %s - %d\n", __FUNCTION__, __LINE__);
		}
	}
	else
	{
		QTRACE("err: %s - %d\n", __FUNCTION__, __LINE__);
	}
}


void CQMLVLCItem::setPause(bool bPause)
{
	if (m_pVLCMediaPlayer != NULL)
	{
		QTRACE("bPause: %d\n", bPause);
		libvlc_media_player_set_pause(m_pVLCMediaPlayer, bPause);
	}
}

void CQMLVLCItem::setPlayPos(int iPos)
{
	if (m_pVLCMediaPlayer != NULL)
	{
		QTRACE("%s %d / %d\n", __FUNCTION__, iPos, libvlc_media_player_get_length(m_pVLCMediaPlayer));

		m_FrameMutex.lock();
		libvlc_media_player_set_time(m_pVLCMediaPlayer, iPos);
		m_FrameMutex.unlock();
	}
}

void CQMLVLCItem::setVolume(int iNum)
{
	QTRACE("%s %d\n", __FUNCTION__, iNum);

	if (m_pVLCMediaPlayer != NULL)
	{
		libvlc_audio_set_volume(m_pVLCMediaPlayer, max(iNum, 0));
	}
}

void CQMLVLCItem::stop()
{
	QTRACE("%s\n", __FUNCTION__);

	if (m_pVLCMediaPlayer != NULL)
	{
		libvlc_media_player_stop(m_pVLCMediaPlayer);
	}
}

void* CQMLVLCItem::Lock(vdss &planes)
{
	m_iFrameWidth = libvlc_video_get_width(m_pVLCMediaPlayer);
	m_iFrameHeight = libvlc_video_get_height(m_pVLCMediaPlayer);
	QTRACE("TRACE: %d, %d\n", m_iFrameWidth, m_iFrameHeight);

	m_FrameMutex.lock();
	//memset(m_pFrameDecodeBuf, 0, FRAME_BUF_SIZE);
	*planes = m_pFrameDecodeBuf;

	return NULL;
}

void CQMLVLCItem::UnLock(void * /*picture*/, void *const * /*planes*/)
{
	m_FrameMutex.unlock();
}

void CQMLVLCItem::Display(void * /*picture*/)
{
	//QEvent *pEvt = new QEvent(QEvent::Paint);
	//QCoreApplication::postEvent(this, pEvt);
}

void* CQMLVLCItem::CallBackLock(void *opaque, void **planes)
{
	CQMLVLCItem *p = static_cast<CQMLVLCItem *>(opaque);
	
	if (p != NULL)
	{
		p->Lock(planes);
	}

	return NULL;
}

void CQMLVLCItem::CallBackUnLock(void *opaque, void *picture, void *const *planes)
{
	CQMLVLCItem *p = static_cast<CQMLVLCItem *>(opaque);

	if (p != NULL)
	{
		p->UnLock(picture, planes);
	}
}

void CQMLVLCItem::CallBackDisplay(void *opaque, void *picture)
{
	CQMLVLCItem *p = static_cast<CQMLVLCItem *>(opaque);

	if (p != NULL)
	{
		p->Display(picture);
	}
}

void CQMLVLCItem::SlotTimeOut()
{
	update();

	static int i = 0;
	
	if ((i = (++i) % 10) == 0)
	{
		if (m_pVLCMediaPlayer != NULL)
		{
			int iLength = libvlc_media_player_get_length(m_pVLCMediaPlayer);

			if (iLength > 0)
			{
				int icurtime = libvlc_media_player_get_time(m_pVLCMediaPlayer);
				
				int iCurSeconds = icurtime / 1000;
				int iLastSeconds = (iLength - icurtime) / 1000;
				QString qstrCurTime;
				QString qstrLastTime;
				qstrCurTime.sprintf("%d:%02d:%02d", iCurSeconds / 3600, (iCurSeconds / 60) % 60, iCurSeconds % 60);
				qstrLastTime.sprintf("%d:%02d:%02d", iLastSeconds / 3600, (iLastSeconds / 60) % 60, iLastSeconds % 60);
				QTRACE("playing %s, %s\n", qstrCurTime.toStdString().c_str(), qstrLastTime.toStdString().c_str());

				emit sigPlayingProgressRefresh(icurtime, iLength, qstrCurTime, qstrLastTime);
			}
		}
	}
}







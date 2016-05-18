//*************************************************************************
//	filename: QMLVLCItem.cpp    create-time: 2016-5-8 10:36:00
//	author: nbuxrr
//	note: 使用VLC播放的QML组件	
//*************************************************************************
#include "QMLVLCItem.h"
#include "AppLPlayer.h"
#include "CommFunc.h"
#include "vlc/libvlc.h"
#include "vlc/libvlc_media.h"
#include "vlc/libvlc_media_player.h"
#include <QPainter>

#define FRAME_WIDTH 1080
#define FRAME_HEIGHT 720

CQMLVLCItem::CQMLVLCItem(QQuickItem *parent/* = NULL*/)
: QQuickPaintedItem(parent)
, m_pMediaPlayCtrl(NULL)
, m_pFrameBuf(NULL)
, m_pFrameDraw(NULL)
{
	m_pFrameBuf = new uchar[FRAME_WIDTH * FRAME_HEIGHT * 4];
	memset(m_pFrameBuf, 0, FRAME_WIDTH * FRAME_HEIGHT * 4);
	m_pFrameDraw = new uchar[FRAME_WIDTH * FRAME_HEIGHT * 4];
	memset(m_pFrameDraw, 0, FRAME_WIDTH * FRAME_HEIGHT * 4);
	
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(SlotTimeOut()));
}


CQMLVLCItem::~CQMLVLCItem()
{
	if (m_pMediaPlayCtrl != NULL)
	{
		libvlc_media_player_stop(m_pMediaPlayCtrl);
		libvlc_media_player_release(m_pMediaPlayCtrl);	// 释放播放器 Free the media_player
	}

	if (m_pFrameBuf != NULL)
	{
		delete []m_pFrameBuf;
		m_pFrameBuf = NULL;
	}
}

void CQMLVLCItem::SetCurPath(const QString &qstrPath)
{
	QString qstrtmp = qstrPath;
	qstrtmp.replace("/", "\\");
	qstrtmp.replace("file:\\\\\\", "file:///");

	m_strCurPath = qstrtmp.toStdString();
}


void CQMLVLCItem::paint(QPainter *painter)
{
	//QTRACE("%s\n", __FUNCTION__);
	m_FrameMutex.lock();
	memcpy(m_pFrameDraw, m_pFrameBuf, FRAME_WIDTH * FRAME_HEIGHT * 4);
	m_FrameMutex.unlock();

	painter->drawImage(QRect(0, 0, width(), height()), QImage(m_pFrameDraw, FRAME_WIDTH, FRAME_HEIGHT, QImage::Format_RGBA8888));
}

void CQMLVLCItem::play()
{
	QTRACE("%s\n", __FUNCTION__);

	if (m_timer.isActive())
	{
		m_timer.stop();
	}

	if (m_strCurPath.empty())
	{
		QTRACE("current file path is empty\n");
		return;
	}

	if (m_pMediaPlayCtrl != NULL)
	{
		libvlc_media_player_stop(m_pMediaPlayCtrl);
		libvlc_media_player_release(m_pMediaPlayCtrl);	// 释放播放器 Free the media_player
	}


	//libvlc_media_t *tmpMedia = libvlc_media_new_location (inst, "file:///F:\\movie\\cuc_ieschool.flv");  
	//libvlc_media_t *tmpMedia = libvlc_media_new_location (inst, "screen://");  //Screen Capture  
	//libvlc_media_t *tmpMedia = libvlc_media_new_path(g_app->m_pVlcInstance, m_strCurPath.c_str());
	libvlc_media_t *tmpMedia  = libvlc_media_new_location(g_app->m_pVlcInstance, m_strCurPath.c_str());

	
	if (tmpMedia != NULL)
	{
		m_pMediaPlayCtrl = libvlc_media_player_new_from_media(tmpMedia);
		libvlc_media_release(tmpMedia);/* No need to keep the media now */
		
		if (m_pMediaPlayCtrl != NULL) {
			libvlc_video_set_callbacks(m_pMediaPlayCtrl
										, CQMLVLCItem::CallBackLock
										, CQMLVLCItem::CallBackUnLock
										, CQMLVLCItem::CallBackDisplay
										, this);

			libvlc_video_set_format(m_pMediaPlayCtrl, "RGBA", FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH * 4);

			m_timer.start(45);
			libvlc_media_player_play(m_pMediaPlayCtrl);
		} else {
			QTRACE("err: %s - %d\n", __FUNCTION__, __LINE__);
		}
	}
	else
	{
		QTRACE("err: %s - %d\n", __FUNCTION__, __LINE__);
	}

// 	int length = libvlc_media_player_get_length(m_pMediaPlayCtrl);
// 	int width = libvlc_video_get_width(m_pMediaPlayCtrl);
// 	int height = libvlc_video_get_height(m_pMediaPlayCtrl);
}

void CQMLVLCItem::playFile(const QString &qstrFile)
{
	QTRACE("%s\n", __FUNCTION__);
	SetCurPath(qstrFile);
	play();
}

void CQMLVLCItem::setPause(bool bPause)
{
	if (m_pMediaPlayCtrl != NULL)
	{
		QTRACE("bPause: %d\n", bPause);
		libvlc_media_player_set_pause(m_pMediaPlayCtrl, bPause);
	}
}

void CQMLVLCItem::stop()
{
	QTRACE("%s\n", __FUNCTION__);

	if (m_pMediaPlayCtrl != NULL)
	{
		libvlc_media_player_stop(m_pMediaPlayCtrl);
	}
}

void CQMLVLCItem::setVolume(int iNum)
{
	QTRACE("%s %d\n", __FUNCTION__, iNum);
	
	if (m_pMediaPlayCtrl != NULL)
	{
		libvlc_audio_set_volume(m_pMediaPlayCtrl, max(iNum, 0));
	}
}

void CQMLVLCItem::setPlayPos(int iPos)
{

	if (m_pMediaPlayCtrl != NULL)
	{
		QTRACE("%s %d / %d\n", __FUNCTION__, iPos, libvlc_media_player_get_length(m_pMediaPlayCtrl));

		m_FrameMutex.lock();
		libvlc_media_player_set_time(m_pMediaPlayCtrl, iPos);
		m_FrameMutex.unlock();
	}
}

void* CQMLVLCItem::Lock(vdss &planes)
{
	m_FrameMutex.lock();
	memset(m_pFrameBuf, 0, FRAME_WIDTH * FRAME_HEIGHT * 4);
	*planes = m_pFrameBuf;

	return NULL;
}

void CQMLVLCItem::UnLock(void *picture, void *const *planes)
{
	m_FrameMutex.unlock();
}

void CQMLVLCItem::Display(void *picture)
{

}

void* CQMLVLCItem::CallBackLock(void *opaque, void **planes)
{
	CQMLVLCItem* p = static_cast<CQMLVLCItem *>(opaque);
	
	if (p != NULL)
	{
		p->Lock(planes);
	}

	return NULL;
}

void CQMLVLCItem::CallBackUnLock(void *opaque, void *picture, void *const *planes)
{
	CQMLVLCItem* p = static_cast<CQMLVLCItem *>(opaque);

	if (p != NULL)
	{
		p->UnLock(picture, planes);
	}
}

void CQMLVLCItem::CallBackDisplay(void *opaque, void *picture)
{
	CQMLVLCItem* p = static_cast<CQMLVLCItem *>(opaque);

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
		if (m_pMediaPlayCtrl != NULL)
		{
			int iLength = libvlc_media_player_get_length(m_pMediaPlayCtrl);

			if (iLength > 0)
			{
				int icurtime = libvlc_media_player_get_time(m_pMediaPlayCtrl);
				
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
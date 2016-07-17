#ifndef _QMLVLCItem_H_
#define _QMLVLCItem_H_

#include <QQuickPaintedItem>
#include <QString>
#include <QImage>
#include <QMutex>
#include <QTimer>
#include <string>
using namespace std;

struct libvlc_media_player_t;
typedef void** vdss;


class CQMLVLCItem : public QQuickPaintedItem
{
	Q_OBJECT
public:
	CQMLVLCItem(QQuickItem *parent = NULL);
	virtual ~CQMLVLCItem();

	virtual void paint(QPainter *painter);

public:
	// 播放业务逻辑接口
	Q_INVOKABLE void playFile(const QString &qstrFile);
	Q_INVOKABLE const QString& GetCurPath(QString &qstrOut) { qstrOut = m_strMediaPath.c_str(); return qstrOut; };
	Q_INVOKABLE void SetCurPath(const QString &qstrPath);
	Q_INVOKABLE void play();								// 加载播放m_strCurPath
	Q_INVOKABLE void setPause(bool bPause);					// 暂停或还原
	Q_INVOKABLE void setPlayPos(int iPos);					// 跳到指定播放位置
	Q_INVOKABLE void setVolume(int iNum);					// 设置音量
	Q_INVOKABLE void stop();								// 终止播放

	// vlc解码回调
	static void* CallBackLock(void *opaque, void **planes);								// typedef void *(*libvlc_video_lock_cb)(void *opaque, void **planes);
	static void CallBackUnLock(void *opaque, void *picture, void *const *planes);		// typedef void (*libvlc_video_unlock_cb)(void *opaque, void *picture, void *const *planes);
	static void CallBackDisplay(void *opaque, void *picture);														// typedef void (*libvlc_video_display_cb)(void *opaque, void *picture);
	void* Lock(vdss &planes);
	void UnLock(void *picture, void *const *planes);
	void Display(void *picture);

signals:
	void sigPlayingProgressRefresh(int iProgress, int iLength, QString qstrCurTime, QString qstrLastTime);	// 通知UI更新播放进度

public slots:
	void SlotTimeOut();

private:
	libvlc_media_player_t *m_pVLCMediaPlayer;
	string m_strMediaPath;
	QTimer m_timer;

	QMutex m_FrameMutex;			// 缓存保护锁
	uchar *m_pFrameDecodeBuf;		// 解码缓存帧
	uchar *m_pFrameDrawBuf;			// 播放绘制缓存帧
	int m_iFrameWidth;
	int m_iFrameHeight;
};



#endif	// _QMLVLCItem_H_



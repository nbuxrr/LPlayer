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
	// ����ҵ���߼��ӿ�
	Q_INVOKABLE void playFile(const QString &qstrFile);
	Q_INVOKABLE const QString& GetCurPath(QString &qstrOut) { qstrOut = m_strMediaPath.c_str(); return qstrOut; };
	Q_INVOKABLE void SetCurPath(const QString &qstrPath);
	Q_INVOKABLE void play();								// ���ز���m_strCurPath
	Q_INVOKABLE void setPause(bool bPause);					// ��ͣ��ԭ
	Q_INVOKABLE void setPlayPos(int iPos);					// ����ָ������λ��
	Q_INVOKABLE void setVolume(int iNum);					// ��������
	Q_INVOKABLE void stop();								// ��ֹ����

	// vlc����ص�
	static void* CallBackLock(void *opaque, void **planes);								// typedef void *(*libvlc_video_lock_cb)(void *opaque, void **planes);
	static void CallBackUnLock(void *opaque, void *picture, void *const *planes);		// typedef void (*libvlc_video_unlock_cb)(void *opaque, void *picture, void *const *planes);
	static void CallBackDisplay(void *opaque, void *picture);														// typedef void (*libvlc_video_display_cb)(void *opaque, void *picture);
	void* Lock(vdss &planes);
	void UnLock(void *picture, void *const *planes);
	void Display(void *picture);

signals:
	void sigPlayingProgressRefresh(int iProgress, int iLength, QString qstrCurTime, QString qstrLastTime);	// ֪ͨUI���²��Ž���

public slots:
	void SlotTimeOut();

private:
	libvlc_media_player_t *m_pVLCMediaPlayer;
	string m_strMediaPath;
	QTimer m_timer;

	QMutex m_FrameMutex;			// ���汣����
	uchar *m_pFrameDecodeBuf;		// ���뻺��֡
	uchar *m_pFrameDrawBuf;			// ���Ż��ƻ���֡
	int m_iFrameWidth;
	int m_iFrameHeight;
};



#endif	// _QMLVLCItem_H_



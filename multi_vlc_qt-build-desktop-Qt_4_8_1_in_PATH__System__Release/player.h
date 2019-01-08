#ifndef PLAYER_H
#define PLAYER_H
#include <vlc/vlc.h>
#include <vlc/libvlc.h>
//#include <phonon/Phonon/../../phonon/videoplayer.h>
#include <phonon/videoplayer.h>
#include <QWidget>
#include <QFrame>
#include <QLabel>





namespace Ui {
    class Player;
}
class QVBoxLayout;
class QPushButton;
class QTimer;
class QFrame;
class QSlider;
#define POSITION_RESOLUTION 10000
class Overlay : public QWidget
{
public:

    Overlay(QWidget *parent);
    void setSize(const QRect &);

protected:
    void paintEvent(QPaintEvent *event);


};
class Player : public QWidget
{
    Q_OBJECT
        QSlider *_positionSlider;
        QSlider *_volumeSlider;
        // [20101201 Ondra Spilka]
        // on Linux/Ubuntu Lucid and VLC >= 1.0 (at least 1.1.5 was tested) XWindow handle have to be passed
        // therefore QX11EmbedContainer have to be used instead of QFrame
   // #ifdef Q_WS_X11
       // QX11EmbedContainer *_videoWidget;
   // #else
        QFrame *_videoWidget;
        QFrame *_videoWidget_ad;
   // #endif
        QTimer *poller;
        QTimer *ad_timer;
        QTimer *banner_timer;
        bool _isPlaying;
        bool _isADPlaying;
        //libvlc_exception_t _vlcexcep;
        libvlc_instance_t *_vlcinstance;
        libvlc_event_manager_t *p_event_manager;
        libvlc_media_player_t *_mp;
        libvlc_media_t *_m;
        Overlay *overlay;
        QString ad_path;
        QString ad_path_1;
        QString ban_path;
        QString ban_path_1;
        QLabel  *label;
        QPixmap  *banner;

    public:
        Player();
        ~Player();
        //void raise(libvlc_exception_t * ex);
        void SetAdPath(QString path,int num);
        QString GetAdPath(int num);


    public slots:
        void playFile(QString file);
        void updateInterface();
        void changeVolume(int newVolume);
        void changePosition(int newPosition);
        void pause(int do_pause);
        void play();
        void test_expire();
        void banner_expire();
        QRect getSize();
        libvlc_state_t getState();




};


#endif // PLAYER_H

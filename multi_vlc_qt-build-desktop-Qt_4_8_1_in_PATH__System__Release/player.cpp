#include "player.h"
#include "ui_player.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QFrame>
#include <QPainter>
#include <QPen>
#include <QSize>
#include <iostream>
using std::cout;
using std::endl;

extern void cb_MediaPlay(const libvlc_event_t *ev, void *param);
extern void show_ad(Player *);
Player::Player() :
        QWidget()
{
    //preparation of the vlc command
    const char * const vlc_args[] = {
        "-I", "dummy", /* Don't use any interface */
        "--ignore-config",  /*Don't use VLC's config */
        "--extraintf=logger", //log anything
        "--verbose=0", //be much more verbose then normal for debugging purpose
        "--plugin-path=/usr/include/vlc/plugins" };

//#ifdef Q_WS_X11
  //  QX11EmbedContainer *_videoWidget;
//#else
    _videoWidget=new QFrame(this);
    //_videoWidget_ad=new QFrame(this);
//#endif

    _volumeSlider=new QSlider(Qt::Horizontal,this);
    _volumeSlider->setMaximum(100); //the volume is between 0 and 100
    _volumeSlider->setToolTip("Audio slider");

    // Note: if you use streaming, there is no ability to use the position slider
    _positionSlider=new QSlider(Qt::Horizontal,this);
    _positionSlider->setMaximum(POSITION_RESOLUTION);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_videoWidget);
    //layout->addWidget(_videoWidget_ad);
    layout->addWidget(_positionSlider);
    layout->addWidget(_volumeSlider);
    setLayout(layout);

    QSize ban_size(600,90);
    ban_path = "<img src='/home/vgaur/Videos/flash_ads/google_nexus.jpg' />";
    ban_path_1 = "<img src='/home/vgaur/Videos/flash_ads/gold.jpg' />";
    //label = new QLabel("<img src='/home/vgaur/Videos/flash_ads/google_nexus.jpg' />",this);
    /*label = new QLabel(ban_path,this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    label->setMinimumSize(ban_size);
    label->setScaledContents(true);
    label->move(0,400);
    label->show();*/

    //overlay = new Overlay(_videoWidget);
    //QRect my_size = this->getSize();
    //QRect my_size(200.0, 200.0, 200.0, 200.0);
    //overlay->setSize(my_size);

    _isPlaying=false;
    poller=new QTimer(this);
    ad_timer = new QTimer(this);
    banner_timer = new QTimer(this);

    //Initialize an instance of vlc
    //a structure for the exception is neede for this initalization
    //libvlc_exception_init(&_vlcexcep);

    //create a new libvlc instance
    _vlcinstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);  //tricky calculation of the char space used
    //raise (&_vlcexcep);

    // Create a media player playing environement
    _mp = libvlc_media_player_new (_vlcinstance);
    p_event_manager = libvlc_media_player_event_manager(_mp);
    //raise (&_vlcexcep);

    //connect the two sliders to the corresponding slots (uses Qt's signal / slots technology)
    connect(poller, SIGNAL(timeout()), this, SLOT(updateInterface()));
    connect(ad_timer, SIGNAL(timeout()), this, SLOT(test_expire()));
    connect(banner_timer, SIGNAL(timeout()), this, SLOT(banner_expire()));
    connect(_positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(changePosition(int)));
    connect(_volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeVolume(int)));

    poller->start(100); //start timer to trigger every 100 ms the updateInterface slot
    //if(libvlc_media_get_state(_m) != libvlc_Ended)
    ad_timer->start(16000);
    banner_timer->start(5000);
}

//desctructor
Player::~Player()
{
    /* Stop playing */
    libvlc_media_player_stop (_mp);

    /* Free the media_player */
    libvlc_media_player_release (_mp);

    libvlc_release (_vlcinstance);
    //raise (&_vlcexcep);
}

void Player::playFile(QString file)
{
    //the file has to be in one of the following formats /perhaps a little bit outdated)
    /*
        [file://]filename              Plain media file
        http://ip:port/file            HTTP URL
        ftp://ip:port/file             FTP URL
        mms://ip:port/file             MMS URL
        screen://                      Screen capture
        [dvd://][device][@raw_device]  DVD device
        [vcd://][device]               VCD device
        [cdda://][device]              Audio CD device
        udp:[[<source address>]@[<bind address>][:<bind port>]]
        */

    /* Create a new LibVLC media descriptor */
    _m = libvlc_media_new_path(_vlcinstance, file.toAscii());
    //raise(&_vlcexcep);

    libvlc_media_player_set_media (_mp, _m);
    //raise(&_vlcexcep);

    // /!\ Please note /!\
    //
    // passing the widget to the lib shows vlc at which position it should show up
    // vlc automatically resizes the video to the ´given size of the widget
    // and it even resizes it, if the size changes at the playing

    /* Get our media instance to use our window */
#if defined(Q_OS_WIN)
    libvlc_media_player_set_drawable(_mp, reinterpret_cast<unsigned int>(_videoWidget->winId()), &_vlcexcep );
    //libvlc_media_player_set_hwnd(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
#elif defined(Q_OS_MAC)
    libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
    //libvlc_media_player_set_agl (_mp, _videoWidget->winId(), &_vlcexcep); // for vlc 1.0
#else //Linux
    //[20101201 Ondrej Spilka] obsolete call on libVLC >=1.1.5
    //libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
    //libvlc_media_player_set_xwindow(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0

    /* again note X11 handle on Linux is needed
            winID() returns X11 handle when QX11EmbedContainer us used */

    int windid = _videoWidget->winId();
    libvlc_media_player_set_xwindow (_mp, windid );

#endif
    //raise(&_vlcexcep);

    /* Play */
    libvlc_media_player_play (_mp);
    //sleep(10);
    //libvlc_media_player_pause (_mp);
    //sleep(10);
    //libvlc_media_player_play (_mp);

    //raise(&_vlcexcep);

    _isPlaying=true;

}

void Player::changeVolume(int newVolume)
{
    //libvlc_exception_clear(&_vlcexcep);
    libvlc_audio_set_volume (_mp,newVolume);
    //raise(&_vlcexcep);
}
void Player::SetAdPath(QString path,int num)
{
    if(num)
        ad_path = path;
    else
        ad_path_1 = path;
}
QString Player::GetAdPath(int num)
{
    if(num)
       return ad_path;
    else
        return ad_path_1;
}
void Player::test_expire()
{
    if(libvlc_media_get_state(_m) == libvlc_Ended)
        return;
    static int do_pause=1;
    //std::cout << "timer expired" << endl;
    libvlc_media_player_set_pause(_mp,do_pause);
    if(do_pause){
        _isADPlaying=true;
        show_ad(this);
        }
    do_pause = !do_pause;
}
void Player::banner_expire()
{
    static int which_banner=1;
    static int show_banner=1;
    QString b_path;
    //std::cout << "Banner timer expired"<< which_banner << endl;
    if(_isADPlaying==true)
        return;
    if(show_banner){
        if((which_banner)==1){
            b_path = ban_path;
            }
        else{
            b_path = ban_path_1;
            }
        which_banner = !which_banner;
        }
    if(show_banner){
        QSize ban_size(600,90);
        label = new QLabel(b_path,this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
        label->setMinimumSize(ban_size);
        label->setScaledContents(true);
        label->move(0,400);
        label->show();
        }
    else {
        label->close();
        }

    /*if(do_banner)
        label->show();
    else
        label->hide();*/
    show_banner = ! show_banner;
    //which_banner++;
}
void Player::pause(int do_pause)
{
    //libvlc_exception_clear(&_vlcexcep);

    //int f=0;
    //libvlc_event_attach(p_event_manager,libvlc_MediaPlayerPaused,cb_MediaPlay,&f);
    libvlc_media_player_set_pause(_mp,do_pause);
    //libvlc_event_detach(p_event_manager,libvlc_MediaPlayerPaused,cb_MediaPlay,&f);
    //raise(&_vlcexcep);
    if(!do_pause)
        _isPlaying = false;
    else
        _isPlaying = true;
}
void Player::play()
{
    //libvlc_exception_clear(&_vlcexcep);
    //int f=0;
    libvlc_media_player_play(_mp);
    //libvlc_event_attach(p_event_manager,libvlc_MediaPlayerPlaying,cb_MediaPlay,&f);
    //raise(&_vlcexcep);
    _isPlaying = true;
}
void Player::changePosition(int newPosition)
{
    //libvlc_exception_clear(&_vlcexcep);
    // It's possible that the vlc doesn't play anything
    // so check before
    libvlc_media_t *curMedia = libvlc_media_player_get_media (_mp);
    //libvlc_exception_clear(&_vlcexcep);
    if (curMedia == NULL)
        return;

    float pos=(float)(newPosition)/(float)POSITION_RESOLUTION;
    libvlc_media_player_set_position (_mp, pos);
    //raise(&_vlcexcep);
}

void Player::updateInterface()
{
    if(!_isPlaying)
        return;

    // It's possible that the vlc doesn't play anything
    // so check before
    libvlc_media_t *curMedia = libvlc_media_player_get_media (_mp);
    //libvlc_exception_clear(&_vlcexcep);
    if (curMedia == NULL)
        return;

    float pos=libvlc_media_player_get_position (_mp);
    int siderPos=(int)(pos*(float)(POSITION_RESOLUTION));
    _positionSlider->setValue(siderPos);
    int volume=libvlc_audio_get_volume (_mp);
    _volumeSlider->setValue(volume);
}


/*void Player::raise(libvlc_exception_t * ex)
{
    if (libvlc_exception_raised (ex))
        {
        fprintf (stderr, "error: %s\n", libvlc_exception_get_message(ex));
        exit (-1);
        }
}*/
QRect Player::getSize()
{
    QRect v_size = this->geometry();
    return v_size;

}
libvlc_state_t Player::getState()
{
    libvlc_state_t state;
    state = libvlc_media_player_get_state(_mp);
    return state;
}



Overlay::Overlay(QWidget *parent) : QWidget(parent)
{
    //setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Overlay::setSize(QRect const & size)
{
    this->setGeometry ( size);
}

void Overlay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage *image = new QImage("/home/vgaur/Videos/flash_ads/nflx_20033v4.gif");
    //painter.setRenderHint(QPainter::Antialiasing);
    //painter.setPen(QPen(Qt::red));
    QRectF rectangle(100.0, 100.0, 2000.0, 2000.0);
    painter.drawImage(rectangle,*image);
    //painter.drawEllipse(rectangle);
    //painter.drawLine(width()/8, height()/8, 7*width()/8, 7*height()/8);
    //painter.drawLine(width()/8, 7*height()/8, 7*width()/8, height()/8);

}

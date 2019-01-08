#include <QtGui/QApplication>
#include "player.h"
#include <phonon/videoplayer.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <iostream>
using std::cout;
using std::endl;

//Phonon::VideoPlayer *v_player;
void cb_MediaPlay(const libvlc_event_t *ev, void *param) {
    //std::cout << " type " << libvlc_event_type_name (ev->type)<<std::endl;
    /*if(ev->type==libvlc_MediaPlayerPaused){
        Phonon::VideoPlayer *v_player = new Phonon::VideoPlayer(Phonon::VideoCategory,&w);
        QRect size = w.getSize();
        v_player->setGeometry(size);
        QObject::connect(v_player, SIGNAL(finished()), v_player, SLOT(deleteLater()));
        v_player->play(Phonon::MediaSource("/home/vgaur/Videos/14069-Vegas.flv"));
        }*/
}
void show_ad(Player* x){
    //std::cout << "Showing AD" << endl;
    static int num=0;
    QPoint position,old_position;
    Phonon::VideoPlayer *v_player = new Phonon::VideoPlayer(Phonon::VideoCategory,x);
    position = x->pos();
    //old_position = x->oldPos();
    QRect size = x->getSize();
    v_player->setGeometry(size);

    v_player->move(0,0);
    v_player->show();
    QObject::connect(v_player, SIGNAL(finished()), v_player, SLOT(deleteLater()));
    //v_player->play(Phonon::MediaSource("/home/vgaur/Videos/flash_ads/2010_Lexus_Commercial _Pitch4.flv"));
    v_player->play(Phonon::MediaSource(x->GetAdPath(num)));
    num = !num;
    //sleep(10);
    //v_player->hide();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(argv[1]);
    libvlc_state_t state;
    Player *w_1 = new Player();
    QString vFile;
    //Player *w_2 = new Player();
    vFile = argv[2];
    int length = vFile.length();
    int pos = atoi(argv[5]);
    srand(pos);
    int position = rand()/1000000;
    w_1->resize(600,480);
    w_1->show();
    w_1->playFile(argv[2]); // Replace with what you want to play
    w_1->SetAdPath(argv[3],1);
    w_1->SetAdPath(argv[4],0);    
    int x = pos*(pos/10);
    int y = pos*(pos/15);
    //std::cout << "Position " << x <<" "<< y << "\n";
    w_1->move(x ,y);
    QString title;
    title.setNum(x);
    QString title_1;
    title_1.setNum(y);
    title.append("x").append(title_1);
    w_1->setWindowTitle(title);
    //w_2->resize(800,600);
    //w_2->show();
    //w_1->playFile("/home/vgaur/Videos/flash_movie/ice_age_3.flv"); // Replace with what you want to play

    //Phonon::VideoPlayer *v_player = new Phonon::VideoPlayer(Phonon::VideoCategory,&w);
    //QRect size = w.getSize();
    //v_player->setGeometry(size);
    /*QObject::connect(v_player, SIGNAL(finished()), v_player, SLOT(deleteLater()));
    v_player->play(Phonon::MediaSource("/home/vgaur/Videos/flash_movie/inception_trim.flv"));
*/
    //w.play();

    //sleep(15);
    //w.show();
    //w.pause(1);
    //sleep(15);
    //w.pause(0);
    //state = w.getState();
    //std::cout << "Playing-first" << state <<endl;

    /*if(state == libvlc_Playing  || state == libvlc_Paused){
        std::cout << "Playing-second" << endl;
        sleep(10);
        w.pause(1);
        state =w.getState();
        std::cout << "Playing-third" << state <<endl;
        std::cout << "Paused" << endl;
        w.pause(1);
        v_player->setGeometry(size);
      QObject::connect(v_player, SIGNAL(finished()), v_player, SLOT(deleteLater()));
      v_player->play(Phonon::MediaSource("/home/vgaur/Videos/14069-Vegas.flv"));
        w.play();
        }*/
    return a.exec();
}

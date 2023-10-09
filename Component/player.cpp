#include "player.h"
#include <QObject>
#include <Component/controlbar_progressbar.h>
#include <Component/controlbar_btng.h>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include "Component/songsdetailpage.h"
#include "Function/lyric.h"
#include "Component/lyricwidget.h"

Player::Player(QObject* parent) :
    QObject(parent),
    player(new QMediaPlayer()),
    checkTimer(new QTimer()),
    controlMetux(new QMutex())

{
    QObject::connect(this->player,SIGNAL(positionChanged(qint64)),&controlbar_progressbar::getInstance(),SLOT(positionCharged(qint64)));
    QObject::connect(this->player,SIGNAL(durationChanged(qint64)),&controlbar_progressbar::getInstance(),SLOT(setDuration(qint64)));
    QObject::connect(this->player,&QMediaPlayer::stateChanged,[=](){
        if(player->state() == QMediaPlayer::StoppedState){
            controlbar_btnG::getInstance().playState = 0;
            controlbar_btnG::getInstance().switchPlayAndPause();
        }
    });
    QObject::connect(this->checkTimer,SIGNAL(timeout()),this,SLOT(check()));
    QObject::connect(this->player,SIGNAL(positionChanged(qint64)),&lyricWidget::getInstance(),SLOT(addHightLight(qint64)));
    QObject::connect(this->player,SIGNAL(stateChanged(QMediaPlayer::State)),&lyricWidget::getInstance(),SLOT(changeTimerStatus(QMediaPlayer::State)));
    this->checkTimer->setInterval(100);

}

Player::~Player()
{
   delete this->player;
}

Player &Player::getInstance()
{
    static Player instance;
   return instance;
}

int Player::getStatus()
{
   qDebug()<< this->player->state();
   return this->player->state();
}

QMediaPlayer* Player::getQPlayer()
{
   return this->player;
}

qint64 Player::play(QString songUrl,QString id)
{
   qint64 duration = 0;
   if(songUrl.isEmpty()){
       return duration;
   }
   this->player->setMedia(QMediaContent(QUrl(songUrl)));
   songsDetailPage::getInstance().setSongLyric(lyric::getInstance().getSongLyric(id));
   duration = this->getDuration();
   qDebug() << duration;
   this->player->play();
   return duration;
}

void Player::pause()
{
   if(this->player->state() == QMediaPlayer::PlayingState){
       this->player->pause();
   }
}

void Player::start()
{
   if(this->player->state() == QMediaPlayer::PausedState){
       this->player->play();
   }
}

qint64 Player::getDuration()
{
//   qDebug()<<this->player->duration();
   return this->player->duration();
}

void Player::sliderReleased()
{
//   qDebug()<<"sliderMoved";
   if(this->player->state() == QMediaPlayer::PlayingState || this->player->state() == QMediaPlayer::PausedState){
       if(this->player->duration() != 0){
           this->controlMetux->lock();
           qint64 position =  qint64((double)controlbar_progressbar::getInstance().getSliderPostion() / 100 * this->player->duration());
           this->player->setPosition(position);
           lyricWidget::getInstance().chargeHightLight(position);
           this->controlMetux->unlock();
       }
   }else{
       return;
   }


}

void Player::check()
{

}

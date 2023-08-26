#include "controlbar_progressbar.h"

#include <Center/controlbar_center.h>

#include <QHBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QTimeEdit>
#include <QDebug>
#include "player.h"
#include <QMutex>

#include "../style.h"

controlbar_progressbar::controlbar_progressbar(QWidget *parent)
    : QWidget{parent},
    parent((controlbar_center*)this->parentWidget()),
    width(this->parent->width * 0.95),
    height(this->parent->height * 0.5),
    slider(new QSlider(this)),
    leftTimeEdit(new QTimeEdit(this)),
    rightTimeEdit(new QTimeEdit(this)),
    mainHBL(new QHBoxLayout(this)),
    mutex(new QMutex())
{
    if(parent != nullptr){
        this->resize(this->width,this->height);
        this->setAttribute(Qt::WA_TranslucentBackground,true);
        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(5);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->slider->setOrientation(Qt::Horizontal);
        this->slider->setAttribute(Qt::WA_OpaquePaintEvent,false);
        this->leftTimeEdit->setAlignment(Qt::AlignCenter);
        this->rightTimeEdit->setAlignment(Qt::AlignCenter);

        this->slider->setMaximum(100);
        this->slider->setMinimum(0);

        this->leftTimeEdit->setDisplayFormat("mm:ss");
        this->rightTimeEdit->setDisplayFormat("mm:ss");

        this->mainHBL->addWidget(this->leftTimeEdit,2);
        this->mainHBL->addWidget(this->slider,3);
        this->mainHBL->addWidget(this->rightTimeEdit,2);
        this->setLayout(this->mainHBL);


        this->setStyle(my_progressbar_style);

        qDebug()<<"control_progressbar init()";

    }else{
            exit(1);
    }


}

controlbar_progressbar &controlbar_progressbar::getInstance(QWidget *parent)
{
    static controlbar_progressbar instance(parent);
    return instance;
}

void controlbar_progressbar::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

int controlbar_progressbar::getSliderPostion()
{
    return this->slider->value();
}


void controlbar_progressbar::setDuration(qint64 duration)  //获取歌曲时长并显示
{
    if(flag == 0){
            QObject::connect(slider,SIGNAL(sliderReleased()),&Player::getInstance(),SLOT(sliderReleased()));
            flag++;
    }
//    qDebug()<<QTime(0,0,0,0).addMSecs(duration);
    if(duration>0){
            this->duration = duration;
    }
    this->rightTimeEdit->setTime(QTime(0,0,0,0).addMSecs(duration));
    this->rightTimeEdit->repaint();
}

void controlbar_progressbar::positionCharged(qint64 position)  //获取已播放歌曲时长
{
    this->mutex->lock();
//    qDebug()<<QTime(0,0,0,0).addMSecs(position);
    this->leftTimeEdit->setTime(QTime(0,0,0,0).addMSecs(position));
//    qDebug()<<QTime(0,0,0,0).addMSecs(position);
    if(this->duration!=-1 && this->duration!=0){
            this->slider->setSliderPosition((double(position) / duration) * 100);
    }
    this->mutex->unlock();
    this->leftTimeEdit->repaint();

}

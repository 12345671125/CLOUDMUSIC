#include "controlbar_progressbar.h"

#include <Center/controlbar_center.h>

#include <QHBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QTimeEdit>

#include "../style.h"

controlbar_progressbar::controlbar_progressbar(QWidget *parent)
    : QWidget{parent},
    parent((controlbar_center*)this->parentWidget()),
    width(this->parent->width * 0.95),
    height(this->parent->height * 0.5),
    leftTimeEdit(new QTimeEdit(this)),
    slider(new QSlider(this)),
    rightTimeEdit(new QTimeEdit(this)),
    mainHBL(new QHBoxLayout(this))
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

        this->mainHBL->addWidget(this->leftTimeEdit,1);
        this->mainHBL->addWidget(this->slider,3);
        this->mainHBL->addWidget(this->rightTimeEdit,1);
        this->setLayout(this->mainHBL);



        this->setStyle(my_progressbar_style);
        qDebug() <<"control_progressbar init()";

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

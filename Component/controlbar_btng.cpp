#include "controlbar_btng.h"

#include <Center/controlbar_center.h>

#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>

controlbar_btnG::controlbar_btnG(QWidget *parent)
    : QWidget{parent},
    parent((controlbar_center*)this->parentWidget()),
    width(this->parent->width * 0.95),
    height(this->parent->height * 0.5),
    startAndpauseBtn(new QPushButton(this)),
    frontBtn(new QPushButton(this)),
    nextBtn(new QPushButton(this)),
    switchModeBtn(new QPushButton(this)),
    startIcon(new QIcon(QPixmap(":/img/start.png"))),
    pauseIcon(new QIcon(QPixmap(":/img/pause.png"))),
    frontIcon(new QIcon(QPixmap(":/img/front.png"))),
    nextIcon(new QIcon(QPixmap(":/img/next.png"))),
    modeIcon_circle(new QIcon(QPixmap(":/img/mode_circle.png"))),
    modeIcon_random(new QIcon(QPixmap(":/img/mode_random.png"))),
    modeIcon_onlyone(new QIcon(QPixmap(":/img/mode_onlyone.png"))),
    mainHBL(new QHBoxLayout(this))
{
    if(parent != nullptr){
        this->resize(this->width,this->height);

        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(15);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->frontBtn->setFlat(true);
        this->nextBtn->setFlat(true);
        this->startAndpauseBtn->setFlat(true);
        this->switchModeBtn->setFlat(true);
        this->frontBtn->setFocusPolicy(Qt::NoFocus);
        this->nextBtn->setFocusPolicy(Qt::NoFocus);
        this->startAndpauseBtn->setFocusPolicy(Qt::NoFocus);
        this->switchModeBtn->setFocusPolicy(Qt::NoFocus);

        this->frontBtn->setIcon(*this->frontIcon);
        this->nextBtn->setIcon(*this->nextIcon);
        this->startAndpauseBtn->setIcon(*this->startIcon);
        this->switchModeBtn->setIcon(*this->modeIcon_circle);

        this->frontBtn->setIconSize(QSize(24,24));
        this->nextBtn->setIconSize(QSize(24,24));
        this->startAndpauseBtn->setIconSize(QSize(32,32));
        this->switchModeBtn->setIconSize(QSize(24,24));


        this->mainHBL->addWidget(this->switchModeBtn);
        this->mainHBL->addWidget(this->frontBtn);
        this->mainHBL->addWidget(this->startAndpauseBtn);
        this->mainHBL->addWidget(this->nextBtn);

        this->setLayout(this->mainHBL);

        qDebug()<<"controlbar_btn init()";
    }else{
        exit(1);
    }



}

controlbar_btnG::~controlbar_btnG()
{
    delete startIcon;
    delete pauseIcon;
    delete frontIcon;
    delete nextIcon;
    delete modeIcon_circle;
    delete modeIcon_random;
    delete modeIcon_onlyone;
}

controlbar_btnG &controlbar_btnG::getInstance(QWidget *parent)
{
    static controlbar_btnG instance(parent);
    return instance;
}

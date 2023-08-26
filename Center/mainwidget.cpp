#include "mainwidget.h"

#include "main_left_listwidget.h"
#include "main_right_stackwidget.h"
#include "main_right_controlbarwidget.h"
#include <QHBoxLayout>
#include <QStyle>
#include <QVBoxLayout>
#include "../style.h"
#include <QDebug>

mainWidget::mainWidget(QWidget *parent)
    : QWidget{parent},
    width(parent->width()),
    height(parent->height()*0.9),
    listWidget(&main_left_listWidget::getInstance(this)),
    stackWidget(&main_right_stackWidget::getInstance(this)),
    controlBarWidget(&main_right_controlBarWidget::getInstance(this)),
    mainHBL(new QHBoxLayout(this)),
    rightHBL(new QVBoxLayout())
{
    if(parent != nullptr){
        this->resize(this->width,this->height);
        qDebug()<<"mainWidget init()";

        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(0);
        this->setAttribute(Qt::WA_StyledBackground);

        this->rightHBL->setContentsMargins(0,0,0,0);
        this->rightHBL->setSpacing(0);
        this->rightHBL->addWidget(this->stackWidget,6);
        this->rightHBL->addWidget(this->controlBarWidget,1);

        this->mainHBL->addWidget(this->listWidget,1);
        this->mainHBL->addLayout(this->rightHBL,4);
        this->setLayout(this->mainHBL);

        this->setStyle(my_centerWidget_style);
        qDebug()<<this->stackWidget;
    }else{
        exit(1);
    }
}

mainWidget &mainWidget::getInstance(QWidget *parent)
{
    static mainWidget instance(parent);
    return instance;
}

void mainWidget::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

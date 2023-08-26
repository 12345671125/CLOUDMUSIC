#include "main_right_controlbarwidget.h"
#include "mainwidget.h"
#include "controlbar_left.h"
#include "controlbar_center.h"
#include "controlbar_right.h"
#include <QHBoxLayout>
#include <QDebug>

main_right_controlBarWidget::main_right_controlBarWidget(QWidget *parent)
    : QWidget{parent},
    parent((mainWidget*)parentWidget()),
    width(this->parent->width * 0.7),
    height(this->parent->height * 0.2),
    mainHBL(new QHBoxLayout(this)),
    leftWidget(&controlbar_left::getInstance(this)),
    centerWidget(&controlbar_center::getInstance(this)),
    rightWidget(&controlbar_right::getInstance(this))
{
    if(parent != nullptr){
        this->resize(width,height);
        qDebug()<<"controlBar init()";

        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(0);

        this->mainHBL->addWidget(this->leftWidget,3);
        this->mainHBL->addWidget(this->centerWidget,5);
        this->mainHBL->addWidget(this->rightWidget,2);

        this->setLayout(this->mainHBL);

        qDebug()<<"main_right_controlbarWidget init()";
    }else{
        exit(1);
    }
}

main_right_controlBarWidget &main_right_controlBarWidget::getInstance(QWidget *parent)
{
    static main_right_controlBarWidget instance(parent);
    return instance;
}

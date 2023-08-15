#include "main_right_controlbarwidget.h"
#include "mainwidget.h"

#include <QHBoxLayout>

main_right_controlBarWidget::main_right_controlBarWidget(QWidget *parent)
    : QWidget{parent},
    parent((mainWidget*)parentWidget()),
    width(this->parent->width * 0.7),
    height(this->parent->height * 0.2),
    mainHBL(new QHBoxLayout(this))
{
    if(parent != nullptr){
        this->resize(width,height);
        qDebug()<<"controlBar init()";

        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(0);
    }else{
        exit(1);
    }
}

main_right_controlBarWidget &main_right_controlBarWidget::getInstance(QWidget *parent)
{
    static main_right_controlBarWidget instance(parent);
    return instance;
}

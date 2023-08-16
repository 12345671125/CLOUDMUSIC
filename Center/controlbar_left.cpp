#include "controlbar_left.h"
#include "Center/main_right_controlbarwidget.h"

#include <QHBoxLayout>

controlbar_left::controlbar_left(QWidget *parent)
    : QWidget{parent},
    parent((main_right_controlBarWidget*)parentWidget()),
    width(this->parent->width * 0.2),
    height(this->parent->height),
    mainHBL(new QHBoxLayout(this))
{
    if(parent != nullptr){

        this->resize(this->width,this->height);

        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(0);
    }else{
        exit(1);
    }
}

controlbar_left &controlbar_left::getInstance(QWidget *parent)
{
    static controlbar_left instance(parent);
    return instance;
}

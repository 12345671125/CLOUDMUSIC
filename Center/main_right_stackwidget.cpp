#include "main_right_stackwidget.h"
#include "mainwidget.h"

main_right_stackWidget::main_right_stackWidget(QWidget *parent)
    : QWidget{parent},
    parent((mainWidget*)parentWidget()),
    width(this->parent->width * 0.7),
    height(this->parent->height * 0.4)
{
    if(parent != nullptr){
        this->resize(width,height);
        qDebug()<<"mystackWidget init()";
    }else{
        exit(1);
    }
}

main_right_stackWidget &main_right_stackWidget::getInstance(QWidget *parent)
{
    static main_right_stackWidget instance(parent);
    return instance;
}

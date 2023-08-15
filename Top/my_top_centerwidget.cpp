#include "my_top_centerwidget.h"

#include <QHBoxLayout>
#include "../Component/searchbox.h"
#include "topwidget.h"
my_top_centerWidget::my_top_centerWidget(QWidget *parent)
    : QWidget{parent},
    parent((topWidget*)parentWidget()),
    width(this->parent->width * 0.6),
    height(this->parent->height * 0.95),
    mainHBL(new QHBoxLayout(this)),
    searchBox(&SearchBox::getInstance(this))
{
    if(parent != nullptr)
    {
        this->resize(width,height);
        this->setAttribute(Qt::WA_StyledBackground,true); //使控件使用自定义样式
        this->mainHBL->setContentsMargins(0,0,0,0);

        this->mainHBL->addWidget(this->searchBox);

        this->setLayout(mainHBL);
        qDebug()<<"top_center init()";
    }else{
        exit(1);
    }

}

my_top_centerWidget &my_top_centerWidget::getInstance(QWidget *parent)
{
    static my_top_centerWidget instance(parent);
    return instance;
}

#include "personalized_group_widget.h"

#include <QGridLayout>
#include "personalized_simple_box.h"

personalized_group_widget::personalized_group_widget(QWidget *parent)
    : QWidget{parent},
    mainGBL(new QGridLayout(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setContentsMargins(0,0,0,0);
    this->mainGBL->setContentsMargins(0,0,0,0);
    this->mainGBL->setSpacing(5);

    for(int i = 0;i<10;i++){
        personalized_simple_box* box = new personalized_simple_box(this);
        QByteArray byteArr;
        byteArr.clear();
        box->init(byteArr);
        this->mainGBL->addWidget(box,i/5,i%5);
    }


    this->setLayout(this->mainGBL);
}

personalized_group_widget &personalized_group_widget::getInstance(QWidget *parent)
{
    static personalized_group_widget instance(parent);
    return instance;
}

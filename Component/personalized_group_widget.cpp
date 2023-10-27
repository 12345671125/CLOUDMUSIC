#include "personalized_group_widget.h"

#include <QGridLayout>
#include <QJsonArray>
#include "personalized_simple_box.h"
#include "../Function/personalized_f.h"
#include <QJsonObject>>

personalized_group_widget::personalized_group_widget(QWidget *parent)
    : QWidget{parent},
    mainGBL(new QGridLayout(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setContentsMargins(0,0,0,0);
    this->mainGBL->setContentsMargins(0,0,0,0);
    this->mainGBL->setSpacing(10);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QJsonArray json_arr = personalized_f::getInstance().getpersonalized_f();

    for(int i = 0;i<10;i++){
        personalized_simple_box* box = new personalized_simple_box(this);
        box->init(json_arr.at(i).toObject());
        this->mainGBL->addWidget(box,i/5,i%5);
    }


    this->setLayout(this->mainGBL);
}

personalized_group_widget &personalized_group_widget::getInstance(QWidget *parent)
{
    static personalized_group_widget instance(parent);
    return instance;
}

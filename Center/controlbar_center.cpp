#include "controlbar_center.h"

#include <QVBoxLayout>
#include "../Component/controlbar_btng.h"
#include "../Component/controlbar_progressbar.h"
#include "Center/main_right_controlbarwidget.h"

controlbar_center::controlbar_center(QWidget *parent)
    : QWidget{parent},
    parent((main_right_controlBarWidget*)parentWidget()),
    width(this->parent->width * 0.6),
    height(this->parent->height),
    mainVBL(new QVBoxLayout(this)),
    btnG(&controlbar_btnG::getInstance(this)),
    progressbar(&controlbar_progressbar::getInstance(this))

{
    if(parent != nullptr){

        this->resize(this->width,this->height);

        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainVBL->setAlignment(Qt::AlignCenter);
        this->mainVBL->setContentsMargins(0,0,0,0);
        this->mainVBL->setSpacing(0);

        this->mainVBL->addWidget(this->btnG);
        this->mainVBL->addWidget(this->progressbar);

        this->setLayout(this->mainVBL);

        qDebug()<< "controlbar_center init()";
    }else{
        exit(1);
    }
}

controlbar_center &controlbar_center::getInstance(QWidget *parent)
{
    static controlbar_center instance(parent);
    return instance;
}

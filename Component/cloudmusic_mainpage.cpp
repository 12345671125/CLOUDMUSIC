#include "cloudmusic_mainpage.h"

#include <QVBoxLayout>
#include <QStyle>
#include "../style.h"
#include "viewpager.h"
#include "../Component/personalized.h"

cloudmusic_mainpage::cloudmusic_mainpage(QWidget *parent)
    : QWidget{parent},
    viewpagerWidget(&viewpager::getInstance(this)),
    mainVBL(new QVBoxLayout(this))
{
    this->personalizedWidget = &personalized::getInstance(this);

    this->setAttribute(Qt::WA_StyledBackground,true);
    this->mainVBL->setSpacing(0);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);

    this->mainVBL->addWidget(this->viewpagerWidget,1);
    this->mainVBL->addWidget(this->personalizedWidget,2);

    this->setLayout(this->mainVBL);
    this->setStyle(my_mainpage_style);
}

cloudmusic_mainpage &cloudmusic_mainpage::getInstace(QWidget *parent)
{
    static cloudmusic_mainpage instance(parent);
    return instance;
}

void cloudmusic_mainpage::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

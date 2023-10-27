#include "personalized.h"
#include "qstyle.h"

#include <QLabel>
#include <QVBoxLayout>
#include "../style.h"
#include "personalized_group_widget.h"

personalized::personalized(QWidget *parent)
    : QWidget{parent},
    title(new QLabel(this)),
    componentGroup(&personalized_group_widget::getInstance(this)),
    mainVBL(new QVBoxLayout(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setContentsMargins(0,0,0,0);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->mainVBL->setSpacing(0);

    this->title->setAlignment(Qt::AlignLeft);
    this->title->setText("推荐歌单 >");

    this->mainVBL->addWidget(this->title,2);
    this->mainVBL->addWidget(this->componentGroup,8);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    this->setLayout(this->mainVBL);
    this->setStyle(my_mainpage_personalized_style);
}

personalized& personalized::getInstance(QWidget *parent)
{
    static personalized instance(parent);
    return instance;
}

void personalized::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

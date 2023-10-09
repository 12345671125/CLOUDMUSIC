#include "personalized_simple_box.h"

#include <QVBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPushButton>

personalized_simple_box::personalized_simple_box(QWidget *parent)
    : QWidget{parent},
    imgBox(new QLabel(this)),
    img(new QImage),
    title(new QLabel),
    mainVBL(new QVBoxLayout(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->mainVBL->setSpacing(0);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);

    this->mainVBL->addWidget(this->imgBox,4);
    this->mainVBL->addWidget(this->title,1);
    this->imgBox->setScaledContents(true);

    this->setLayout(this->mainVBL);
}

void personalized_simple_box::init(QByteArray byteArr, QString title)
{
    if(byteArr.isEmpty()){
        QPixmap pixmap(":/img/testImg.png");
        pixmap.scaled(this->imgBox->size(),Qt::KeepAspectRatio);
        this->imgBox->setPixmap(pixmap);
        this->title->setText(title);
    }else{
        QPixmap pixmap;
        pixmap.loadFromData(byteArr);
        this->imgBox->setPixmap(pixmap);
        this->title->setText(title);
    }
}

#include "my_listwidgetitem.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

my_ListWidgetItem::my_ListWidgetItem(QString title,QString imgPath,QWidget *parent)
    : QWidget{parent},
    img(new QIcon(QPixmap(imgPath))),
    imgBox(new QPushButton(this)),
    title(new QLabel(this)),
    mainHBL(new QHBoxLayout(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->mainHBL->setSpacing(0);
    this->mainHBL->setContentsMargins(10,5,5,5);
    this->mainHBL->setAlignment(Qt::AlignCenter);

    this->imgBox->setIcon(*this->img);
    this->imgBox->setFlat(true);
    this->imgBox->setEnabled(false);

    this->title->setText(title);

    this->mainHBL->addWidget(this->imgBox);
    this->mainHBL->addWidget(this->title);

    this->setLayout(this->mainHBL);
}

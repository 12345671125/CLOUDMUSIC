#include "personalized_simple_box.h"

#include <QVBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include "../Function/networksource.h"
#include <QByteArray>
#include <QThread>
personalized_simple_box::personalized_simple_box(QWidget *parent)
    : QWidget{parent},
    imgBox(new QLabel(this)),
    img(new QImage),
    title(new QLabel),
    mainVBL(new QVBoxLayout(this)),
    workThread(new QThread(this))
{
//    this->setFixedHeight(220);
//    this->setFixedWidth(240);
    this->setAttribute(Qt::WA_StyledBackground);
    this->mainVBL->setSpacing(0);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);

    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->imgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->title->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

//    this->title->setWordWrap(true); //文本自动换行

    this->mainVBL->addWidget(this->imgBox,4);
    this->mainVBL->addWidget(this->title,1);
    this->imgBox->setScaledContents(true);

    this->setLayout(this->mainVBL);
}

void personalized_simple_box::init(QJsonObject json_obj)
{
    if(json_obj.isEmpty()){
        QPixmap pixmap(":/img/testImg.png");
        pixmap.scaled(this->imgBox->size(),Qt::KeepAspectRatio);
        this->imgBox->setPixmap(pixmap);
        this->title->setText("无");
    }else{
        if(json_obj.contains("name") && json_obj.contains("picUrl")){
            QString picUrl = json_obj.value("picUrl").toVariant().toString();
            this->networkSrc = new networkSource();
            QObject::connect(this,SIGNAL(getNetworkSrc(QString)),this->networkSrc,SLOT(getNetworkSource(QString)),Qt::QueuedConnection);
            emit this->getNetworkSrc(picUrl);
            QObject::disconnect(this,SIGNAL(getNetworkSrc(QString)),this->networkSrc,SLOT(getNetworkSource(QString)));
            QObject::connect(this->networkSrc,SIGNAL(finished(QByteArray)),this,SLOT(getImg(QByteArray)),Qt::QueuedConnection);
            QObject::connect(this,SIGNAL(imgLoaded()),this->networkSrc,SLOT(erase()));
            networkSrc->moveToThread(this->workThread);
            this->workThread->start();
            //设置超出省略号
            QString newStr = this->title->fontMetrics().elidedText(json_obj.value("name").toVariant().toString(),Qt::ElideRight,this->title->width());
            this->title->setText(newStr);
            this->title->adjustSize();

        }

    }
}

void personalized_simple_box::getImg(QByteArray byteArr)
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArr);
    this->img->loadFromData(byteArr);
    this->img->scaled(this->imgBox->size(),Qt::KeepAspectRatio);
    this->imgBox->setScaledContents(true);
    this->imgBox->setPixmap(QPixmap::fromImage(*this->img));
    emit imgLoaded();
}

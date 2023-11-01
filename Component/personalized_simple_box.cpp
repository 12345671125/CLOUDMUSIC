#include "personalized_simple_box.h"

#include <QVBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include "../Function/networksource.h"
#include <QByteArray>
#include <QThread>
#include <QStyle>
#include <QPainter>
#include "../style.h"
#include <QBitmap>

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
    this->imgBox->setAttribute(Qt::WA_StyledBackground);
    this->title->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

//    this->title->setWordWrap(true); //文本自动换行

    this->mainVBL->addWidget(this->imgBox,4);
    this->mainVBL->addWidget(this->title,1);
    this->imgBox->setScaledContents(true);

    this->setLayout(this->mainVBL);

    this->setStyle("my_personalized_box");
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

void personalized_simple_box::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

void personalized_simple_box::getImg(QByteArray byteArr)
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArr);
//    this->img->loadFromData(byteArr);
    int width = this->imgBox->width();
    int height = this->imgBox->height();
    QSize size(width, height);
    QBitmap mask(size); //给图片上层加一层面具
    QPainter painter(&mask);//画出面具
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 10, 10);//修改这个值，可以改弧度，和直径相等就是圆形
    QPixmap image = pixmap.scaled(size);
    image.setMask(mask);
    image.scaled(this->imgBox->size(),Qt::KeepAspectRatio);
    this->imgBox->setScaledContents(true);
    this->imgBox->setPixmap(image);
    emit imgLoaded();
}

#include "songimg_songtitle.h"
#include "qevent.h"
#include "qstyle.h"

#include <Center/controlbar_left.h>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include "../style.h"
#include "../Center/main_right_stackwidget.h"

songImg_songTitle::songImg_songTitle(QWidget *parent)
    : QWidget{parent},
    parent((controlbar_left*)this->parentWidget()),
    width(this->parent->width * 0.95),
    height(this->parent->height * 0.95),
    title(new QLabel(this)),
    singerName(new QLabel(this)),
    imgBox(new QLabel(this)),
    songImg(new QImage()),
    mainHBL(new QHBoxLayout(this)),
    labelVBL(new QVBoxLayout(this))
{
    if(this->parent != nullptr){
        this->setAttribute(Qt::WA_StyledBackground);
        this->mainHBL->setSpacing(10);
        this->mainHBL->setContentsMargins(15,0,0,0);

        this->imgBox->setScaledContents(true);
        this->imgBox->setFixedSize(80,80);

        this->labelVBL->setSpacing(0);
        this->labelVBL->setContentsMargins(10,0,0,0);

        this->labelVBL->addWidget(this->title);
        this->labelVBL->addWidget(this->singerName);

        this->mainHBL->addWidget(this->imgBox,1);
        this->mainHBL->addLayout(this->labelVBL,2);

        this->setLayout(this->mainHBL);
        qDebug()<<"songimg_songtitle init()";

        this->title->setStyleSheet(".QLabel{font-size:28px;}");
        this->setStyle(my_songImg_songTitle_style);
    }else{
        exit(1);
    }

}

songImg_songTitle &songImg_songTitle::getInstance(QWidget *parent)
{
    static songImg_songTitle instance(parent);
    return instance;
}

void songImg_songTitle::setImgAndTitle(QJsonArray json_arr,QString songName,QString singer)
{
    if(!songName.isEmpty()){
        this->title->setText(songName);
    }
    if(!singer.isEmpty()){
        this->singerName->setText(singer);
    }

    if(!json_arr.empty()){
        QJsonObject json_object = json_arr.at(0).toObject();
        if(json_object.contains("al")){
            QJsonObject json_object_al = json_object.value("al").toObject();
            if(json_object_al.contains("picUrl")){
                QString picUrl = json_object_al.value("picUrl").toVariant().toString();
                QUrl url(picUrl);
                QNetworkAccessManager manager;
                QEventLoop loop;

                // qDebug() << "Reading picture form " << url;
                QNetworkReply *reply = manager.get(QNetworkRequest(url));
                //请求结束并下载完成后，退出子事件循环
                QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                //开启子事件循环
                loop.exec();

                QByteArray jpegData = reply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(jpegData);
                pixmap.scaled(this->imgBox->size());
                this->imgBox->setPixmap(pixmap); // 你在QLabel显示图片
            }
        }
    }else{
        return;
    }
}

void songImg_songTitle::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

void songImg_songTitle::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && !this->title->text().isEmpty() && !this->singerName->text().isEmpty()){
        main_right_stackWidget::getInstance().toSongsDetailPage();
    }
}

void songImg_songTitle::mouseMoveEvent(QMouseEvent *e)
{
    if(!this->title->text().isEmpty() && !this->singerName->text().isEmpty()){
        this->setCursor(Qt::PointingHandCursor);
    }
}

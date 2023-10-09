#include "songsdetailpage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDebug>
#include <QStringList>
#include <QScrollArea>
#include "lyricwidget.h"
#include "../mainwin.h"
#include "qstyle.h"
#include "style.h"

songsDetailPage::songsDetailPage(QWidget *parent)
    : QWidget{parent},
    title(new QLabel(this)),
    singer(new QLabel(this)),
    album(new QLabel(this)),
    imgBox(new QLabel(this)),
    lyricWidget(&lyricWidget::getInstance()),
    mainHBL(new QHBoxLayout(this)),
    rightVBL(new QVBoxLayout()),
    scrollArea(new QScrollArea)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->mainHBL->setContentsMargins(10,10,10,10);
    this->mainHBL->setSpacing(10);
    this->rightVBL->setContentsMargins(0,0,0,0);
    this->rightVBL->setSpacing(0);
    this->rightVBL->setAlignment(Qt::AlignCenter);

    this->title->setAlignment(Qt::AlignCenter);
    this->singer->setAlignment(Qt::AlignCenter);
    this->album->setAlignment(Qt::AlignCenter);
    this->imgBox->setAlignment(Qt::AlignCenter);

    this->imgBox->setScaledContents(true);
    this->imgBox->setFixedSize(500,500);

    this->rightVBL->addWidget(this->title,4);
    this->rightVBL->addWidget(this->singer,1);
    this->rightVBL->addWidget(this->album,1);
    this->rightVBL->addWidget(this->lyricWidget,12);

    this->mainHBL->setAlignment(Qt::AlignCenter);
    this->mainHBL->addWidget(imgBox,1);
    this->mainHBL->addLayout(this->rightVBL,2);
    this->setLayout(this->mainHBL);

    this->setStyle(my_songDetail_style);
    this->title->setStyleSheet(".QLabel{font-size:48px;font-weight:bold;}");
    this->singer->setStyleSheet("font-size:28px;padding:5px;");
    this->album->setStyleSheet("font-size:28px;margin-bottom:20px;padding:5px;");

}

songsDetailPage &songsDetailPage::getInstance()
{
    static songsDetailPage instance;
    return instance;
}
void songsDetailPage::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

void songsDetailPage::setSongLyric(QString songLyric)
{
    if(songLyric.isEmpty()){
        qDebug()<< "getLyric Fault!";
        return;
    }

    this->lyricWidget->setLyric(songLyric);

//    qDebug()<<lyricList;

}

void songsDetailPage::setSongtitle(QString songTitle, QString singer, QString album)
{
    this->title->setText(songTitle);
    this->singer->setText("歌手 : " + singer);
    this->album->setText("专辑 : "+ album);
}

void songsDetailPage::setAlbumPic(QByteArray byteArr)
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArr);
    pixmap.scaled(this->imgBox->size());
    this->imgBox->setPixmap(pixmap); // 你在QLabel显示图片
}

#include "songsdetailpage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDebug>
#include <QStringList>
#include <QScrollArea>
#include "lyricwidget.h"

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
    this->mainHBL->setContentsMargins(0,0,0,0);
    this->mainHBL->setSpacing(0);
    this->rightVBL->setContentsMargins(0,0,0,0);
    this->rightVBL->setSpacing(0);

    this->rightVBL->addWidget(this->title,2);
    this->rightVBL->addWidget(this->singer,1);
    this->rightVBL->addWidget(this->album,1);
    this->rightVBL->addWidget(this->lyricWidget,8);

    this->mainHBL->addWidget(imgBox,1);
    this->mainHBL->addLayout(this->rightVBL,2);
    this->setLayout(this->mainHBL);
}

songsDetailPage &songsDetailPage::getInstance()
{
    static songsDetailPage instance;
    return instance;
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

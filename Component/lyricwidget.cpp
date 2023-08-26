#include "lyricwidget.h"
#include "qstyle.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../style.h"
#include <QScrollArea>
#include <QScrollBar>
#include "player.h"
#include <QDateTime>

lyricWidget::lyricWidget(QWidget *parent)
    : QWidget{parent},
    mainWidget(new QWidget(this)),
    mainVBL(new QHBoxLayout(this)),
    insertVBL(new QVBoxLayout(this->mainWidget)),
    labelArr(new QVector<QLabel* >),
    scrollArea(new QScrollArea(this)),
    lyricList(QStringList()),
    timeList(QStringList())
{

    this->setAttribute(Qt::WA_StyledBackground);
    this->mainWidget->setAttribute(Qt::WA_StyledBackground);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->insertVBL->setSpacing(20);
    this->insertVBL->setContentsMargins(5,5,5,5);
    this->scrollArea->verticalScrollBar()->setMaximum(100);
    this->scrollArea->verticalScrollBar()->setMinimum(0);
    this->insertVBL->setAlignment(Qt::AlignVCenter);

    this->scrollArea->setAlignment(Qt::AlignRight); // 设置滚动条位置
    this->scrollArea->setWidget(this->mainWidget); // 将设置好的幕布嵌入到滚动显示区域
    this->scrollArea->setWidgetResizable(true);

    this->labelArr->clear();

    this->mainVBL->addWidget(this->scrollArea);

    this->setLayout(this->mainVBL);

    this->setStyle(my_lyric_style_def);
}

lyricWidget &lyricWidget::getInstance()
{
    static lyricWidget instance;
    return instance;
}

void lyricWidget::setLyric(QString songLyric)
{
    this->front_H_L_label = nullptr;
    if(songLyric.isEmpty()){
        return;
    }
    QStringList lyricAndTimeList = songLyric.split('\n'); //歌词与时间数组
    QStringList timeList;
    QStringList lyricList;
    timeList.clear();
    lyricList.clear();
    for(QString i :lyricAndTimeList){
        timeList.append(i.mid(i.indexOf('[')+1,i.indexOf(']')-1));
//                qDebug()<<timeList.last();
    }
    for(QString i :lyricAndTimeList){
        lyricList.append(i.mid(i.indexOf(']')+1));
//                qDebug()<<lyricList.last();
    }
    for(int i = 0 ; i<lyricList.count();i++){
        QLabel* label = new QLabel(this->mainWidget);
        label->setText(lyricList.at(i));
        this->labelArr->push_back(label);
        this->insertVBL->addWidget(label);
        label->adjustSize();
        label->setGeometry(QRect(328, 240, 329, 27*4)); //四倍行距
//        QRect()
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
    }
    this->timeList =  timeList;
    this->lyricList = lyricList;
    this->scrollArea->widget()->setLayout(this->insertVBL);
    this->repaint();

}

void lyricWidget::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

void lyricWidget::setScrollBar(int value)
{
    this->scrollArea->verticalScrollBar()->setValue(value);
}

void lyricWidget::addHightLight(qint64 position)
{

//    qDebug()<<position;
    if(!this->lyricList.isEmpty() && !this->timeList.isEmpty()){
//        qDebug()<<"addHightLight";
//        qDebug()<< this->timeList.at(this->currentFlag);
//        qDebug()<<QTime::fromString(this->timeList.at(this->currentFlag)).msec();
        int m = this->timeList.at(this->currentFlag).mid(0,this->timeList.at(this->currentFlag).indexOf(':')).toInt();
        int s = this->timeList.at(this->currentFlag).mid(this->timeList.at(this->currentFlag).indexOf(':')+1,2).toInt();
        int other = this->timeList.at(this->currentFlag).mid(this->timeList.at(this->currentFlag).indexOf('.')+1,2).toInt();
        int msec = m * 60000 + s * 1000 + ((double)other / 100) * 1000;
//        qDebug()<<msec;
        if(position <= msec){
            if(this->front_H_L_label != nullptr){
                this->front_H_L_label->setStyleSheet(my_lyric_style_def);
            }
//            qDebug()<< this->labelArr->at(this->currentFlag);
                this->labelArr->at(this->currentFlag)->style()->unpolish(this->labelArr->at(this->currentFlag));
                this->labelArr->at(this->currentFlag)->setStyleSheet(my_lyric_style_highLight);
                this->labelArr->at(this->currentFlag)->style()->polish(this->labelArr->at(this->currentFlag));
                this->front_H_L_label = this->labelArr->at(this->currentFlag);
                this->labelArr->at(this->currentFlag)->repaint();
        }else{
                this->currentFlag++;
            }

}

}

void lyricWidget::changeScrollBar(qint64 position)
{
    if(Player::getInstance().getDuration()>0){
            int duration = Player::getInstance().getDuration();
            qDebug()<<((double)position / duration) * this->scrollArea->verticalScrollBar()->maximum();
            this->scrollArea->verticalScrollBar()->setValue(((double)position / duration) * this->scrollArea->verticalScrollBar()->maximum());
    }
}

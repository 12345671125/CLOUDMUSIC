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
#include<QMouseEvent>

lyricWidget::lyricWidget(QWidget *parent)
    : QWidget{parent},
    mainWidget(new QWidget(this)),
    mainVBL(new QHBoxLayout(this)),
    insertVBL(new QVBoxLayout(this->mainWidget)),
    labelArr(new QVector<QLabel* >),
    scrollArea(new QScrollArea(this)),
    lyricList(QStringList()),
    timeList(QStringList()),
    scrollTimer(new QTimer(this)),
    checkTimer(new QTimer(this)),
    mutex(QMutex())
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

    this->scrollTimer->setInterval(200);
    this->checkTimer->setInterval(5000);
    this->labelArr->clear();

    this->scrollArea->verticalScrollBar()->hide();

    this->mainVBL->addWidget(this->scrollArea);

    this->setLayout(this->mainVBL);

    this->setStyle(my_lyric_style_def);
    QObject::connect(this->scrollTimer,SIGNAL(timeout()),this,SLOT(changeScrollBar()));
    QObject::connect(this->checkTimer,&QTimer::timeout,[=](){
        this->checkTimer->stop();
        if(this->scrollTimer->isActive() == false){
            this->scrollTimer->start();
        }
    });
}

lyricWidget &lyricWidget::getInstance()
{
    static lyricWidget instance;
    return instance;
}

void lyricWidget::setLyric(QString songLyric)
{
    this->lyricList.clear();
    this->timeList.clear();
    if(!this->labelArr->isEmpty()){
        for(int i = 0;i<labelArr->count();i++){
            delete labelArr->at(i);
        }
        this->labelArr->clear();
    }


    this->front_H_L_label = nullptr;
    if(songLyric.isEmpty()){
        return;
    }

    this->currentFlag = 0;
    this->front_H_L_label = nullptr;

    QStringList lyricAndTimeList = songLyric.split('\n'); //歌词与时间数组
    QStringList timeList;
    QStringList lyricList;
    timeList.clear();
    lyricList.clear();
    for(QString i :lyricAndTimeList){

        QString time = i.mid(i.indexOf('[')+1,i.indexOf(']')-1);
        int m = time.mid(0,time.indexOf(':')).toInt();
        int s = time.mid(time.indexOf(':')+1,2).toInt();
        int other = time.mid(time.indexOf('.')+1,2).toInt();
        qint64 msec = qint64(m * 60000 + s * 1000 + ((double)other / 100) * 1000);
//        qDebug()<<msec;
//        qDebug()<<time;
        timeList.append(QString("%1").arg(msec));
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

void lyricWidget::chargeHightLight(qint64 position)
{
//    mutex.lock();
    if(position>=0 && !this->lyricList.isEmpty() && !this->timeList.isEmpty()){
        for(int i = 1;i<this->lyricList.count();i++){
            if(this->timeList.at(i-1).toInt() < position && position <= this->timeList.at(i).toInt() ){
                qDebug()<<i;
                this->currentFlag = i;
//                addHightLight(position);
                    //                qDebug()<<this->currentFlag;
                    return;
            }
        }
    }else{
        return;
    }
//    mutex.unlock();
}

void lyricWidget::addHightLight(qint64 position)
{
//    mutex.lock();
    if(!this->lyricList.isEmpty() && !this->timeList.isEmpty()){
        if(position <= this->timeList.at(this->currentFlag).toInt()){
            if(this->front_H_L_label != nullptr){
//                this->front_H_L_label->style()->unpolish(this);
                this->front_H_L_label->setStyleSheet("font-size:34px;font-family:Microsoft YaHei;border:none;");
//                this->front_H_L_label->style()->polish(this);
                this->front_H_L_label->repaint();
            };
            if(this->currentFlag>0){
                //                this->labelArr->at(this->currentFlag-1)->style()->unpolish(this->labelArr->at(this->currentFlag-1));
                this->labelArr->at(this->currentFlag-1)->setStyleSheet("font-size:40px;font-family:Microsoft YaHei;color:#d81e06;font-weight:bold;");
                //                this->labelArr->at(this->currentFlag-1)->style()->polish(this->labelArr->at(this->currentFlag-1));
                this->front_H_L_label = this->labelArr->at(this->currentFlag-1);
                this->labelArr->at(this->currentFlag)->repaint();
            }

        }else{
            if(this->currentFlag>=this->timeList.count()-1){
                this->currentFlag = this->timeList.count()-1;
            }else{
                this->currentFlag++;
                }
            }
//        mutex.unlock();
}

}

void lyricWidget::changeTimerStatus(QMediaPlayer::State state)
{
if(state == QMediaPlayer::PlayingState){
            this->scrollTimer->start();
}else if(state == QMediaPlayer::PausedState ||state == QMediaPlayer::StoppedState){
            this->scrollTimer->stop();
}
}

void lyricWidget::wheelEvent(QWheelEvent *event)
{
//    qDebug()<<"wheelEvent";
    if(this->scrollTimer->isActive() == true){
            this->scrollTimer->stop();
            this->checkTimer->start();
}

}

void lyricWidget::changeScrollBar()
{
    if(Player::getInstance().getDuration()>0){
//            int duration = Player::getInstance().getDuration();
//            qDebug()<<((double)position / duration) * this->scrollArea->verticalScrollBar()->maximum();
            if(this->currentFlag>0)
                this->scrollArea->verticalScrollBar()->setValue(this->scrollArea->verticalScrollBar()->maximum()/this->timeList.count() * (this->currentFlag-1));

    }
}

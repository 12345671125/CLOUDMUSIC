#include "mainwin.h"
#include "QGuiApplication"
#include <QScreen>
#include <QVBoxLayout>
#include "Top/topwidget.h"
#include "Center/mainwidget.h"
#include "QApplication"

mainWin::mainWin(QWidget *parent)
    : QWidget(parent),
    screen(QGuiApplication::primaryScreen()),
    mainVBL(new QVBoxLayout(this)),
    realW(screen->availableVirtualGeometry().width()),
    realH(screen->availableVirtualGeometry().height()),
    initW(realW * 1080 / 1920),
    initH(realH * 680 / 1080),
    c_Position(QCursor::pos()),
    Dragging(false)
{
    this->resize(this->initW,this->initH);
    this->setWindowIcon(QIcon(QPixmap(":/img/logo.png")));
    QCoreApplication::setApplicationName("CloudMusic");
    QCoreApplication::setApplicationVersion("1.0");


    this->topWidget = &topWidget::getInstance(this);
    this->centerWidget = &mainWidget::getInstance(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground,true);
    setAttribute(Qt::WA_TranslucentBackground);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->mainVBL->setSpacing(0);

    this->mainVBL->addWidget(this->topWidget);
    this->mainVBL->addWidget(this->centerWidget);

    QApplication* app;
    this->f_Position = QPoint((app->primaryScreen()->size().width() - this->width())/2,(app->primaryScreen()->size().height() - this->height())/2);
//    qDebug()<<this->f_Position;
    this->setStyleSheet(".myMain{border:none;border-radius:5px;margin:0px;padding:0px;}");

    this->setLayout(this->mainVBL);
}

mainWin &mainWin::getInstance(QWidget *parent)
{
    static mainWin instance(parent);
    return instance;
}

mainWin::~mainWin()
{

}


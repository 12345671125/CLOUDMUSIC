#include "mainwin.h"
#include "QGuiApplication"
#include <QScreen>
#include <QVBoxLayout>
#include "Top/topwidget.h"
#include "Center/mainwidget.h"

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

    this->f_Position = QPoint(this->geometry().x(),this->geometry().y());

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


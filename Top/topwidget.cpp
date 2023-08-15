#include "topwidget.h"
#include <QHBoxLayout>
#include "my_top_logowidget.h"
#include "my_top_centerwidget.h"
#include "my_top_rightwidget.h"
#include <QStyle>
#include "mainwin.h"
#include <QMouseEvent>
#include "style.h"

topWidget::topWidget(QWidget *parent)
    : QWidget{parent},
    width(parent->width()),
    height(parent->height() * 0.1),
    mainHBL(new QHBoxLayout(this)),
    logoWidget(&my_top_logoWidget::getInstance(this)),
    centerWidget(&my_top_centerWidget::getInstance(this)),
    rightWidget(&my_top_rightWidget::getInstance(this))
{
    if(parent != nullptr){
        this->resize(this->width,this->height);
        qDebug()<<"topWidget init()";

        this->setAttribute(Qt::WA_StyledBackground);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->setContentsMargins(0,0,0,0);


        this->mainHBL->addWidget(this->logoWidget,3);
        this->mainHBL->addWidget(this->centerWidget,2);
        this->mainHBL->addWidget(this->rightWidget,3);


        this->setLayout(this->mainHBL);
        this->setStyle(my_topWidget_style);
    }else{
        exit(1);
    }

}

topWidget &topWidget::getInstance(QWidget *parent)
{
    static topWidget instance(parent);
    return instance;
}

void topWidget::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}
void topWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        this->setCursor(Qt::SizeAllCursor);
        mainWin::getInstance().Dragging = true;
        mainWin::getInstance().f_Position = QPoint(mainWin::getInstance().geometry().x(),
                                                  mainWin::getInstance().geometry().y());
        mainWin::getInstance().c_Position = QCursor::pos();
    }

}

void topWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mainWin::getInstance().Dragging == true){
        mainWin::getInstance().move(mainWin::getInstance().f_Position + (QCursor::pos() - mainWin::getInstance().c_Position));
    }
}

void topWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    mainWin::getInstance().Dragging = false;
}

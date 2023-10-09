#include "my_top_rightwidget.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include "mainwin.h"
#include "../Component/username_headportrait.h"
#include <QDebug>

#include "topwidget.h"

my_top_rightWidget::my_top_rightWidget(QWidget *parent)
    : QWidget{parent},
    parent((topWidget*)parentWidget()),
    width(this->parent->width * 0.2),
    height(this->parent->height * 0.95),
    quitBtn(new QPushButton(this)),
    fullBtn(new QPushButton(this)),
    minmunBtn(new QPushButton(this)),
    switchStyleBtn(new QPushButton(this)),
    quitIcon(new QIcon(QPixmap(":/img/quit.png"))),
    fullIcon(new QIcon(QPixmap(":/img/full.png"))),
    minmunIcon(new QIcon(QPixmap(":/img/collapse.png"))),
    normalSizeIcon(new QIcon(QPixmap(":/img/normal.png"))),
    lightIcon(new QIcon(QPixmap(":/img/Light.png"))),
    nightIcon(new QIcon(QPixmap(":/img/Night.png"))),
    mainHBL(new QHBoxLayout(this)),
    username_headportrait_widget(&username_headportrait::getInstance(this))
{
    if(parent != nullptr){
        this->setAttribute(Qt::WA_StyledBackground,true); //使控件使用自定义样式
        this->setAttribute(Qt::WA_TranslucentBackground); //设置控件背景透明
        this->mainHBL->setSpacing(0);

        this->minmunBtn->setIcon(*this->minmunIcon);
        this->fullBtn->setIcon(*this->fullIcon);
        this->quitBtn->setIcon(*this->quitIcon);
        this->switchStyleBtn->setIcon(*this->nightIcon);

        this->minmunBtn->setFocusPolicy(Qt::NoFocus);
        this->fullBtn->setFocusPolicy(Qt::NoFocus);
        this->quitBtn->setFocusPolicy(Qt::NoFocus);
        this->switchStyleBtn->setFocusPolicy(Qt::NoFocus);

        this->mainHBL->setAlignment(Qt::AlignRight);
        this->mainHBL->setSpacing(15);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->quitBtn->setFlat(true);
        this->fullBtn->setFlat(true);
        this->minmunBtn->setFlat(true);
        this->switchStyleBtn->setFlat(true);
        this->fullBtn->setMaximumSize(32,32);
        this->minmunBtn->setMaximumSize(32,32);
        this->quitBtn->setMaximumSize(32,32);
        this->switchStyleBtn->setMaximumSize(32,32);

        this->resize(128,32);

        this->mainHBL->addWidget(this->username_headportrait_widget);
        this->mainHBL->addWidget(switchStyleBtn);
        this->mainHBL->addWidget(minmunBtn);
        this->mainHBL->addWidget(fullBtn);
        this->mainHBL->addWidget(quitBtn);
        this->setLayout(this->mainHBL);
        QObject::connect(this->quitBtn,SIGNAL(clicked()),this,SLOT(quit()));
        QObject::connect(this->fullBtn,SIGNAL(clicked()),this,SLOT(fullScreen()));
        QObject::connect(this->minmunBtn,SIGNAL(clicked()),this,SLOT(minmun()));
        QObject::connect(this->switchStyleBtn,SIGNAL(clicked()),this,SLOT(switchStyle()));

        qDebug()<<"top_right init()";
    }else{
        exit(1);
    }

}

my_top_rightWidget::~my_top_rightWidget()
{

}

my_top_rightWidget &my_top_rightWidget::getInstance(QWidget *parent)
{
    static my_top_rightWidget instance(parent);
    return instance;
}
void my_top_rightWidget::quit()
{
    QApplication* a;
    a->quit();
}

void my_top_rightWidget::fullScreen()
{
    if(this->hasFull == false){
//        qDebug()<<"full";
        this->hasFull = true;
        mainWin::getInstance().showMaximized();  //最大化主窗口
        this->fullBtn->setIcon(*this->normalSizeIcon);
        mainWin::getInstance().repaint();
    }else{
//        qDebug()<< "min";
        this->hasFull = false;
        mainWin::getInstance().showNormal();
        //        myMain::getInstance().adjustSize();
        this->fullBtn->setIcon(*this->fullIcon);
        mainWin::getInstance().move(mainWin::getInstance().f_Position);
        mainWin::getInstance().repaint();
    }

}

void my_top_rightWidget::minmun()
{
    mainWin::getInstance().showMinimized(); //最小化主窗口
}

void my_top_rightWidget::switchStyle()
{
    if(this->hasLight == false){
        this->switchStyleBtn->setIcon(*this->nightIcon);
        this->hasLight = true;

    }else{
        this->switchStyleBtn->setIcon(*this->lightIcon);
        this->hasLight = false;
    }
}

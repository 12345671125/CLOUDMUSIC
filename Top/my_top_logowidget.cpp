#include "my_top_logowidget.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include "../style.h"
#include <QStyle>
#include<QCoreApplication>
#include "topwidget.h"

my_top_logoWidget::my_top_logoWidget(QWidget *parent)
    : QWidget{parent},
    parent((topWidget*)parentWidget()),
    width(this->parent->width * 0.2),
    height(this->parent->height * 0.95),
    titleLabel(new QLabel(this)),
    logoButton(new QPushButton(this)),
    logoIcon(new QIcon(QPixmap(":/img/music.png"))),
    mainHBL(new QHBoxLayout(this))
{
    if(parent != nullptr){
        this->resize(width,height);
        qDebug()<<"logo init()";

        this->setAttribute(Qt::WA_StyledBackground); //设置widget应用样式
        this->logoButton->setFlat(true); //设置按钮背景为透明
        this->logoButton->setFocusPolicy(Qt::NoFocus); //去除选中焦点效果
        this->mainHBL->setContentsMargins(10,0,0,0); //设置布局默认内边距为0
        this->mainHBL->setAlignment(Qt::AlignLeft); //将布局中的内容向左排列
        this->mainHBL->setSpacing(5);
        this->titleLabel->setText(QCoreApplication::applicationName());
        this->titleLabel->setAlignment(Qt::AlignCenter);

        /*Button*/
        this->logoButton->setIcon(*this->logoIcon);
        //    this->logoButton->setEnabled(false);

        /*将widget加入布局*/
        this->mainHBL->addWidget(logoButton);
        this->mainHBL->addWidget(titleLabel);

        /*设置布局*/
        this->setLayout(this->mainHBL);

        this->setStyle(my_logoWidget_style); //应用样式表
    }else{
        exit(1);
    }
}

my_top_logoWidget &my_top_logoWidget::getInstance(QWidget *parent)
{
    static my_top_logoWidget instance(parent);
    return instance;
}

void my_top_logoWidget::setStyle(QString style)   //用于动态的应用样式表
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

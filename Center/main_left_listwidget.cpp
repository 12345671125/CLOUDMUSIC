#include "main_left_listwidget.h"

#include <QHBoxLayout>
#include <QListWidget>
#include "../Component/my_listwidgetitem.h"
#include "mainwidget.h"

main_left_listWidget::main_left_listWidget(QWidget *parent)
    : QWidget{parent},
    parent((mainWidget*)parentWidget()),
    width(this->parent->width * 0.2),
    height(this->parent->height),
    listWidget(new QListWidget(this)),
    mainHBL(new QHBoxLayout(this))
{
    if(parent != nullptr){

        this->resize(this->width,this->height);
        qDebug()<<"mylistWidget init()";

        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setSpacing(0);

        this->addItem_To_listWidget("推荐",":/img/recommend.png");
        this->addItem_To_listWidget("音乐馆",":/img/music.png");
        this->addItem_To_listWidget("我喜欢",":/img/like.png");
        this->addItem_To_listWidget("最近播放",":/img/early.png");

        this->listWidget->setFocusPolicy(Qt::NoFocus);
        this->listWidget->setSpacing(2);

        this->mainHBL->addWidget(this->listWidget);
        this->setLayout(mainHBL);
    }else{
        exit(1);
    }
}

main_left_listWidget &main_left_listWidget::getInstance(QWidget *parent)
{
    static main_left_listWidget instance(parent);
    return instance;
}

void main_left_listWidget::addItem_To_listWidget(QString title, QString imgPath)
{
    my_ListWidgetItem* ListItemWidget = new my_ListWidgetItem(title,imgPath,this);
    QListWidgetItem* ListItem = new QListWidgetItem(this->listWidget);
    this->listWidget->addItem(ListItem);
    this->listWidget->setItemWidget(ListItem,ListItemWidget);
}

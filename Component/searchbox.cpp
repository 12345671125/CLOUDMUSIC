#include "searchbox.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <../style.h>
#include <QStyle>
#include "my_top_centerwidget.h"

SearchBox::SearchBox(QWidget *parent)
    : QWidget{parent},
    parent((my_top_centerWidget*)parentWidget()),
    width(this->parent->width * 0.4),
    height(this->parent->height * 0.95),
    search_input(new QLineEdit(this)),
    search_Icon(new QIcon(QPixmap(":/img/search.png"))),
    search_btn(new QPushButton(this)),
    mainHBL(new QHBoxLayout(this))
{
    if(parent != nullptr){
        this->resize(width,height);
        qDebug()<<"Search init";
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainHBL->setContentsMargins(0,0,0,0);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->mainHBL->setSpacing(0);

        this->search_btn->setFlat(true);
        this->search_btn->setIcon(*this->search_Icon);


        this->mainHBL->addWidget(this->search_input);
        this->mainHBL->addWidget(this->search_btn);

        this->setStyle(my_searchBox_style);



    }else{
        exit(1);
    }
}

SearchBox::~SearchBox()
{

}

SearchBox &SearchBox::getInstance(QWidget *parent)
{
    static SearchBox instance(parent);
    return instance;
}

void SearchBox::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

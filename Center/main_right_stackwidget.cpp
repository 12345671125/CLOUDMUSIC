#include "main_right_stackwidget.h"
#include "mainwidget.h"
#include "../Component/searchpage.h"
#include "../Component/songsdetailpage.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDebug>


main_right_stackWidget::main_right_stackWidget(QWidget *parent)
    : QWidget{parent},
    parent((mainWidget*)parentWidget()),
    width(this->parent->width * 0.7),
    height(this->parent->height * 0.4),
    mainVBL(new QVBoxLayout(this)),
    stackedWidget(new QStackedWidget(this)),
    searchPage(&SearchPage::getInstance()),
    songsDetailPage(&songsDetailPage::getInstance())
{
    if(parent != nullptr){
        this->resize(width,height);
        this->setAttribute(Qt::WA_StyledBackground,true);
        this->mainVBL->setSpacing(0);
        this->setContentsMargins(0,0,0,0);

        this->stackedWidget->setAttribute(Qt::WA_StyledBackground);
        this->stackedWidget->setContentsMargins(0,0,0,0);
        this->stackedWidget->addWidget(this->searchPage);
        this->stackedWidget->addWidget(this->songsDetailPage);
        this->stackedWidget->setCurrentWidget(nullptr);

        this->mainVBL->addWidget(this->stackedWidget);
        this->setLayout(this->mainVBL);
        qDebug()<<"mystackWidget init()";
    }else{
        exit(1);
    }
}

main_right_stackWidget &main_right_stackWidget::getInstance(QWidget *parent)
{
    static main_right_stackWidget instance(parent);
    return instance;
}

void main_right_stackWidget::toSearchPage(QString input)
{
    this->stackedWidget->setCurrentWidget(this->searchPage);
    this->searchPage->getSearchContent(input);
}

void main_right_stackWidget::toSongsDetailPage()
{

    if(this->stackedWidget->currentWidget() != this->songsDetailPage){
        this->frontWidget = this->stackedWidget->currentWidget();
        this->stackedWidget->setCurrentWidget(this->songsDetailPage);
    }else{
        this->stackedWidget->setCurrentWidget(this->frontWidget);
    }


}

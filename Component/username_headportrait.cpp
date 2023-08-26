#include "username_headportrait.h"

#include "../Top/my_top_rightWidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <qrcode_page.h>
#include <Function/login_by_qr_code.h>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

username_headportrait::username_headportrait(QWidget *parent)
    : QWidget{parent},
    parent((my_top_rightWidget*)parentWidget()),
    width(this->parent->width * 0.3),
    height(this->parent->height * 0.95),
    mainHBL(new QHBoxLayout(this)),
    headportrait(new QIcon(QPixmap(":/img/default_head_portrait.png"))),
    imgBox(new QPushButton(this)),
    username(new QLabel(this))
{
    if(this->parent != nullptr){
        this->resize(this->width,this->height);
        this->setAttribute(Qt::WA_StyledBackground);
        this->mainHBL->setSpacing(10);
        this->mainHBL->setAlignment(Qt::AlignCenter);
        this->mainHBL->setContentsMargins(0,0,15,0);

        this->username->setText("未登录");

        this->imgBox->setIcon(*this->headportrait);
        this->imgBox->setIconSize(QSize(32,32));
        this->mainHBL->addWidget(imgBox);
        this->mainHBL->addWidget(this->username);

        this->setLayout(this->mainHBL);

        this->setStyleSheet("color:#ffffff;font-size:24px;");

        connect(this->imgBox,SIGNAL(clicked(bool)),this,SLOT(showQrCodePage()));
    }else{
        exit(1);
    }

}

username_headportrait &username_headportrait::getInstance(QWidget* parent)
{
    static username_headportrait instance(parent);
    return instance;
}

void username_headportrait::setHeadPortait(QString imgurl)
{
    QString picUrl = imgurl;
    QUrl url(picUrl);
    QNetworkAccessManager manager;
    QEventLoop loop;

    // qDebug() << "Reading picture form " << url;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    QByteArray jpegData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    this->headportrait->addPixmap(pixmap);
    this->repaint();
}

void username_headportrait::setUserName(QString username)
{
    this->username->setText(username);
}

void username_headportrait::showQrCodePage()
{

    if(codePageFlag == 0){
         QrCode_page::getInstance(login_by_Qr_code::getinstance().getQrCode_Base64()).show();
    }else{
         QrCode_page::getInstance().show();
         login_by_Qr_code::getinstance().startTimer();

    }


}

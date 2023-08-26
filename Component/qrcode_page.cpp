#include "qrcode_page.h"

#include <QCloseEvent>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "Function/login_by_qr_code.h"
#include "Function/getuserinfo.h"
#include "Component/username_headportrait.h"
#include <QDebug>

QrCode_page::QrCode_page(QString base64,QWidget *parent)
    : QWidget{parent},
    imgBox(new QLabel(this)),
    QrCodeImg(new QImage()),
    mainVBL(new QVBoxLayout(this)),
    title(new QLabel(this)),
    flushBtn(new QPushButton(this))
{
    this->title->setText("扫码登录");
    this->setWindowIcon(QPixmap(":/img/logo.png"));
    this->flushBtn->setText("刷新");
    this->flushBtn->hide();

    this->title->setAlignment(Qt::AlignCenter);
    this->resize(177,300);
    this->setAttribute(Qt::WA_StyledBackground);
    this->mainVBL->setSpacing(20);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->getQrCodeImg(base64);
    this->mainVBL->addWidget(title);
    this->imgBox->setFixedSize(180,180);
    this->mainVBL->addWidget(this->imgBox,4);
    this->mainVBL->addWidget(this->flushBtn,1);
    this->mainVBL->setAlignment(Qt::AlignCenter);

    this->setLayout(this->mainVBL);

    this->setStyleSheet("background:#000000;color:white;font-size:24px");

    QObject::connect(&login_by_Qr_code::getinstance(),SIGNAL(codeTimeout(int)),this,SLOT(checkCodeStatues(int)));
    QObject::connect(&login_by_Qr_code::getinstance(),SIGNAL(waitScan(int)),this,SLOT(checkCodeStatues(int)));
    QObject::connect(&login_by_Qr_code::getinstance(),SIGNAL(waitVerify(int)),this,SLOT(checkCodeStatues(int)));
    QObject::connect(&login_by_Qr_code::getinstance(),SIGNAL(loginSuccess(int)),this,SLOT(checkCodeStatues(int)));
    QObject::connect(this->flushBtn,SIGNAL(clicked(bool)),this,SLOT(flushQrcodeImg()));
}

QrCode_page &QrCode_page::getInstance(QString base64)
{
    static QrCode_page instance(base64);
    return instance;
}

void QrCode_page::getQrCodeImg(QString base64)
{
    this->QrCodeImg->loadFromData(QByteArray::fromBase64(base64.section(",",1).toLatin1()));
    this->imgBox->setPixmap(QPixmap::fromImage(*this->QrCodeImg));
    this->repaint();
}

void QrCode_page::closeEvent(QCloseEvent *e)
{
    login_by_Qr_code::getinstance().stopTimer();
    e->accept();
}

void QrCode_page::checkCodeStatues(int code)
{
    qDebug()<<code;
    switch (code) {
    case 800:
    {
        this->QrCodeImg->load(":/img/oldcard.png");
        this->imgBox->setPixmap(QPixmap::fromImage(*QrCodeImg));
        qDebug()<<"二维码过期";
        this->flushBtn->show();
        this->repaint();
        break;
    }
    case 801:
    {
        break;
    }
    case 802:
    {
        this->QrCodeImg->load(":/img/waitVerify.png");
        this->imgBox->setPixmap(QPixmap::fromImage(*QrCodeImg));
        qDebug()<<"待确认";
        this->repaint();
        break;
    }
    case 803:
    {
        this->close();
        getUserInfo::getInstance().userInfo();
        QString username = getUserInfo::getInstance().getUsername();
        QString userImg = getUserInfo::getInstance().getUsername();
        if(!username.isEmpty() && !userImg.isEmpty()){
            username_headportrait::getInstance().setUserName(username);
            username_headportrait::getInstance().setHeadPortait(userImg);
        }else{
            username_headportrait::getInstance().setUserName("已登录,信息未找到");
        }
        break;
    }
    default:
        break;
    }

}

void QrCode_page::flushQrcodeImg()
{
    getQrCodeImg(login_by_Qr_code::getinstance().getQrCode_Base64());
    this->flushBtn->hide();
}

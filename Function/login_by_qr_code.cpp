#include "login_by_qr_code.h"
#include "Network/myhttphandle.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

login_by_Qr_code::login_by_Qr_code(QObject* parent) :
    QObject(parent),
    checkStatusTimer(new QTimer(this)),
    codeKey(QString())
{

    codeKey.clear();
    this->checkStatusTimer->setInterval(100);
    QObject::connect(checkStatusTimer,SIGNAL(timeout()),this,SLOT(checkStatus()));
}

login_by_Qr_code::~login_by_Qr_code()
{

}

login_by_Qr_code &login_by_Qr_code::getinstance()
{
    static login_by_Qr_code instance;
    return instance;
}

QString login_by_Qr_code::getQrCode_Base64()
{
    QJsonObject JSON;
    QNetworkReply* reply_key = myHttpHandle::getInstance().sendHttpRequest("/login/qr/key","get",JSON,true);
    QEventLoop eventLoop;
    QObject::connect(reply_key,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply_key,SIGNAL(finished()),&eventLoop,SLOT(quit()));

    if(reply_key->error() != QNetworkReply::NoError){
        qDebug()<<reply_key->error();
        return "\0";
    }else{
        QByteArray responseData = reply_key->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
        QJsonObject json_object = json_doc.object().value("data").toObject();
        if(json_object.contains(QString("unikey"))){
            QString unikey = json_object.value(QString("unikey")).toString();
            if(!unikey.isEmpty()){
                this->codeKey = unikey;
            }

            JSON.insert("key",unikey);
            JSON.insert("qrimg","true");
            QNetworkReply* reply_base64 = myHttpHandle::getInstance().sendHttpRequest("/login/qr/create","get",JSON);
            QEventLoop eventLoop;
            QObject::connect(reply_base64,SIGNAL(finished()),&eventLoop,SLOT(quit()));
            eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
            QObject::disconnect(reply_base64,SIGNAL(finished()),&eventLoop,SLOT(quit()));

            if(reply_base64->error() !=QNetworkReply::NoError){
                qDebug() <<reply_base64->error();
            }else{
                QByteArray responseData_base64 = reply_base64->readAll();
                QJsonDocument json_doc_base64 = QJsonDocument::fromJson(responseData_base64);
                QJsonObject json_object_base64 = json_doc_base64.object().value("data").toObject();
                if(json_object_base64.contains("qrimg")){
                    const QString base64 = json_object_base64.value("qrimg").toString();
                    reply_base64->deleteLater();
                    this->checkStatusTimer->start();
                    return base64;
                }
            }

        }
        qDebug()<<json_object;
    }
    reply_key->deleteLater();

}

void login_by_Qr_code::stopTimer()
{
    this->checkStatusTimer->stop();
}

void login_by_Qr_code::startTimer()
{
    this->checkStatusTimer->start();
}

void login_by_Qr_code::checkStatus()
{
    if(!this->codeKey.isEmpty())
    {
        QJsonObject JSON;
        JSON.insert("key",this->codeKey);
        JSON.insert("noCookie","true");
        QNetworkReply* reply = myHttpHandle::getInstance().sendHttpRequest("/login/qr/check","get",JSON,true);
        QEventLoop eventLoop;
        QObject::connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        QObject::disconnect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
        if(reply->error() == QNetworkReply::NoError){
            QByteArray responseData = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
            QJsonObject json_object = json_doc.object();
            if(json_object.contains("code")){
                    switch (json_object.value("code").toInt()) {
                    case 800:
                    {
                        this->checkStatusTimer->stop();
                        emit codeTimeout(800);
                        qDebug()<<"二维码过期";
                        break;
                    }
                    case 801:
                    {
                        emit waitScan(801);
                        qDebug()<<"等待扫码";
                        break;
                    }
                    case 802:
                    {
                        emit waitVerify(802);
                        qDebug()<<"待确认";
                        break;
                    }
                    case 803:
                    {
                        this->checkStatusTimer->stop();
                        myHttpHandle::getInstance().setCookie(json_object.value("cookie").toString());
                        emit loginSuccess(803);
                        qDebug()<<"授权登录成功";
                        break;
                    }
                    default:
                        break;
                    }

            }else{
                return;
            }

        }else{
            qDebug()<<reply->error();
            return;
        }

    }
    else
    {
        return;
    }
}

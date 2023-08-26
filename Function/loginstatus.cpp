#include "loginstatus.h"
#include "QJsonObject"
#include "../Network/myhttphandle.h"
#include <QEventLoop>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>

loginStatus::loginStatus():
    uid(QString())
{
    this->uid.clear();
}

int loginStatus::getloginStatus()
{
    QJsonObject JSON;
    QNetworkReply* reply  =  myHttpHandle::getInstance().sendHttpRequest("/login/status","get",JSON,true);
    QEventLoop eventLoop;
    QObject::connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    if(reply->error() == QNetworkReply::NoError){
        QByteArray responseData = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
        QJsonObject json_object = json_doc.object().value("data").toObject();
        if(json_object.value("code").toInt() == 200 && json_object.contains("account")){
            QJsonObject json_object_account = json_object.value("account").toObject();
            if(json_object_account.contains("id")){
//                int a = json_object_account.value("id").toVariant().toDouble();
                QString i;
                i.clear();
                i   = json_object_account.value("id").toVariant().toString();
                this->uid = i;

            }
            if(json_object_account.value("status").toInt() == 1000){
                return LOGINSTATUS_HASLOGIN;
            }else{
                return LOGINSTATUS_OTHER;
            }
        }
        else
        {
            return LOGINSTATUS_ERROR;
        }

    }
    else
    {
        qDebug()<<reply->error();
        return LOGINSTATUS_ERROR;
    }


}

loginStatus &loginStatus::getinstance()
{
    static loginStatus instance;
    return instance;
}

QString loginStatus::getUid()
{
    return this->uid;
}

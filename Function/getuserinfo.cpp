#include "getuserinfo.h"
#include "../Network/myhttphandle.h"
#include "QJsonObject"
#include "loginstatus.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QDebug>

getUserInfo::getUserInfo()
{

}

getUserInfo &getUserInfo::getInstance()
{
    static getUserInfo instance;
    return instance;
}

bool getUserInfo::userInfo()
{
    if(loginStatus::getinstance().getloginStatus() == loginStatus::LOGINSTATUS_HASLOGIN){
        QJsonObject JSON;
        QString uid = loginStatus::getinstance().getUid();
        if(uid.isEmpty()){
            return false;
        }
        JSON.insert("uid",uid);
        QNetworkReply* reply  =  myHttpHandle::getInstance().sendHttpRequest("/user/detail","get",JSON,true);
        QEventLoop eventLoop;
        QObject::connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        QObject::disconnect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
        if(reply->error() == QNetworkReply::NoError){
            QByteArray responseData = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
            QJsonObject json_object = json_doc.object();
            if(json_object.contains("profile")){
                QJsonObject json_object_profile = json_object.value("profile").toObject();
                if(json_object_profile.contains("nickname")){
                    this->username = json_object_profile.value("nickname").toVariant().toString();
                }
                if(json_object_profile.contains("avatarUrl")){
                    this->userImg = json_object_profile.value("avatarUrl").toVariant().toString();
                }
                return true;
            }else{
                return false;
            }


        }
        else
        {
            qDebug()<<reply->error();
            return false;
        }
    }

}

QString getUserInfo::getUsername()
{
    return this->username;
}

QString getUserInfo::getUserImg()
{
    return this->userImg;
}

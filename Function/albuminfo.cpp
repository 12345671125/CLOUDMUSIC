#include "albuminfo.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "Network/myhttphandle.h"
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

albumInfo::albumInfo()
{

}

albumInfo &albumInfo::getInstance()
{
    static albumInfo instance;
    return instance;
}

QJsonArray albumInfo::getAlbumInfo(QString id)
{
    if(!id.isEmpty()){
        QJsonObject JSON;
        JSON.insert("id",id);
        QNetworkReply* reply =  myHttpHandle::getInstance().sendHttpRequest("/album","get",JSON,false);
        QEventLoop eventloop;
        QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
        eventloop.exec(QEventLoop::ExcludeUserInputEvents);//程序阻塞，进入事件循环，等待请求结束
        QObject::disconnect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
        if(reply->error() == QNetworkReply::NoError){
            QByteArray byteArray = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(byteArray);
            QJsonObject json_object= json_doc.object();
            if(json_object.contains("songs")){
                QJsonArray json_songArray = json_object.value("songs").toArray();
                return json_songArray;
            }else{
                QJsonArray arrNull;
                return arrNull;
            }


        }else{
            qDebug()<<reply->error();
            QJsonArray arrNull;
            return arrNull;
        }
    }else{
        QJsonArray arrNull;
        return arrNull;
    }

}

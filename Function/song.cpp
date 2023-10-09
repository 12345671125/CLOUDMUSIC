#include "song.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <Network/myhttphandle.h>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include <QJsonArray>

song::song()
{

}

song &song::getInstance()
{
    static song instance;
    return instance;
}

bool song::isVaild(QString id)  //查看歌曲是否合法
{
    QJsonObject JSON;
    JSON.insert("id",id);
    QNetworkReply* reply = myHttpHandle::getInstance().sendHttpRequest("/check/music","get",JSON,true);
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray byteArray = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(byteArray);
        QJsonObject json_object = json_doc.object();
        if(json_object.contains("message")){
            if(json_object.value("message").toVariant().toString().compare("ok") == 0){
                return true;
            }else{
                return false;
            }
        }
    }
    else
    {
        qDebug()<<reply->error();
        return false;
    }
}

QString song::getSong(QString id)  //获取歌曲url
{
    QJsonObject JSON;
    QString url;
    url.clear();
    JSON.insert("id",id);
    JSON.insert("level","exhigh");
    QEventLoop eventloop;
    QNetworkReply* reply = myHttpHandle::getInstance().sendHttpRequest("/song/url/v1","get",JSON,true);
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    if(reply->error() == QNetworkReply::NoError){
        QByteArray byteArray = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(byteArray);
        QJsonObject json_object = json_doc.object();
        if(json_object.contains("data") && json_object.value("code").toInt() == 200){
            QJsonObject json_object_data = json_doc.object().value("data").toArray().at(0).toObject();
            if(json_object_data.contains("url")){
                qDebug()<< json_object_data.value("url").toVariant().toString();
                return json_object_data.value("url").toVariant().toString();
            }
    }else{
            return url;
        }



    }else{
        qDebug()<<reply->error();
        return url;
    }
}

#include "search.h"
#include "qjsonarray.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <Network/myhttphandle.h>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

search::search()
{

}

search &search::getinstance()
{
    static search instance;
    return instance;
}

QJsonArray search::getSearchContent(QString input)
{
    QJsonObject JSON;
    JSON.insert("keywords",input);
    QNetworkReply* reply =  myHttpHandle::getInstance().sendHttpRequest("/search","get",JSON,false);
    QEventLoop eventloop;
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    if(reply->error() == QNetworkReply::NoError){
        QByteArray byteArray = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(byteArray);
        QJsonObject json_object= json_doc.object();
        if(json_object.contains("result")){
            QJsonArray json_songArray = json_object.value("result").toObject().value("songs").toArray();
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

}

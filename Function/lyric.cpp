#include "lyric.h"

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QJsonDocument>
#include <Network/myhttphandle.h>
#include <QEventLoop>

lyric::lyric()
{

}

lyric &lyric::getInstance()
{
    static lyric instance;
    return instance;
}

QString lyric::getSongLyric(QString songId)
{
    QJsonObject JSON;
    QString lyric;
    lyric.clear();
    JSON.insert("id",songId);
    QNetworkReply* reply = myHttpHandle::getInstance().sendHttpRequest("/lyric","get",JSON);
    QEventLoop eventLoop;
    QObject::connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray byteArr = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(byteArr);
        QJsonObject json_object = json_doc.object();
        if(json_object.contains("lrc") && json_object.value("code").toInt() == 200){
            QJsonObject json_object_lrc =  json_object.value("lrc").toObject();
            lyric = json_object_lrc.value("lyric").toVariant().toString();
            return lyric;

        }
    }
    else
    {
        qDebug()<<reply->error();
        return lyric;
    }
}

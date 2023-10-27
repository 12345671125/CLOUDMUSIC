#include "personalized_f.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QJsonDocument>
#include <Network/myhttphandle.h>
#include <QEventLoop>

personalized_f::personalized_f()
{

}

personalized_f &personalized_f::getInstance()
{
    static personalized_f instance;
    return instance;
}

QJsonArray personalized_f::getpersonalized_f()
{
    QJsonObject object;
    QNetworkReply* reply = myHttpHandle::getInstance().sendHttpRequest("/personalized?limit=10","get",object);//发送http请求
    QEventLoop eventloop;
    QJsonArray json_arr; //存放请求结果
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    if(reply->error() == QNetworkReply::NoError){
        QByteArray byteArray = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(byteArray);
        if(!json_doc.isEmpty()){
            QJsonObject  json_obj= json_doc.object();
            if(json_obj.contains("code") && json_obj.value("code") == 200 && json_obj.contains("result")){
                json_arr = json_obj.value("result").toArray();
                return json_arr;

            }else{
                qDebug()<<"httpcode:"<<json_obj.value("code")<<";请求数据时发生未知错误! 请重试";
                return json_arr;
            }

        }else{
            qDebug()<<"请求数据时发生未知错误! 请重试";
            return json_arr;
        }
    }else{
        qDebug()<<reply->error();
        return json_arr;
    }



}

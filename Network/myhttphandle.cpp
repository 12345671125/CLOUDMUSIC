#include "myhttphandle.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

myHttpHandle::myHttpHandle(QObject* parent):
    QObject(parent),
    networkManager(new QNetworkAccessManager(nullptr)),
    baseUrl(new QUrl()),
    timeT(QDateTime::currentDateTime().toMSecsSinceEpoch())
{
    init();
}

myHttpHandle &myHttpHandle::getInstance()
{
    static myHttpHandle instance;
    return instance;
}

QNetworkReply* myHttpHandle::sendHttpRequest(QString appendUrl, QString requestMethod, QJsonObject Json_object,bool needTimeStamp)
{
    QUrl url = QUrl(this->baseUrl->toString().append(appendUrl));
    QNetworkReply* reply = nullptr;
    QNetworkRequest  request;
    if(!url.isValid()){
        qDebug()<<"请求的url不合法!";
        return reply;
    }
    if(needTimeStamp == true){
        this->timeT = QDateTime::currentDateTime().toMSecsSinceEpoch();
        Json_object.insert("timestamp",QString("%1").arg(this->timeT));
    }
    if(!this->Cookie.isEmpty()){
//        qDebug()<<"addcookie"<<Cookie;
        Json_object.insert("cookie",this->Cookie);
    }
    if(requestMethod.compare("get") == 0)
    {
        if(!Json_object.isEmpty()){
           QString newUrl = url.toString();
           newUrl.append("?");
           QJsonObject::Iterator it ;
            for(it = Json_object.begin();it!=Json_object.end();it++){
               if(it !=Json_object.begin()){
                    newUrl.append("&");
                }
               newUrl.append(it.key());
               newUrl.append("=");
               newUrl.append(it.value().toString());
           }
//            qDebug()<<newUrl;
           request.setUrl(newUrl);
           reply =  this->networkManager->get(request);
           return reply;
        }
        request.setUrl(url);
        reply =  this->networkManager->get(request);
        return reply;
    }
    else if(requestMethod.compare("post") == 0)
    {
        if(Json_object.isEmpty()){
            qDebug()<<"JSON对象为空!";
            return reply;
        }else{
            QJsonDocument json_documnent = QJsonDocument();
            json_documnent.setObject(Json_object);
            QByteArray byteArray = json_documnent.toJson(QJsonDocument::Compact);
            request.setUrl(url);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            reply =  this->networkManager->post(request,byteArray);
            return reply;
            qDebug()<<byteArray;
        }
    }

    return reply;

}

QString myHttpHandle::getCookie()
{
    return this->Cookie;
}

void myHttpHandle::setCookie(QString cookie)
{
    this->Cookie = cookie;
}

void myHttpHandle::init()
{
    QString projectDirPath = QCoreApplication::applicationDirPath();
//    qDebug()<<projectFilePath;
    QFile* config =  new QFile(projectDirPath.append("/config.conf"));
    if(!config->exists())
    {
        qDebug()<<"网络配置文件缺失,网络模块初始化失败";
        exit(1);
    }
    if(config->open(QIODevice::ReadOnly))
    {
        QString str = QString::fromUtf8(config->readAll());
        QString ipStr = str.mid(str.indexOf("server_address"),str.indexOf(';') - str.indexOf("server_address") );
        QString portStr = str.mid(str.indexOf("port"),str.lastIndexOf(';') - str.indexOf("port") );
//        qDebug()<<ipStr;
//        qDebug() <<portStr;
        QString ip = ipStr.mid(ipStr.indexOf(':')+1);
        QString port = portStr.mid(portStr.indexOf(':')+1);
        QString baseUrl = ip.append(":").append(port);
        qDebug()<<"server_url:"<<baseUrl;
        this->baseUrl = new QUrl(baseUrl);
        if(!this->baseUrl->isValid()){
            qDebug()<<"服务器地址不合法!";
            exit(1);
        }

    }else
    {
        qDebug()<<"配置文件打开失败";
        exit(1);
    }

//    QObject::connect(this->networkManager,SIGNAL(finished(QNetworkReply*)),this,)
}

#include "networksource.h"
#include <QByteArray>
#include <QString>
//#include "../Network/myhttphandle.h"
#include <QNetworkReply>
#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QNetworkAccessManager>

networkSource::networkSource(QObject* parent):
    QObject(parent),
    networkManager(new QNetworkAccessManager(this))
{
//    this->getNetworkSource(url);
}
void networkSource::getNetworkSource(QString url)
{
    QByteArray byteArr;
    QJsonObject json_obj;
    byteArr.clear();
    if(url.isEmpty()){
        return;
    }
    QEventLoop eventloop;
    QNetworkReply* reply = this->pushHttpRequest(url,"get");
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec(QEventLoop::ExcludeUserInputEvents);
    QObject::disconnect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    byteArr = reply->readAll();
    emit finished(byteArr);
}

void networkSource::erase()
{
    QThread::currentThread()->exit();
    QThread::currentThread()->deleteLater();
}
QNetworkReply *networkSource::pushHttpRequest(QString httpurl, QString requestMethod)
{
    QUrl url = QUrl(httpurl);
    QNetworkReply* reply = nullptr;
    QNetworkRequest  request;
    if(!url.isValid()){
        qDebug()<<"请求的url不合法!";
        return reply;
    }
    if(requestMethod.compare("get") == 0)
    {
        request.setUrl(url);
        reply =  this->networkManager->get(request);
        return reply;
    }
    else if(requestMethod.compare("post") == 0)
    {
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        QByteArray byteArray;
        byteArray.clear();
        reply =  this->networkManager->post(request,byteArray);
        return reply;
    }

    return reply;
}

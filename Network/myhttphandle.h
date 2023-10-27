#ifndef MYHTTPHANDLE_H
#define MYHTTPHANDLE_H

#include <QObject>

QT_BEGIN_NAMESPACE
    class QNetworkRequest;
    class QNetworkReply;
    class QNetworkAccessManager;
    class QNetworkCookieJar;
QT_END_NAMESPACE

class myHttpHandle : public QObject
{
    Q_OBJECT
public:
    myHttpHandle(QObject* parent = nullptr);
    static myHttpHandle& getInstance();
    QNetworkReply* sendHttpRequest(QString appendUrl,QString requestMethod,QJsonObject Json_object,bool needTimeStamp = false);
    QNetworkReply* sendHttpRequest(QString httpurl,QString requestMethod);
    QString getCookie();
    void setCookie(QString cookie);

private:
    QNetworkAccessManager* networkManager = nullptr;
    QUrl* baseUrl = nullptr;
    QString Cookie = "\0";
    int timeT;

    void init();

};

#endif // MYHTTPHANDLE_H

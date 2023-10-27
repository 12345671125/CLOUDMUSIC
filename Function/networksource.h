#ifndef NETWORKSOURCE_H
#define NETWORKSOURCE_H

#include <QObject>
class QByteArray;
class QString;
class QTimer;
class QNetworkReply;
class QNetworkAccessManager;

class networkSource : public QObject
{
     Q_OBJECT
public:
    networkSource(QObject* parent = nullptr);
private:
    QNetworkReply * pushHttpRequest(QString httpurl, QString requestMethod);
    QNetworkAccessManager* networkManager = nullptr;
public slots:
    void getNetworkSource(QString url);
    void erase();
signals:
    void finished(QByteArray result);
};

#endif // NETWORKSOURCE_H

#ifndef PERSONALIZED_SIMPLE_BOX_H
#define PERSONALIZED_SIMPLE_BOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QImage;
class QVBoxLayout;
class QThread;
class networkSource;
QT_END_NAMESPACE

class personalized_simple_box : public QWidget
{
    Q_OBJECT
public:
    explicit personalized_simple_box(QWidget *parent = nullptr);
    void init(QJsonObject json_obj);
    void setStyle(QString style);
private:
    QLabel* imgBox;
    QImage* img;
    QLabel* title;
    QVBoxLayout* mainVBL;
    QThread* workThread;
    networkSource* networkSrc;

signals:
    void getNetworkSrc(QString url);
    void imgLoaded();

private slots:
    void getImg(QByteArray byteArr);


};

#endif // PERSONALIZED_SIMPLE_BOX_H

#ifndef PERSONALIZED_SIMPLE_BOX_H
#define PERSONALIZED_SIMPLE_BOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QImage;
class QVBoxLayout;
QT_END_NAMESPACE

class personalized_simple_box : public QWidget
{
    Q_OBJECT
public:
    explicit personalized_simple_box(QWidget *parent = nullptr);
    void init(QByteArray byteArr,QString title = "test");

private:
    QLabel* imgBox;
    QImage* img;
    QLabel* title;
    QVBoxLayout* mainVBL;

signals:

};

#endif // PERSONALIZED_SIMPLE_BOX_H

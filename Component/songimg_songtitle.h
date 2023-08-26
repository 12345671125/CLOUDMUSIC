#ifndef SONGIMG_SONGTITLE_H
#define SONGIMG_SONGTITLE_H

#include <QWidget>
QT_BEGIN_INCLUDE_NAMESPACE
    class controlbar_left;
    class QLabel;
    class QImage;
    class QHBoxLayout;
    class QVBoxLayout;
QT_END_INCLUDE_NAMESPACE

class songImg_songTitle : public QWidget
{
    Q_OBJECT
public:
    controlbar_left* parent;
    int width;
    int height;
    explicit songImg_songTitle(QWidget *parent = nullptr);
    static songImg_songTitle& getInstance(QWidget *parent = nullptr);
    void setImgAndTitle(QJsonArray json_arr,QString songName,QString singer);
    void setStyle(QString style);
private:
    QLabel* title;
    QLabel* singerName;
    QLabel* imgBox;
    QImage* songImg;
    QHBoxLayout* mainHBL;
    QVBoxLayout* labelVBL;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:

};

#endif // SONGIMG_SONGTITLE_H

#ifndef CONTROLBAR_PROGRESSBAR_H
#define CONTROLBAR_PROGRESSBAR_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QSlider;
class QIcon;
class QHBoxLayout;
class controlbar_center;
class QTimeEdit;
class QMutex;
QT_END_NAMESPACE

class controlbar_progressbar : public QWidget
{
    Q_OBJECT
public:
    controlbar_center* parent;
    int width;
    int height;
    explicit controlbar_progressbar(QWidget *parent = nullptr);
    static controlbar_progressbar& getInstance(QWidget* parent = nullptr);
    void setStyle(QString style);
    int getSliderPostion();
    QMutex* mutex;


public slots:
   void positionCharged(qint64 position);
   void setDuration(qint64 duration);

private:
    QSlider* slider;
    QTimeEdit* leftTimeEdit;
    QTimeEdit* rightTimeEdit;
    QHBoxLayout* mainHBL;
    qint64 duration = -1; //存放当前播放的歌曲时长 -1为当前无歌曲播放
    int flag = 0;

signals:

};

#endif // CONTROLBAR_PROGRESSBAR_H

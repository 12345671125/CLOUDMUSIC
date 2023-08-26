#ifndef CONTROLBAR_BTNG_H
#define CONTROLBAR_BTNG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QIcon;
class QHBoxLayout;
class controlbar_center;
QT_END_NAMESPACE

class controlbar_btnG : public QWidget
{
    Q_OBJECT
public:
    controlbar_center* parent;
    int width;
    int height;
    explicit controlbar_btnG(QWidget *parent = nullptr);
    ~controlbar_btnG();
    static controlbar_btnG& getInstance(QWidget* parent = nullptr);
    void switchPlayAndPause();
    int playState = 0;
public slots:
    void controlMusic();


private:
    QPushButton* startAndpauseBtn;
    QPushButton* frontBtn;
    QPushButton* nextBtn;
    QPushButton* switchModeBtn;
    QIcon* startIcon;
    QIcon* pauseIcon;
    QIcon* frontIcon;
    QIcon* nextIcon;
    QIcon* modeIcon_circle;
    QIcon* modeIcon_random;
    QIcon* modeIcon_onlyone;
    QHBoxLayout* mainHBL;


signals:

};

#endif // CONTROLBAR_BTNG_H

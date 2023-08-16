#ifndef CONTROLBAR_CENTER_H
#define CONTROLBAR_CENTER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class controlbar_btnG;
class controlbar_progressbar;
class main_right_controlBarWidget;
QT_END_NAMESPACE

class controlbar_center : public QWidget
{
    Q_OBJECT
public:
    main_right_controlBarWidget* parent;
    int width;
    int height;
    explicit controlbar_center(QWidget *parent = nullptr);
    static controlbar_center& getInstance(QWidget *parent = nullptr);
private:
    QVBoxLayout* mainVBL;
    controlbar_btnG* btnG;
    controlbar_progressbar* progressbar;

signals:

};

#endif // CONTROLBAR_CENTER_H

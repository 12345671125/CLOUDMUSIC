#ifndef CONTROLBAR_LEFT_H
#define CONTROLBAR_LEFT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class main_right_controlBarWidget;
QT_END_NAMESPACE

class controlbar_left : public QWidget
{
    Q_OBJECT
public:
    main_right_controlBarWidget* parent;
    int width;
    int height;
    explicit controlbar_left(QWidget *parent = nullptr);
    static controlbar_left& getInstance(QWidget *parent = nullptr);

private:
    QHBoxLayout* mainHBL;

signals:

};

#endif // CONTROLBAR_LEFT_H

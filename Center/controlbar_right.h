#ifndef CONTROLBAR_RIGHT_H
#define CONTROLBAR_RIGHT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class main_right_controlBarWidget;
QT_END_NAMESPACE

class controlbar_right : public QWidget
{
    Q_OBJECT
public:
    main_right_controlBarWidget* parent;
    int width;
    int height;
    explicit controlbar_right(QWidget *parent = nullptr);
    static controlbar_right& getInstance(QWidget *parent = nullptr);
private:
    QHBoxLayout* mainHBL;

signals:

};

#endif // CONTROLBAR_RIGHT_H

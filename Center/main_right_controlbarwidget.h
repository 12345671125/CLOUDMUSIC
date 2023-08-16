#ifndef MAIN_RIGHT_CONTROLBARWIDGET_H
#define MAIN_RIGHT_CONTROLBARWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class mainWidget;
class controlbar_left;
class controlbar_center;
class controlbar_right;
QT_END_NAMESPACE

class main_right_controlBarWidget : public QWidget
{
    Q_OBJECT
public:
    mainWidget* parent;
    int width;
    int height;
    explicit main_right_controlBarWidget(QWidget *parent = nullptr);
    static main_right_controlBarWidget& getInstance(QWidget* parent = nullptr);

private:
    QHBoxLayout* mainHBL;
    controlbar_left* leftWidget;
    controlbar_center* centerWidget;
    controlbar_right* rightWidget;

signals:

};

#endif // MAIN_RIGHT_CONTROLBARWIDGET_H

#ifndef MAIN_RIGHT_STACKWIDGET_H
#define MAIN_RIGHT_STACKWIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class mainWidget;
QT_END_NAMESPACE
class main_right_stackWidget : public QWidget
{
    Q_OBJECT
public:
    mainWidget* parent;
    int width;
    int height;
    explicit main_right_stackWidget(QWidget *parent = nullptr);
    static main_right_stackWidget& getInstance(QWidget* parent = nullptr);

signals:

};

#endif // MAIN_RIGHT_STACKWIDGET_H

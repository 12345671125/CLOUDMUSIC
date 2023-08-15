#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class my_top_logoWidget;
class my_top_centerWidget;
class my_top_rightWidget;
QT_END_NAMESPACE

class topWidget : public QWidget
{
    Q_OBJECT
public:
    int width;
    int height;
    explicit topWidget(QWidget *parent = nullptr);
    static topWidget& getInstance(QWidget* parent);
    void setStyle(QString style);


private:
    QHBoxLayout* mainHBL;
    my_top_logoWidget* logoWidget;
    my_top_centerWidget* centerWidget;
    my_top_rightWidget* rightWidget;

protected:
    virtual void mousePressEvent(QMouseEvent* event); //鼠标按下事件
    virtual void mouseMoveEvent(QMouseEvent* event); //鼠标移动事件
    virtual void mouseReleaseEvent(QMouseEvent* event); //鼠标释放事件
signals:

};

#endif // TOPWIDGET_H

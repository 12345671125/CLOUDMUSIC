#ifndef MY_TOP_CENTERWIDGET_H
#define MY_TOP_CENTERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class SearchBox;
class topWidget;
QT_END_NAMESPACE

class my_top_centerWidget : public QWidget
{
    Q_OBJECT
public:
    topWidget* parent;
    int width;
    int height;
    explicit my_top_centerWidget(QWidget *parent = nullptr);
    static my_top_centerWidget& getInstance(QWidget* parent = nullptr);


private:
    QHBoxLayout* mainHBL;
    SearchBox* searchBox;
signals:

};

#endif // MY_TOP_CENTERWIDGET_H

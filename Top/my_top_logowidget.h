#ifndef MY_TOP_LOGOWIDGET_H
#define MY_TOP_LOGOWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QIcon;
class QPushButton;
class QLabel;
class QHBoxLayout;
class topWidget;
QT_END_NAMESPACE

class my_top_logoWidget : public QWidget
{
    Q_OBJECT
public:
    topWidget* parent;
    int width;
    int height;
    explicit my_top_logoWidget(QWidget *parent = nullptr);
    static my_top_logoWidget& getInstance(QWidget *parent = nullptr);
    void setStyle(QString style);

private:
    QLabel* titleLabel; //应用标题
    QPushButton* logoButton; //logo
    QIcon* logoIcon;  //logo图标
    QHBoxLayout* mainHBL;

signals:

};

#endif // MY_TOP_LOGOWIDGET_H

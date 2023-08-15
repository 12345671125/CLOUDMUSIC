#ifndef MY_LISTWIDGETITEM_H
#define MY_LISTWIDGETITEM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
    class QIcon;
    class QPushButton;
    class QLabel;
    class QHBoxLayout;
QT_END_NAMESPACE

class my_ListWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit my_ListWidgetItem(QString title,QString imgPath,QWidget *parent = nullptr);

private:
    QIcon* img;
    QPushButton* imgBox;
    QLabel* title;
    QHBoxLayout* mainHBL;
signals:

};

#endif // MY_LISTWIDGETITEM_H

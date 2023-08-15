#ifndef MAIN_LEFT_LISTWIDGET_H
#define MAIN_LEFT_LISTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListWidget;
class QHBoxLayout;
class mainWidget;
QT_END_NAMESPACE

class main_left_listWidget : public QWidget
{
    Q_OBJECT
public:
    mainWidget* parent;
    int width;
    int height;
    explicit main_left_listWidget(QWidget *parent = nullptr);
    static main_left_listWidget& getInstance(QWidget* parent = nullptr);
    void addItem_To_listWidget(QString title,QString imgPath);

private:
    QListWidget* listWidget;
    QHBoxLayout* mainHBL;

signals:
};

#endif // MAIN_LEFT_LISTWIDGET_H

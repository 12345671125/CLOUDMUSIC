#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
    class main_left_listWidget;
    class main_right_stackWidget;
    class QHBoxLayout;
    class QVBoxLayout;
    class main_right_controlBarWidget;
QT_END_NAMESPACE

class mainWidget : public QWidget
{
    Q_OBJECT
public:
    int width;
    int height;
    explicit mainWidget(QWidget *parent = nullptr);
    static mainWidget& getInstance(QWidget* parent = nullptr);
    void setStyle(QString style);

private:
    main_left_listWidget* listWidget;
    main_right_stackWidget* stackWidget;
    main_right_controlBarWidget* controlBarWidget;
    QHBoxLayout* mainHBL;
    QVBoxLayout* rightHBL;

signals:

};

#endif // MAINWIDGET_H

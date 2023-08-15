#ifndef MY_TOP_RIGHTWIDGET_H
#define MY_TOP_RIGHTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QHBoxLayout;
class QIcon;
QT_END_NAMESPACE

class my_top_rightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit my_top_rightWidget(QWidget *parent = nullptr);
    ~my_top_rightWidget();
    static my_top_rightWidget& getInstance(QWidget* parent = nullptr);

private:
    bool hasFull = false;
    bool hasLight = true;
    QPushButton* quitBtn;
    QPushButton* fullBtn;
    QPushButton* minmunBtn;
    QPushButton* switchStyleBtn;
    QIcon* quitIcon;
    QIcon* fullIcon;
    QIcon* minmunIcon;
    QIcon* normalSizeIcon;
    QIcon* lightIcon;
    QIcon* nightIcon;
    QHBoxLayout* mainHBL;


private slots:
    void quit();
    void fullScreen();
    void minmun();
    void switchStyle();

signals:

};

#endif // MY_TOP_RIGHTWIDGET_H

#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QScreen;
class QVBoxLayout;
class topWidget;
class mainWidget;
QT_END_NAMESPACE

class mainWin : public QWidget
{
    Q_OBJECT

private:
    QScreen* screen; //屏幕对象
    QVBoxLayout* mainVBL;
    topWidget* topWidget;
    mainWidget* centerWidget;

public:
    const int realW; //物理屏幕宽度
    const int realH; //物理屏幕高
    const int initW; //初始化屏幕宽
    const int initH; //初始化屏幕高
    QPoint c_Position; //鼠标位置
    bool Dragging; //是否正在拖动
    QPoint f_Position; //窗口位置
    mainWin(QWidget *parent = nullptr);
    static mainWin& getInstance(QWidget* parent = nullptr);
    ~mainWin();

};
#endif // MAINWIN_H

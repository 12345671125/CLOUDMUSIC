#ifndef CONTROLBAR_PROGRESSBAR_H
#define CONTROLBAR_PROGRESSBAR_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QSlider;
class QIcon;
class QHBoxLayout;
class controlbar_center;
class QTimeEdit;
QT_END_NAMESPACE

class controlbar_progressbar : public QWidget
{
    Q_OBJECT
public:
    controlbar_center* parent;
    int width;
    int height;
    explicit controlbar_progressbar(QWidget *parent = nullptr);
    static controlbar_progressbar& getInstance(QWidget* parent = nullptr);
    void setStyle(QString style);

private:
    QTimeEdit* leftTimeEdit;
    QSlider* slider;
    QTimeEdit* rightTimeEdit;
    QHBoxLayout* mainHBL;

signals:

};

#endif // CONTROLBAR_PROGRESSBAR_H

#ifndef PERSONALIZED_H
#define PERSONALIZED_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class personalized_group_widget;
QT_END_NAMESPACE

class personalized : public QWidget
{
    Q_OBJECT
public:
    explicit personalized(QWidget *parent = nullptr);
    static personalized& getInstance(QWidget* parent = nullptr);
    void setStyle(QString style);
private:
    QLabel* title;
    personalized_group_widget* componentGroup;
    QVBoxLayout* mainVBL;


signals:

};

#endif // PERSONALIZED_H

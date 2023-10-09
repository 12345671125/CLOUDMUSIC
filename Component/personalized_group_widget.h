#ifndef PERSONALIZED_GROUP_WIDGET_H
#define PERSONALIZED_GROUP_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE

class personalized_group_widget : public QWidget
{
    Q_OBJECT
public:
    explicit personalized_group_widget(QWidget *parent = nullptr);
    static personalized_group_widget& getInstance(QWidget* parent = nullptr);

private:
    QGridLayout* mainGBL;

signals:

};

#endif // PERSONALIZED_GROUP_WIDGET_H

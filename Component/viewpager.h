#ifndef VIEWPAGER_H
#define VIEWPAGER_H

#include <QWidget>

class viewpager : public QWidget
{
    Q_OBJECT
public:
    explicit viewpager(QWidget *parent = nullptr);
    static viewpager& getInstance(QWidget* parent = nullptr);

signals:

};

#endif // VIEWPAGER_H

#ifndef CLOUDMUSIC_MAINPAGE_H
#define CLOUDMUSIC_MAINPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class viewpager;
class personalized;
QT_END_NAMESPACE

class cloudmusic_mainpage : public QWidget
{
    Q_OBJECT
public:
    explicit cloudmusic_mainpage(QWidget *parent = nullptr);
    static cloudmusic_mainpage& getInstace(QWidget *parent = nullptr);
    void setStyle(QString style);

private:
    viewpager* viewpagerWidget;
    personalized* personalizedWidget;
    QVBoxLayout* mainVBL;

signals:

};

#endif // CLOUDMUSIC_MAINPAGE_H

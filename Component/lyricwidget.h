#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include <QWidget>
#include <QVector>

QT_BEGIN_NAMESPACE
    class QLabel;
    class QVBoxLayout;
    class QHBoxLayout;
    class QScrollArea;
QT_END_NAMESPACE

class lyricWidget : public QWidget
{
    Q_OBJECT
public:
    explicit lyricWidget(QWidget *parent = nullptr);
    static  lyricWidget& getInstance();
    void setLyric(QString songLyric);
    void setStyle(QString style);
    void setScrollBar(int value);

public slots:
    void addHightLight(qint64 postion);
    void changeScrollBar(qint64 position);

private:
    QWidget* mainWidget;
    QHBoxLayout* mainVBL;
    QVBoxLayout* insertVBL;
    QVector<QLabel*> * labelArr;
    QScrollArea* scrollArea;
    QStringList lyricList;
    QStringList timeList;
    int currentFlag = 0; //歌词段号
    QLabel* front_H_L_label = nullptr; //上一次高光的


signals:

};

#endif // LYRICWIDGET_H

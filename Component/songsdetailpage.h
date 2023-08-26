#ifndef SONGSDETAILPAGE_H
#define SONGSDETAILPAGE_H

#include <QWidget>
QT_BEGIN_INCLUDE_NAMESPACE
    class QLabel;
    class QTextBrowser;
    class QHBoxLayout;
    class QVBoxLayout;
    class QWidget;
    class lyricWidget;
    class QScrollArea;
QT_END_NAMESPACE

class songsDetailPage : public QWidget
{
    Q_OBJECT
public:
    explicit songsDetailPage(QWidget *parent = nullptr);
    static songsDetailPage& getInstance();
    void setSongLyric(QString songLyric);
private:
    QLabel* title;
    QLabel* singer;
    QLabel* album;
    QLabel* imgBox;
    lyricWidget* lyricWidget;
    QHBoxLayout* mainHBL;
    QVBoxLayout* rightVBL;
    QScrollArea* scrollArea;

signals:

};

#endif // SONGSDETAILPAGE_H

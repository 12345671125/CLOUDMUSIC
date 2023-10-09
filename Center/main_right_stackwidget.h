#ifndef MAIN_RIGHT_STACKWIDGET_H
#define MAIN_RIGHT_STACKWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
    class mainWidget;
    class QStackedWidget;
    class SearchPage;
    class QVBoxLayout;
    class songsDetailPage;
    class cloudmusic_mainpage;
    class QListWidgetItem;
QT_END_NAMESPACE

class main_right_stackWidget : public QWidget
{
    Q_OBJECT
public:
    mainWidget* parent;
    int width;
    int height;
    explicit main_right_stackWidget(QWidget *parent = nullptr);
    static main_right_stackWidget& getInstance(QWidget* parent = nullptr);
    void toSearchPage(QString input);
    void toSongsDetailPage();
private:
    QVBoxLayout* mainVBL;
    QStackedWidget* stackedWidget;
    SearchPage* searchPage;
    songsDetailPage* songsDetailPage;
    cloudmusic_mainpage* mainPage;
    QWidget* frontWidget = nullptr;



signals:

public slots:
    void switchByClickList(QListWidgetItem *item);

};

#endif // MAIN_RIGHT_STACKWIDGET_H

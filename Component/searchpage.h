#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>

QT_BEGIN_INCLUDE_NAMESPACE
    class QLabel;
    class QTableWidget;
    class QVBoxLayout;
    class QTableWidgetItem;
QT_END_NAMESPACE
class SearchPage : public QWidget
{
    Q_OBJECT
public:
    explicit SearchPage(QWidget *parent = nullptr);
    static SearchPage& getInstance();
    void setStyle(QString style);
    void getSearchContent(QString input);
private:
    QLabel* searchTitle;
    QTableWidget* tableWidget;
    QVBoxLayout* mainVBL;

private slots:
    void itemDoubleClicked(QTableWidgetItem *item);
signals:


};

#endif // SEARCHPAGE_H

#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QHBoxLayout;
class QIcon;
class QPushButton;
class my_top_centerWidget;
QT_END_NAMESPACE

class SearchBox : public QWidget
{
    Q_OBJECT
public:
    my_top_centerWidget* parent;
    int width;
    int height;
    explicit SearchBox(QWidget *parent = nullptr);
    ~SearchBox();
    static SearchBox& getInstance(QWidget* parent = nullptr);
    void setStyle(QString style);

private:
    QLineEdit* search_input;
    QIcon* search_Icon;
    QPushButton* search_btn;
    QHBoxLayout* mainHBL;

    void keyPressEvent(QKeyEvent *event);

private slots:
    void showSearchPage();

signals:

};

#endif // SEARCHBOX_H

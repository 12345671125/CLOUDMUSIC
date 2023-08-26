#ifndef USERNAME_HEADPORTRAIT_H
#define USERNAME_HEADPORTRAIT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
    class QHBoxLayout;
    class QIcon;
    class QLabel;
    class my_top_rightWidget;
    class QPushButton;
QT_END_NAMESPACE
class username_headportrait : public QWidget
{
    Q_OBJECT
public:
    my_top_rightWidget* parent;
    int width;
    int height;
    explicit username_headportrait(QWidget *parent = nullptr);
    static username_headportrait& getInstance(QWidget *parent = nullptr);
    void setHeadPortait(QString imgurl);
    void setUserName(QString username);
private:
    QHBoxLayout* mainHBL;
    QIcon* headportrait;
    QPushButton* imgBox;
    QLabel* username;
    int codePageFlag  = 0;

private slots:
    void showQrCodePage();

signals:

};

#endif // USERNAME_HEADPORTRAIT_H

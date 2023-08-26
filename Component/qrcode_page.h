#ifndef QRCODE_PAGE_H
#define QRCODE_PAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
    class QImage;
    class QVBoxLayout;
    class QLabel;
    class QPushButton;
QT_END_NAMESPACE

class QrCode_page : public QWidget
{
    Q_OBJECT
public:
    explicit QrCode_page(QString base64,QWidget *parent = nullptr);
    static QrCode_page& getInstance(QString base64 = "");
    void getQrCodeImg(QString base64);
private:
    QLabel* imgBox;
    QImage* QrCodeImg;
    QVBoxLayout* mainVBL;
    QLabel* title;
    QPushButton* flushBtn;
    void closeEvent(QCloseEvent*e);

private slots:
   void checkCodeStatues(int code);
    void flushQrcodeImg();

signals:

};

#endif // QRCODE_PAGE_H

#ifndef LOGIN_BY_QR_CODE_H
#define LOGIN_BY_QR_CODE_H

#include <QObject>
QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class login_by_Qr_code: public QObject
{
    Q_OBJECT
public:
    login_by_Qr_code(QObject* parent = nullptr);
    ~login_by_Qr_code();
    static login_by_Qr_code& getinstance();
    QString getQrCode_Base64();
    void stopTimer();
    void startTimer();

signals:
    void codeTimeout(int code);//超时
    void waitScan(int code); //等待扫码
    void waitVerify(int code); // 等待确认
    void loginSuccess(int code); //登录成功
private:
    QTimer* checkStatusTimer;
    QString codeKey;
private slots:
    void checkStatus();

};

#endif // LOGIN_BY_QR_CODE_H

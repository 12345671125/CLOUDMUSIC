#ifndef LOGINSTATUS_H
#define LOGINSTATUS_H

#include <QObject>
QT_BEGIN_INCLUDE_NAMESPACE
    class QString;
QT_END_NAMESPACE

class loginStatus
{
public:
    enum STATUS{
        LOGINSTATUS_ERROR = -1,
        LOGINSTATUS_HASLOGIN = -10,
        LOGINSTATUS_OTHER = 0,
    };
    loginStatus();
    int getloginStatus();
    static loginStatus& getinstance();
   QString getUid();
private:
    QString uid;
};

#endif // LOGINSTATUS_H

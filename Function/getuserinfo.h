#ifndef GETUSERINFO_H
#define GETUSERINFO_H

#include <QString>


class getUserInfo
{
public:
    getUserInfo();
    static getUserInfo& getInstance();
    bool userInfo();
    QString getUsername();
    QString getUserImg();

private:
    QString username;
    QString userImg;

};

#endif // GETUSERINFO_H

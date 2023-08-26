#ifndef SONG_H
#define SONG_H
#include <QObject>

class song
{
public:
    song();
    static song& getInstance();
    bool isVaild(QString id);
    QString getSong(QString id);
};

#endif // SONG_H

#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>

class QTimer;
class QMutex;

class Player : public QObject
{
     Q_OBJECT
public:
    Player(QObject* parent = nullptr);
    ~Player();
    static Player& getInstance();
    int getStatus();
    QMediaPlayer* getQPlayer();
public slots:
    qint64 play(QString songUrl,QString id);
    void pause();
    void start();
    qint64 getDuration();
    void sliderReleased();
private:
    QMediaPlayer* player;
    QTimer* checkTimer;
    QMutex* controlMetux;

private slots:
    void check();
};

#endif // PLAYER_H

#ifndef LYRIC_H
#define LYRIC_H

class QString;

class lyric
{
public:
    lyric();
  static lyric& getInstance();
    QString getSongLyric(QString songId);
};

#endif // LYRIC_H

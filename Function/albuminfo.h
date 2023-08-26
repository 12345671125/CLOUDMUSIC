#ifndef ALBUMINFO_H
#define ALBUMINFO_H

class QJsonArray;
class QString;

class albumInfo
{
public:
    albumInfo();
    static albumInfo& getInstance();
    QJsonArray getAlbumInfo(QString id);
};

#endif // ALBUMINFO_H

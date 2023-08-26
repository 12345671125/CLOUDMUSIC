#ifndef SEARCH_H
#define SEARCH_H
#include <QObject>

class QJsonArray;

class search
{
public:
    search();
    static search& getinstance();
    QJsonArray getSearchContent(QString input);
};

#endif // SEARCH_H

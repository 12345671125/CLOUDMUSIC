#include "viewpager.h"

viewpager::viewpager(QWidget *parent)
    : QWidget{parent}
{

}

viewpager &viewpager::getInstance(QWidget *parent)
{
    static viewpager instance;
    return instance;
}

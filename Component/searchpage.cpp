#include "searchpage.h"

#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>
#include "../style.h"
#include "Function/search.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include "Function/song.h"
#include "Component/player.h"
#include "../Component/controlbar_btng.h"
#include "../Component/controlbar_progressbar.h"
#include "songimg_songtitle.h"
#include "albuminfo.h"
#include <QDebug>
#include "songsdetailpage.h"

SearchPage::SearchPage(QWidget *parent)
    : QWidget{parent},
    searchTitle(new QLabel(this)),
    tableWidget(new QTableWidget(this)),
    mainVBL(new QVBoxLayout(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->mainVBL->setContentsMargins(0,0,0,0);
    this->mainVBL->setSpacing(10);

    this->searchTitle->setText("TEST");

    this->tableWidget->setColumnCount(4);
    this->tableWidget->setRowCount(30);

    this->tableWidget->setAttribute(Qt::WA_StyledBackground);
    this->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中
    this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格数据区内的所有单元格都不允许编辑
    this->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableWidget->verticalHeader()->setVisible(false);
    this->tableWidget->setShowGrid(false);
    this->tableWidget->setHorizontalHeaderLabels(QStringList()<<"音乐标题"<<"歌手"<<"专辑"<<"时长");


    this->mainVBL->addWidget(this->searchTitle,1);
    this->mainVBL->addWidget(tableWidget,6);
    this->setLayout(this->mainVBL);

    this->setStyle(my_searchPage_style);

    QObject::connect(this->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));

}

SearchPage &SearchPage::getInstance()
{
    static SearchPage instance;
    return instance;
}

void SearchPage::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}

void SearchPage::getSearchContent(QString input)
{
    this->searchTitle->setText(input+"的搜索内容");
    QJsonArray songsArray = search::getinstance().getSearchContent(input);
    if(songsArray.isEmpty()){
        return;
    }
    for(int i = 0;i<songsArray.count();i++){
        QJsonObject json_detail = songsArray.at(i).toObject();
        QTableWidgetItem* item_songName = new QTableWidgetItem();
        QTableWidgetItem* item_songArtists = new QTableWidgetItem();
        QTableWidgetItem* item_songAlbum = new QTableWidgetItem();
        QTableWidgetItem* item_songDuration = new QTableWidgetItem();
        QString idStr;
        QString albumidStr;
        idStr.clear();
        albumidStr.clear();
        if(json_detail.contains("id")){
            idStr = json_detail.value("id").toVariant().toString();
//            qDebug()<< idStr;
        }
        if(json_detail.contains("name")){
            QString songName;
            songName.clear();
            songName = json_detail.value("name").toString();
            item_songName->setText(songName);
            item_songName->setTextAlignment(Qt::AlignCenter);
        }
        if(json_detail.contains("artists")){
            QJsonArray artistsArr = json_detail.value("artists").toArray();
            QString artistsStr;
            artistsStr.clear();
            for(int j = 0;j<artistsArr.count();j++){
                QJsonObject json_artist = artistsArr.at(j).toObject();
                if(json_artist.contains("name")){
                    if(j != 0) artistsStr.append(',');
                    artistsStr.append(json_artist.value("name").toString());
                }
            }
            item_songArtists->setText(artistsStr);
            item_songArtists->setTextAlignment(Qt::AlignCenter);
        }
        if(json_detail.contains("album")){
            QJsonObject json_album = json_detail.value("album").toObject();
            if(json_album.contains("id")){
                albumidStr =  json_album.value("id").toVariant().toString();
            }
            if(json_album.contains("name")){
                QString albumName;
                albumName.clear();
                albumName =  json_album.value("name").toString();
                item_songAlbum->setText(albumName);
                item_songAlbum->setTextAlignment(Qt::AlignCenter);
                QString whatThis;
                whatThis.clear();
                whatThis.append(idStr).append(':').append(albumidStr);
                item_songName->setWhatsThis(whatThis);
                item_songArtists->setWhatsThis(whatThis);
                item_songAlbum->setWhatsThis(whatThis);
                item_songDuration->setWhatsThis(whatThis);
            }

        }
        if(json_detail.contains("duration")){
            int duration = json_detail.value("duration").toInt();
            int sec = duration / 1000;
            int minute = sec / 60;
            int sec_residue = sec - minute * 60;

            QString durationStr = QString("%1:%2").arg(minute).arg(sec_residue);
            item_songDuration->setText(durationStr);
            item_songDuration->setTextAlignment(Qt::AlignCenter);
        }
        this->tableWidget->setItem(i,0,item_songName);
        this->tableWidget->setItem(i,1,item_songArtists);
        this->tableWidget->setItem(i,2,item_songAlbum);
        this->tableWidget->setItem(i,3,item_songDuration);

    }

    this->tableWidget->setAlternatingRowColors(true);

    this->tableWidget->setPalette(QPalette(QColor(235,235,235)));

}

void SearchPage::itemDoubleClicked(QTableWidgetItem *item)
{
    if(song::getInstance().isVaild(item->whatsThis()) == true){
        QString whatThis = item->whatsThis();
        QString idStr = whatThis.mid(0,whatThis.indexOf(":"));
        QString idAlbumStr = whatThis.mid(whatThis.indexOf(":")+1);
//        qDebug()<<idStr;
//        qDebug()<<idAlbumStr;
        Player::getInstance().play(song::getInstance().getSong(idStr),idStr);
        controlbar_btnG::getInstance().playState = 1;
        controlbar_btnG::getInstance().switchPlayAndPause();
        QString title = this->tableWidget->item(this->tableWidget->currentRow(),0)->text();
        QString singer = this->tableWidget->item(this->tableWidget->currentRow(),1)->text();
        QString album = this->tableWidget->item(this->tableWidget->currentColumn(),2)->text();
        songImg_songTitle::getInstance().setImgAndTitle(albumInfo::getInstance().getAlbumInfo(idAlbumStr),title,singer);
        songsDetailPage::getInstance().setSongtitle(title,singer,album);
    };

}

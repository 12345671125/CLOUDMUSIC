#ifndef STYLE_H
#define STYLE_H
#include <QString>

/*style*/

const QString my_logoWidget_style = "QLabel{color:white;}";


const QString my_topWidget_style = "*{background:#d81e06;margin:0px;padding:0px;} \
                                    .topWidget{color:white;font-size:24px;border:none;border-top-left-radius:5px;border-top-right-radius:5px;} \
                                    QPushButton{border:none;}";


const QString my_searchBox_style = "QLineEdit{background:#e6e6e6; border:1px solid #d81e06;border-radius:10px;padding:5px 5px 5px 5px;}";


const QString my_centerWidget_style = "*{background:#ffffff;padding:0px;margin:0px;}                                                   \
                                        QListWidget{border-right:1px solid #e6e6e6;padding:0px;margin:0px;}  \
                                        QListWidget:item{border:none;width:85px;height:50px;font-size:24px;padding:10px 10px 10px 10px;} \
                                        QListWidget:item::selected{border-bottom:3px solid red;}  \
                                        QListWidget:item::hover{border-bottom:2px solid red;}    \
                                        .main_right_controlBarWidget{border-top:1px solid #e6e6e6;border-bottom-right-radius:5px;}                                                                  ";

const QString my_progressbar_style = "QTimeEdit{border:none;margin:0px;padding:0px;}\
                                      QTimeEdit::up-button,.QTimeEdit::down-button{border:none;width:0px}\
                                        \
                                      QSlider::groove:horizontal {border: 0px solid #bbb;}\
                                      QSlider::add-page:horizontal {background: #dbdbdb;border: 0px solid #777;border-radius: 2px;margin-top:9px;margin-bottom:9px;}\
                                      QSlider::sub-page:horizontal {background: #d81e06;border-radius: 2px;margin-top:9px;margin-bottom:9px;} \
                                      QSlider::handle:horizontal{width: 10px;border:none;background:#707070;} \
                                      QSlider::handle:horizontal:hover{width:10px;border:none;background:#2c2c2c;} " ;


const QString my_searchPage_style = " *{font-size:24px;font-family:Microsoft YaHei;border:none;padding:0px;margin:0px;}\
                                    QHeadView{background:transparent;}   \
                                     QHeadView::section{font-size:18px;color:#717171;font-family:Microsoft YaHei;border:none;padding:0px;margin:0px;}   \
                                     QTableWidget{font-size:24px;background:#ffffff;alternate-background-color:#fafafa;border:none;font-family:Microsoft YaHei;border:none;padding:0px;margin:0px;color:#717171;}   \
                                     QTableWidget::item{border:none;color:#717171;} \
                                     QTableWidget::item:selected{background:#e1e1e1;}                                              \
                                     QLabel{margin-left:20px;font-family:Microsoft YaHei;font-size:36px;font-weight:900;}";
const QString my_songImg_songTitle_style = "";


const QString my_lyric_style_def = ".QLabel{font-size:34px;font-family:Microsoft YaHei;}";
const QString my_lyric_style_highLight = ".QLabel{font-size:40px;font-family:Microsoft YaHei;color:#d81e06;font-weight:bold;}";
#endif // STYLE_H

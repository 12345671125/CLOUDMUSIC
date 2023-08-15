#ifndef STYLE_H
#define STYLE_H
#include <QString>

/*style*/

const QString my_logoWidget_style = ".QLabel{color:white;}";


const QString my_topWidget_style = "*{background:#d81e06;margin:0px;padding:0px;} \
                                    .topWidget{border:none;border-top-left-radius:5px;border-top-right-radius:5px;} \
                                     .QPushButton{border:none;}";


const QString my_searchBox_style = ".QLineEdit{background:#e6e6e6; border:1px solid #d81e06;border-radius:10px;padding:5px 5px 5px 5px;}";


const QString my_centerWidget_style = "*{background:#ffffff;padding:0px;margin:0px;}                                                   \
                                        .QListWidget{border-right:1px solid #e6e6e6;padding:0px;margin:0px;}  \
                                        .QListWidget:item{border:none;width:85px;height:35px;font-size:14px;padding:5px 5px 5px 5px;} \
                                        .QListWidget:item::selected{border-bottom:3px solid red;}  \
                                         .QListWidget:item::hover{border-bottom:2px solid red;}    \
                                          .main_right_controlBarWidget{border-top:1px solid #e6e6e6;border-bottom-right-radius:5px;}                                                                  ";
#endif // STYLE_H
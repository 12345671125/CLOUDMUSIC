QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwin.cpp

HEADERS += \
    mainwin.h \
    style.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/front.png \
    img/mode_ circle.png \
    img/mode_onlyone.png \
    img/mode_random.png \
    img/music.png \
    img/next.png \
    img/pause.png \
    img/start.png

include($$PWD/Top/top.pri)
include($$PWD/Center/center.pri)
include($$PWD/Bottom/bottom.pri)
include($$PWD/Component/Component.pri)

RESOURCES += \
    IMAGE.qrc

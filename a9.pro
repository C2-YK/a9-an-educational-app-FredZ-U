QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    action.cpp \
    block.cpp \
    bot.cpp \
    boteditor.cpp \
    coin.cpp \
    connecter.cpp \
    gamemode.cpp \
    main.cpp \
    maze.cpp \
    mazeeditor.cpp \
    previewer.cpp \
    space.cpp \
    viewer.cpp \
    wall.cpp

HEADERS += \
    action.h \
    block.h \
    bot.h \
    boteditor.h \
    coin.h \
    connecter.h \
    gamemode.h \
    maze.h \
    mazeeditor.h \
    previewer.h \
    space.h \
    viewer.h \
    wall.h

FORMS += \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

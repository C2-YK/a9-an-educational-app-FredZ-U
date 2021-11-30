QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bot.cpp \
    boteditor.cpp \
    boteditorpreviewer.cpp \
    connecter.cpp \
    filesystem.cpp \
    gamemode.cpp \
    main.cpp \
    maze.cpp \
    mazeeditor.cpp \
    mazeeditorpreviewer.cpp \
    viewer.cpp

HEADERS += \
    bot.h \
    boteditor.h \
    boteditorpreviewer.h \
    connecter.h \
    filesystem.h \
    gamemode.h \
    maze.h \
    mazeeditor.h \
    mazeeditorpreviewer.h \
    viewer.h

FORMS += \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Box2D/box2d-master/build/bin/release/ -lbox2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Box2D/box2d-master/build/bin/debug/ -lbox2d
else:unix: LIBS += -L$$PWD/../../Box2D/box2d-master/build/bin/ -lbox2d

INCLUDEPATH += $$PWD/../../Box2D/box2d-master/build/bin/Debug
DEPENDPATH += $$PWD/../../Box2D/box2d-master/build/bin/Debug

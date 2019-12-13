QT -= gui
LIBS += -lpthread libwsock32 libws2_32
CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    sql.cpp \
    server.cpp

HEADERS += \
    sql.h \
    global.h \
    server.h \
    include/tip.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/winodws/ -leasysqlite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/winodws/ -leasysqlited
else:unix: LIBS += -L$$PWD/lib/winodws/ -leasysqlite

INCLUDEPATH += $$PWD/include/easySQLite
DEPENDPATH += $$PWD/lib/winodws

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/winodws/libeasysqlite.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/winodws/libeasysqlited.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/winodws/easysqlite.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/winodws/easysqlited.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/winodws/libeasysqlite.a

QT -= gui
QT += network

CONFIG += c++17 cmdline
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        command_line_parser.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetworkLibrary/release/ -lUpdaterLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetworkLibrary/debug/ -lUpdaterLib
else:unix:!macx: LIBS += -L$$OUT_PWD/../NetworkLibrary/ -lUpdaterLib

INCLUDEPATH += $$PWD/../NetworkLibrary
DEPENDPATH += $$PWD/../NetworkLibrary

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetworkLibrary/release/libUpdaterLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetworkLibrary/debug/libUpdaterLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetworkLibrary/release/UpdaterLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetworkLibrary/debug/UpdaterLib.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../NetworkLibrary/libUpdaterLib.a

HEADERS += \
    command_line_parser.h

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_dialog.cpp \
    command_line_parser.cpp \
    ico_worker.cpp \
    icon_button.cpp \
    listed_widget.cpp \
    main.cpp \
    piconmaker_wnd.cpp \
    scaled_widget.cpp \
    settings.cpp \
    updater.cpp

HEADERS += \
    about_dialog.h \
    abstract_widget.h \
    command_line_parser.h \
    ico_data.h \
    ico_worker.h \
    icon_button.h \
    listed_widget.h \
    piconmaker_wnd.h \
    scaled_widget.h \
    settings.h \
    updater.h

FORMS += \
    about_dialog.ui \
    icon_button.ui \
    listed_widget.ui \
    piconmaker_wnd.ui \
    scaled_widget.ui

TRANSLATIONS += \
    PIconMaker_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

win32 {
    RC_FILE = app.rc
    OTHER_FILES += app.rc
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc

DISTFILES += \
    app.rc

unix {
    # QMAKE_POST_LINK += &&system( echo $${VERSION} > $$OUT_PWD/ver )
    QMAKE_POST_LINK += echo $$VERSION > $$OUT_PWD/ver.rc
}

win32 {

}

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

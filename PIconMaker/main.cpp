#include "piconmaker_wnd.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    a.setWindowIcon( QIcon( ":/icons/resources/icons/icon.png" ) );
    a.setApplicationName( "PIconMaker" );
    // a.setApplicationVersion( "0.1a" );
    {
        #define STR(x) #x
        #define XSTR(x) STR(x)
        a.setApplicationVersion( XSTR(VERSION) );
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PIconMaker_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    PIconMakerWnd w;
    w.show();
    return a.exec();
}

#include <QCoreApplication>
#include <QDir>
#include <QProcess>

#include "command_line_parser.h"
#include "updater.h"

int main( int argc, char *argv[] ){
    QCoreApplication a(argc, argv);    
    {
        #define STR(x) #x
        #define XSTR(x) STR(x)
        a.setApplicationVersion( XSTR(VERSION) );
    }

    CommandLineParser parser( a.arguments() );
    Updater update( parser.getPath(), parser.getVersion(), parser.getServer() );
    update.start();

    return a.exec();
}

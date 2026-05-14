#include "command_line_parser.h"

#include <QObject>

CommandLineParser::CommandLineParser() {
    QCommandLineParser parser;

    QCommandLineOption cmdOpt = QCommandLineOption( QStringList() << "c" );
    cmdOpt.setDescription( QObject::tr( "Выполня" ) );

    parser.addVersionOption();
    parser.addHelpOption();
    parser.process( qApp->arguments() );
}

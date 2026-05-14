#include "command_line_parser.h"

#include <QCoreApplication>

CommandLineParser::CommandLineParser( QStringList arguments ){
    m_server = "http://127.0.0.1/pub/";///PIconMaker/updates/";
    m_appPath = qApp->applicationDirPath();
    m_version = -1;

    QCommandLineParser parser;
    QCommandLineOption pathOpt = QCommandLineOption( "path", "Path to application PIconMaker", "AppPath" );
    parser.addOption( pathOpt );

    QCommandLineOption serverOpt = QCommandLineOption( "srv", "Address of server to download updates", "Server" );
    parser.addOption( serverOpt );

    QCommandLineOption versionOpt = QCommandLineOption( "v", "Current version of application PIconMaker", "Version" );
    parser.addOption( versionOpt );

    parser.process( arguments );

    if( parser.isSet( pathOpt ) ){
        m_appPath = parser.value( pathOpt );
    }

    if( parser.isSet( serverOpt ) ){
        m_server = parser.value( serverOpt );
    }

    if( parser.isSet( versionOpt ) ){
        m_version = parser.value( versionOpt );
    }
}

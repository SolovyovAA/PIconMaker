#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <QCommandLineParser>
#include <QCommandLineOption>

class CommandLineParser {
public:
    CommandLineParser(QStringList arguments);
    ~CommandLineParser() = default;

    QString getServer() { return  m_server; }
    QString getVersion() { return  m_version; }
    QString getPath() { return  m_appPath; }

private:
    bool m_serverIsSet, m_versionIsSet, m_appPathIsSet;
    QString m_server, m_version, m_appPath;
};

#endif // COMMAND_LINE_PARSER_H

#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

class CommandLineParser {
public:
    CommandLineParser();
    ~CommandLineParser() = default;

private:
    bool m_isCommandVerIsSet;
};

#endif // COMMAND_LINE_PARSER_H

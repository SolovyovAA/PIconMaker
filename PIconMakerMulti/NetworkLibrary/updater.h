#ifndef UPDATER_H
#define UPDATER_H

#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QTimer>

class Updater : public QObject {
    Q_OBJECT
public:
    Updater( const QString &appPath, const QString &localVersion, const QString &ftp, QObject *parent = nullptr );
    ~Updater() = default;

    void start();

signals:
    void info( const QString &msg );
    void error( const QString &msg );
    void progress( qint64 received, qint64 total );

private:
    Q_SLOT void onReplyFinished();

    void checkServerAvailability();
    void downloadUpdate( const QString &urlStr );
    void installUpdate();

    int compareVersions( const QString &v1, const QString &v2 );

    QString m_appPath;
    QString m_localVersion;
    QString m_ftpServer;
    QNetworkAccessManager *m_mgr;
    QNetworkReply *m_downloadReply = nullptr;
    QFile m_tmpFile;
};

#endif // UPDATER_H

#include "updater.h"

#include <QUrl>
#include <QProcess>

Updater::Updater(const QString &appPath, const QString &localVersion, const QString &ftp, QObject *parent)
    : QObject ( parent )
    , m_appPath( appPath )
    , m_localVersion( localVersion )
    , m_ftpServer( ftp ){
    m_mgr = new QNetworkAccessManager( this );
}

void Updater::start(){
    checkServerAvailability();
}

void Updater::onReplyFinished(){
    QNetworkReply *reply = qobject_cast< QNetworkReply* >( sender() );
    bool serverOk = (reply->error() == QNetworkReply::NoError );
    if( !serverOk ){
        emit error( tr( "Сервер недоступен: %1" ).arg( reply->errorString() ) );
        reply->deleteLater();
        return;
    }

    QJsonObject root;
    auto data = reply->readAll();
    auto doc = QJsonDocument::fromJson( data );
    if( !doc.isNull() && doc.isObject() ){
        root = doc.object();
    }

    reply->deleteLater();

    if( root.isEmpty() ){
        emit error( tr( "Не удалось прочитать файл обновлений" ) );
        return;
    }

    QString serverVersion = root[ "version" ].toString();
    QString updateUrlStr = root[ "url" ].toString();

    int cmp = compareVersions( m_localVersion, serverVersion );
    if( cmp >= 0 ){
        emit info( tr( "Обновлений нет" ) );
        return;
    }

    emit info( tr( "Найдено обновление %1 -> %2" ).arg( m_localVersion ).arg( serverVersion ) );
    downloadUpdate( updateUrlStr );
}

void Updater::checkServerAvailability(){
    QUrl url( m_ftpServer + "/updates/PIconMaker/update.json" );
    QNetworkRequest req( url );
    req.setHeader( QNetworkRequest::UserAgentHeader, "PIconMaker-Updater/1.0" );

    QNetworkReply *reply = m_mgr->get( req );
    connect( reply, &QNetworkReply::finished, this, &Updater::onReplyFinished );
}

void Updater::downloadUpdate( const QString &urlStr ){
    QUrl url( urlStr );
    QNetworkRequest req( url );

    QNetworkReply *reply = m_mgr->get( req );
    m_downloadReply = reply;

    // временный файл для скачивания
    QString tmpPath = QDir( qApp->applicationDirPath() ).absoluteFilePath( "PIconMaker_new.exe" ); // TODO: win only, fix later
    m_tmpFile.setFileName( tmpPath );
    if( !m_tmpFile.open( QIODevice::WriteOnly ) ){
        emit error( tr( "Не удалось создать временный файл" ) );
        reply->abort();
        return;
    }

    connect( reply, &QNetworkReply::readyRead, this, [this, reply]{ m_tmpFile.write( reply->readAll() ); } );
    connect( reply, &QNetworkReply::downloadProgress, this, [this]( qint64 recieved, qint64 total ){ if( total > 0 ){ emit progress( recieved, total ); } } );
    connect( reply, &QNetworkReply::finished, this, [this]{
        m_tmpFile.close();
        if( m_downloadReply->error() != QNetworkReply::NoError ){
            emit error( tr( "Ошибка скачивания: %1" ).arg( m_downloadReply->errorString() ) );
            return;
        }

        emit info( tr( "Скачивания завершено, установка..." ) );
        QTimer::singleShot( 100, this, &Updater::installUpdate );
    } );
}

void Updater::installUpdate(){
    QString appPath = m_appPath;
    QString backupPath = appPath + ".old";
    QString newPath = m_tmpFile.fileName();

    if( QFile::exists( appPath ) ){
        QFile::rename( appPath, backupPath );
    }

    if( !QFile::copy( newPath, appPath ) ){
        emit error( tr( "Не удалось заменить приложение" ) );
        if( QFile::exists( backupPath ) ){
            QFile::rename( backupPath, appPath );
        }
        return;
    }

    emit info( tr( "Обновление установлено, запускаем новую версию" ) );
    QProcess::startDetached( appPath );
    qApp->exit( 0 );
}

int Updater::compareVersions( const QString &v1, const QString &v2 ){
    auto tokens1 = v1.split( '.' );
    auto tokens2 = v2.split( '.' );

    int n = qMax( tokens1.size(), tokens2.size() );
    for( int i =0; i < n; i++ ){
        QString t1 = ( i < tokens1.size() )? tokens1[ i ].toStdString().c_str() : "0";
        QString t2 = ( i < tokens2.size() )? tokens2[ i ].toStdString().c_str() : "0";

        if( t1 < t2 ) return -1;
        if( t1 > t2 ) return 1;
    }
    return  0;
}

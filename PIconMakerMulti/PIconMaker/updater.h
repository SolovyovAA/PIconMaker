#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>

class Updater : public QObject {
    Q_OBJECT
public:
    explicit Updater( QObject *parent = nullptr );
    ~Updater() = default;

signals:
};

#endif // UPDATER_H

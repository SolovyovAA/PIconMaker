#ifndef ICOWORKER_H
#define ICOWORKER_H

#include <QImage>
#include <QVector>
#include <QByteArray>
#include <QFile>
#include <QDataStream>

// Возвращает QByteArray с BMP‑данными из QImage
QByteArray imageToBmpData( const QImage &img );

// Формирование ICO файла из списка картинок
bool saveIco( const QString &path, const QList< QImage > &images );

// Метод для формирования разных размеров из одного изображения
QList< QImage > makeIconSetFromOne( const QImage &source );

#endif // ICOWORKER_H

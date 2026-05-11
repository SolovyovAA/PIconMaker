#ifndef ICOWORKER_H
#define ICOWORKER_H

#include <QImage>
#include <QVector>
#include <QByteArray>
#include <QFile>
#include <QDataStream>

// Возвращает QByteArray с BMP‑данными из QImage
QByteArray imageToBmpData(const QImage &img);

// Формирование ICO файла из списка картинок
bool saveIco(const QString &path, const QList< QImage > &images);

#endif // ICOWORKER_H

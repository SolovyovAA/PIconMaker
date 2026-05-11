#include "ico_worker.h"

#include "ico_data.h"

QByteArray imageToBmpData( const QImage &img ){
    if (img.isNull()) return QByteArray();

    QImage bmp = img.convertToFormat(QImage::Format_ARGB32);

    const int width  = bmp.width();
    const int height = bmp.height();
    const int rowPad = 4 - (width * 4) % 4;
    const int rowSize = width * 4 + (rowPad % 4);
    const int dataSize = rowSize * height;

    BITMAPINFOHEADER hdr = {};
    hdr.biSize = 40;
    hdr.biWidth = width;
    hdr.biHeight = height * 2;        // top‑down, no bottom‑up support
    hdr.biPlanes = 1;
    hdr.biBitCount = 32;
    hdr.biCompression = 0;
    hdr.biSizeImage = dataSize;
    hdr.biXPelsPerMeter = 2835;       // 72 dpi
    hdr.biYPelsPerMeter = 2835;

    QByteArray ret;
    ret.resize(sizeof(BITMAPINFOHEADER) + dataSize);

    char *ptr = ret.data();

    // BITMAPINFOHEADER
    memcpy(ptr, &hdr, sizeof(hdr));
    ptr += sizeof(hdr);

    // Пиксели: в BMP пиксель — BGRA, а QImage — RGBA,
    // поэтому нужно поменять порядок байт.
    const int srcStride = bmp.bytesPerLine();
    const uchar *src = bmp.constBits() + srcStride * (height - 1);

    for (int y = height - 1; y >= 0; --y) {
        const QRgb *line = (const QRgb *)src;
        for (int x = 0; x < width; ++x) {
            QRgb c = line[x];
            *ptr++ = qBlue(c);  // B
            *ptr++ = qGreen(c); // G
            *ptr++ = qRed(c);   // R
            *ptr++ = qAlpha(c); // A
        }
        src -= srcStride;
    }

    return ret;
}

bool saveIco( const QString &path, const QList< QImage > &images ){
    if (images.isEmpty()) return false;

    QFile f(path);
    if (!f.open(QIODevice::WriteOnly)) return false;

    QDataStream s(&f);
    s.setByteOrder(QDataStream::LittleEndian);

    ICONDIR dir;
    dir.idReserved = 0;
    dir.idType = 1;   // 1 = ICO
    dir.idCount = static_cast<quint16>(images.size());

    s.writeRawData(reinterpret_cast<const char*>(&dir), sizeof(dir));

    // Массив ICONDIRENTRY + отдельный список BMP‑данных
    QVector<ICONDIRENTRY> entries(images.size());
    QVector<QByteArray> bmps;

    quint32 offset = sizeof(dir) + images.size() * sizeof(ICONDIRENTRY);

    for (int i = 0; i < images.size(); ++i) {
        const QImage &img = images[i];
        if (img.width() > 256 || img.height() > 256 || img.width() < 1 || img.height() < 1) {
            // можно пропустить некорректные размеры или ресайзить
            continue;
        }

        QByteArray bmpData = imageToBmpData(img);
        if (bmpData.isEmpty()) continue;

        entries[i].bWidth  = img.width();
        entries[i].bHeight = img.height();
        entries[i].bColorCount = 0;
        entries[i].bReserved = 0;
        entries[i].wPlanes = 1;
        entries[i].wBitCount = 32;
        entries[i].dwBytesInRes = bmpData.size();
        entries[i].dwImageOffset = offset;

        bmps.append(bmpData);
        offset += bmpData.size();
    }

    // Пишем ICONDIRENTRY
    for (const auto &e : entries)
        s.writeRawData(reinterpret_cast<const char*>(&e), sizeof(e));

    // Пишем BMP‑блоки
    for (const QByteArray &b : bmps)
        s.writeRawData(b.constData(), b.size());

    return true;
}

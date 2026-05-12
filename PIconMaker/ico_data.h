#pragma pack(push, 1)
#include <QtCore>

struct ICONDIR {
    quint16 idReserved;  // 0
    quint16 idType;      // 1 for icons
    quint16 idCount;     // number of images
};

struct ICONDIRENTRY {
    quint8  bWidth;
    quint8  bHeight;
    quint8  bColorCount;
    quint8  bReserved;
    quint16 wPlanes;
    quint16 wBitCount;
    quint32 dwBytesInRes;
    quint32 dwImageOffset;
};

struct BITMAPINFOHEADER {
    quint32 biSize;
    quint32 biWidth;
    quint32 biHeight;
    quint16 biPlanes;
    quint16 biBitCount;
    quint32 biCompression;
    quint32 biSizeImage;
    quint32 biXPelsPerMeter;
    quint32 biYPelsPerMeter;
    quint32 biClrUsed;
    quint32 biClrImportant;
};

// Перечень стандартных размеров
const QVector< QSize > kIconSizes {
    {16, 16},
    {24, 24},
    {32, 32},
    {48, 48},
    {256, 256},
    {512, 512}
};
#pragma pack(pop)

#ifndef TILESDOWNLOADER_H
#define TILESDOWNLOADER_H

#include <QThread>
#include <QGeoCoordinate>
#include <math.h>
#include <QMutex>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QImage>

class TilesDownloader : public QThread
{
    Q_OBJECT
public:
    TilesDownloader(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;

public slots:
    void downloadTiles(QVariant center, int zoomLevel);

private:
    int long2tilex(double lon);
    int lat2tiley(double lat);

    void savePngToFile(QByteArray frame, int x, int y);

    QGeoCoordinate m_coordinates;

    int m_zoomLevel;
};

#endif // TILESDOWNLOADER_H



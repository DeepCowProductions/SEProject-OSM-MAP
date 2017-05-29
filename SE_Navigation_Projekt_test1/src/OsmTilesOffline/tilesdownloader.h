#ifndef TILESDOWNLOADER_H
#define TILESDOWNLOADER_H

#include <QGeoCoordinate>
#include <math.h>
#include <QMutex>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


#include "tile.h"
#include "tilereply.h"
#include "tileofflinemanager.h"

class TilesDownloader : public QObject
{
    Q_OBJECT
public:
    TilesDownloader(QObject *parent = 0);

public slots:
    void downloadTiles(QVariant center, QString tileProvider, int zoomLevel);
    void saveTile(Tile* tile);

signals:
    void downloadFinished();

private:
    QString m_tileProvider;
    Tile * m_tile;
    TileOfflineManager *m_tom;
};

#endif // TILESDOWNLOADER_H



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
    TilesDownloader(QObject *parent = 0, QPoint screenSize = QPoint(0,0));
    ~TilesDownloader();

public slots:
    void downloadTiles(QVariant center, QString tileProvider, int zoomLevel);
    void saveTile(Tile* tile);

signals:
    void downloadFinished();

private:

    void createRequest(Tile * tile);

    bool sendingRequests();

    QString m_tileProvider;
    Tile * m_startTile;
    TileOfflineManager *m_tom;
    QPoint m_screenSize;
    QList<Tile *> m_downloadTiles;
    QList<QNetworkRequest * > m_requests;
    int m_x;
    int m_y;
    int m_zoomlevel;
    int m_counter;
};

#endif // TILESDOWNLOADER_H



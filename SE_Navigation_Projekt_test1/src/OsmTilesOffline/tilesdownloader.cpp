#include "tilesdownloader.h"
#include <QStandardPaths>
#include "src/Singleton/networkaccesmanagersingleton.hpp"


TilesDownloader::TilesDownloader(QObject* parent)
    : QObject(parent)
{
    m_tom = new TileOfflineManager("jpg", this);
}


void TilesDownloader::downloadTiles(QVariant center, QString tileProvider, int zoomLevel)
{
//    QNetworkAccessManager * nm = NetworkAccessManagerSingleton::getInstance();
    QGeoCoordinate coordinates = center.value<QGeoCoordinate>();
    this->m_tileProvider = tileProvider;
    const double longi = coordinates.longitude();
    const double lati = coordinates.latitude();
    m_tile = new Tile((double)longi, (double)lati, zoomLevel, "osm", 1, this);

    if(!m_tom->copyChacheTileIfPossible(m_tile)){
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::UserAgentHeader, "Qt Location based application");
//    QString url = "http://" + m_tileProvider +  "/tiles/roads/x=" + QByteArray::number(m_tile.x()) + "&y=" + QByteArray::number(m_tile.y()) + "&z=" + QByteArray::number(m_tile.zoomlevel());
    QString url = "http://" + m_tileProvider +  "/tiles/roads/x=" + QByteArray::number(m_tile->x()) + "&y=" + QByteArray::number(m_tile->y()) + "&z=" + QByteArray::number(m_tile->zoomlevel());
//    QString url = "http://" + m_tileProvider +  "/" + QByteArray::number(m_tile.zoomlevel()) + "/" + QByteArray::number(m_tile.x()) + "/" + QByteArray::number(m_tile.y()) + ".png";
    request.setUrl(QUrl(url));


    QNetworkAccessManager * nm = new QNetworkAccessManager(this);
//    nm->connectToHost(m_tileProvider);

    QNetworkReply *reply = nm->get(request);

    TileReply * tileReply = new TileReply(reply, m_tile, this);

    connect(nm, SIGNAL(finished(QNetworkReply*)), tileReply, SLOT(networkReplyFinished(QNetworkReply*)));
    connect(tileReply, SIGNAL(saveTile(Tile*)), this, SLOT(saveTile(Tile*)));
    }else{
        emit downloadFinished();
    }
//    (!tileReply->finished());

//    if(request)
//        delete request;
//    if(reply)
//        delete reply;
//    while(nm->disconnect());
//    if(nm)
//        delete nm;
//    if(m_tile)
//        delete m_tile;
            //    emit downloadFinished();
}

void TilesDownloader::saveTile(Tile *tile)
{
    m_tom->saveToFile(tile);
    emit downloadFinished();
}

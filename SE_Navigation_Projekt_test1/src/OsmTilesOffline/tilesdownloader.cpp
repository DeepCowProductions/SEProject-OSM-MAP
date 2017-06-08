#include "tilesdownloader.h"
#include <QStandardPaths>
#include "src/Singleton/networkaccesmanagersingleton.hpp"

TilesDownloader::TilesDownloader(QObject* parent, QPoint screenSize)
    : QObject(parent)
{
    m_tom = new TileOfflineManager("jpg", parent);

    m_screenSize = screenSize;
    m_counter = 0;
}

TilesDownloader::~TilesDownloader()
{
    for(int i = 0; i< m_downloadTiles.size(); i++)
        delete m_downloadTiles.at(i);
    for(int i = 0; i< m_requests.size(); i++)
        delete m_requests.at(i);
    if(m_tom)
        delete m_tom;
    if(m_startTile)
        delete m_startTile;
}


void TilesDownloader::downloadTiles(QVariant center, QString tileProvider, int zoomLevel)
{

    QGeoCoordinate coordinates = center.value<QGeoCoordinate>();
    this->m_tileProvider = tileProvider;
    const double longi = coordinates.longitude();
    const double lati = coordinates.latitude();
    m_startTile = new Tile((double)longi, (double)lati, zoomLevel, "osm", 1, this);

    int requestCounter = 0;
    int tileCounter = 1; // 1 aufgrund des StartTiles
    int x = m_startTile->x();
    int y = m_startTile->y();
    int zLevel = m_startTile->zoomlevel();

    Tile* tile;

    //Äußere Schleife für zoomlevel
    for(int z = 0; z < 2; z++){
        //Schleife die abhängig von der Bildschirmgröße die benötigte Anzahl an Tiles für das aktuelle zoomlevel berechnet
        int amountY = (m_screenSize.y() / 256 + 1) * pow(2, z);
        int amountX = (m_screenSize.x() / 256 + 1) * pow(2, z);

        for(int i = y * pow(2, z) - amountY/ 2; i <= y * pow(2, z) + amountY/ 2; i++ ){
            for(int j = x * pow(2, z); j < x * pow(2, z) + amountX; j++){
                tile = new Tile(j, i, zLevel + z, "osm", 1, this);
                if(!m_tom->copyChacheTileIfPossible(tile)){
                    createRequest(tile);
                    requestCounter++;
                    //                    sendRequest(tile);
                }
                tileCounter++;

            }
        }
    }
    sendingRequests();
    qDebug() << requestCounter << " Requests wurden verschickt";
}

void TilesDownloader::sendingRequests()
{
    if(m_counter < m_requests.size()){
        QNetworkAccessManager * nm = NetworkAccessManagerSingleton::getInstance();

        TileReply * tileReply = new TileReply(nm->get(*m_requests.at(m_counter)), m_downloadTiles.at(m_counter), this);
        //         qDebug() << "Tile: " << tile->x() << " " << tile->y();
        connect(nm, SIGNAL(finished(QNetworkReply*)), tileReply, SLOT(networkReplyFinished(QNetworkReply*)));
        connect(tileReply, SIGNAL(saveTile(Tile*)), this, SLOT(saveTile(Tile*)));
    }else{
        emit downloadFinished();
    }
}

void TilesDownloader::createRequest(Tile *tile)
{
    QNetworkRequest *request = new QNetworkRequest();
    request->setHeader(QNetworkRequest::UserAgentHeader, "Qt Location based application");
    //    QString url = "http://" + m_tileProvider +  "/tiles/roads/x=" + QByteArray::number(m_tile.x()) + "&y=" + QByteArray::number(m_tile.y()) + "&z=" + QByteArray::number(m_tile.zoomlevel());
    QString url = "http://" + m_tileProvider +  "/tiles/roads/x=" + QByteArray::number(tile->x()) + "&y=" + QByteArray::number(tile->y()) + "&z=" + QByteArray::number(tile->zoomlevel());
    //    QString url = "http://" + m_tileProvider +  "/" + QByteArray::number(tile->zoomlevel()) + "/" + QByteArray::number(tile->x()) + "/" + QByteArray::number(tile->y()) + ".png";

    request->setUrl(QUrl(url));
    m_requests.append(request);
    m_downloadTiles.append(tile);
}

void TilesDownloader::saveTile(Tile *tile)
{

    m_tom->saveToFile(tile);
    qDebug() << "Counter" << m_counter;
    delete static_cast<TileReply *>(sender());
    m_counter++;
    sendingRequests();
}




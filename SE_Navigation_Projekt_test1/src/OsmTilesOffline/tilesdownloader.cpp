#include "tilesdownloader.h"
#include <QStandardPaths>
#include "src/Singleton/networkaccesmanagersingleton.hpp"


TilesDownloader::TilesDownloader(QObject* parent)
    : QObject(parent)
{
    m_tom = new TileOfflineManager(parent);
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


void TilesDownloader::downloadTiles(QVariant center, QString tileProvider, int zoomLevel,int depth, QPoint screenSize)
{
    m_screenSize = screenSize;

    QGeoCoordinate coordinates = center.value<QGeoCoordinate>();
    this->m_tileProvider = tileProvider;
    const double longi = coordinates.longitude();
    const double lati = coordinates.latitude();
    m_startTile = new Tile((double)longi, (double)lati, zoomLevel, "osm", 1, "png", this);

    int requestCounter = 0;
    int tileCounter = 1; // 1 aufgrund des StartTiles
    int x = m_startTile->x();
    int y = m_startTile->y();
    int zLevel = m_startTile->zoomlevel();

    Tile* tile;
//    QTime time;
//    time.start();
    //Äußere Schleife für zoomlevel
    for(int z = 0; z < depth+1; z++){
        //Schleife die abhängig von der Bildschirmgröße die benötigte Anzahl an Tiles für das aktuelle zoomlevel berechnet
        int amountY = (m_screenSize.y() / 256 + 1) * pow(2, z);
        int amountX = (m_screenSize.x() / 256 + 1) * pow(2, z);

        for(int i = y * pow(2, z) - amountY/ 2 ; i <= y * pow(2, z) + amountY/ 2; i++ ){
            for(int j = x * pow(2, z); j < x * pow(2, z) + amountX; j++){
                tile = new Tile(j, i, zLevel + z, "osm", 1, "png", this);
                if(!m_tom->copyChacheTileIfPossible(tile)){
                    m_downloadTiles.append(tile);
                    requestCounter++;
                    //                    sendRequest(tile);
                }
                tileCounter++;

            }
        }
    }
//    qDebug() << "Time for creation(in msecs): " << time.elapsed() / 1000.0;
    if(!m_downloadTiles.isEmpty())
        sendingRequests();
    else
        emit downloadFinished();
}

void TilesDownloader::sendingRequests()
{

    QNetworkAccessManager * nm = NetworkAccesManagerSingleton::getInstance();
    TileReply * tileReply = new TileReply(nm->get(createRequest(m_downloadTiles.at(m_counter))), m_downloadTiles.at(m_counter), this);
    connect(nm, SIGNAL(finished(QNetworkReply*)), tileReply, SLOT(networkReplyFinished(QNetworkReply*)));
    connect(tileReply, SIGNAL(saveTile(Tile*)), this, SLOT(saveTile(Tile*)));
}

QNetworkRequest TilesDownloader::createRequest(Tile *tile)
{
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::UserAgentHeader, "Qt Location based application");
    QString url = "http://" + m_tileProvider +  "/tiles/roads/x=" + QByteArray::number(tile->x()) + "&y=" + QByteArray::number(tile->y()) + "&z=" + QByteArray::number(tile->zoomlevel());

    request.setUrl(QUrl(url));

//    qDebug() << "Creating Request finished";
    return request;
}

void TilesDownloader::saveTile(Tile *tile)
{
    qDebug() << m_tom->saveToFile(tile);
//    qDebug() << "Counter" << m_counter;
    delete static_cast<TileReply *>(sender());
    if(m_counter < m_downloadTiles.size()){
        emit nextTileDownloadStarted(m_counter, m_downloadTiles.size());
        sendingRequests();
    }else{
        emit nextTileDownloadStarted(m_counter, m_downloadTiles.size());
        emit downloadFinished();
    }
    m_counter++;
}




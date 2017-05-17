#include "tilesdownloader.h"
#include <QStandardPaths>

TilesDownloader::TilesDownloader(QObject* parent)
    : QThread(parent)
{

}

void TilesDownloader::run()
{
    QMutex lock;
    lock.lock();
    int x = long2tilex(m_coordinates.longitude());
    int y = lat2tiley(m_coordinates.latitude());
    lock.unlock();
    qDebug() << "x: " << x << "\ny: " << y;
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost("korona.geog.uni-heidelberg.de", 80);
    QByteArray requestPacket;
    QString header = "GET /tiles/roads/x=" + QByteArray::number(x) + "&y=" + QByteArray::number(y) + "&z=" + QByteArray::number(m_zoomLevel) + " HTTP/1.1\r\n";

    requestPacket.append(header);
    requestPacket.append("User-Agent: Qt Location based application\r\n");
    requestPacket.append("Connection: Keep-Alive\r\n");
    requestPacket.append("Accept-Encoding: gzip, deflate\r\n");
    requestPacket.append("Accept-Language: de-DE, en,*\r\n");
    requestPacket.append("Host: korona.geog.uni-heidelberg.de\r\n\r\n");

    qDebug() << QStandardPaths::CacheLocation;
    if(socket->waitForConnected()){
        socket->write(requestPacket);
        socket->waitForReadyRead();
        savePngToFile(socket->readAll(), x, y);
    }else{
        qDebug() << "Failed to establish the connection";
        qDebug() << "Error: " << socket->error();
    }
    socket->disconnectFromHost();

    if(socket->state() != QAbstractSocket::UnconnectedState)
        socket->waitForDisconnected();
    delete socket;

}

void TilesDownloader::downloadTiles(QVariant center, int zoomLevel)
{
    this->m_coordinates = center.value<QGeoCoordinate>();
    this->m_zoomLevel = zoomLevel;
    this->start();

}

int TilesDownloader::long2tilex(double lon)
{
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, m_zoomLevel)));
}

int TilesDownloader::lat2tiley(double lat)
{
    return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, m_zoomLevel)));
}

void TilesDownloader::savePngToFile(QByteArray frame, int x, int y)
{
    QString fileName = "/home/maik/Schreibtisch/OSM-Data/" + QString::number(m_zoomLevel) + "/" + QString::number(x) + "/" + QString::number(y) + ".png";
    QDir dir;
    dir.mkpath("/home/maik/Schreibtisch/OSM-Data/" + QString::number(m_zoomLevel) + "/" + QString::number(x) + "/");
    QFile imageFile(fileName);
    if(!imageFile.exists()){
        if(imageFile.open(QFile::WriteOnly |QFile::Truncate)){
            QByteArray pngData = frame.right(frame.size() - frame.indexOf("\211PNG\r\n\032\n"));
//            pngData.append("IEND");
            qDebug() << pngData;
//            pngData.remove(0, 17);
//            QImage image = QImage::fromData(pngData, "PNG");
//            qDebug() << image.save(&imageFile, "PNG");
            imageFile.write(pngData);
        }
        imageFile.close();
    }

}

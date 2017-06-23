#include "tilereply.h"

TileReply::TileReply(QNetworkReply * reply, Tile *tile, QObject *parent) : QObject(parent)
{
    if(!reply){
        return;
    }

    m_reply = reply;
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this , SLOT(networkErrorOccured(QNetworkReply::NetworkError)));
    m_tile = tile;

}

void TileReply::networkReplyFinished(QNetworkReply *reply)
{
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError){
        qDebug() << "Error ist aufgetreten: " << reply->errorString();
        return;
    }
    m_tile->setImageData(reply->readAll());
    emit saveTile(m_tile);
}

void TileReply::networkErrorOccured(QNetworkReply::NetworkError error)
{
    m_reply->deleteLater();
    qDebug() << "Error occured:\n";
    qDebug() << error;
    emit errorOccured();
}


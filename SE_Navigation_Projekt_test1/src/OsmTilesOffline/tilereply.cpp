#include "tilereply.h"

TileReply::TileReply(QNetworkReply * reply, Tile *tile, QObject *parent) : QObject(parent)
{
    if(!reply){
        return;
    }

    m_reply = reply;
//    qDebug() << connect(m_reply, &QNetworkReply::finished, this, &TileReply::networkReplyFinished);
//    qDebug() << connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this , SLOT(networkErrorOccured(QNetworkReply::NetworkError)));
    m_finished = false;
    m_tile = tile;

}

void TileReply::networkReplyFinished(QNetworkReply *reply)
{
//    QNetworkReply * reply = static_cast<QNetworkReply *>(sender());
    qDebug() << "Read finished";
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError)
        return;
    m_tile->setImageData(reply->readAll());
    m_finished = true;
    emit saveTile(m_tile);
}

void TileReply::networkErrorOccured(QNetworkReply::NetworkError error)
{
    m_reply->deleteLater();
    qDebug() << "Error occured:\n";
    qDebug() << error;

}

bool TileReply::finished() const
{
    return m_finished;
}

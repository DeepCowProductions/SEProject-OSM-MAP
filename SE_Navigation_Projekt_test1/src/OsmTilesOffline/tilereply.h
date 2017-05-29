#ifndef TILEREPLY_H
#define TILEREPLY_H

#include <QObject>
#include <QNetworkReply>
#include "tile.h"

class TileReply : public QObject
{
    Q_OBJECT
public:
    explicit TileReply(QNetworkReply *reply, Tile *tile, QObject *parent = 0);


    bool finished() const;

signals:
    void saveTile(Tile *tile);

public slots:
    void networkReplyFinished(QNetworkReply* reply);
    void networkErrorOccured(QNetworkReply::NetworkError error);
private:
    Tile * m_tile = Q_NULLPTR;
    QNetworkReply * m_reply = Q_NULLPTR;
    bool m_finished;
};

#endif // TILEREPLY_H

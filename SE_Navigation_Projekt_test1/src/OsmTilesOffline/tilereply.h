#ifndef TILEREPLY_H
#define TILEREPLY_H

#include <QObject>
#include <QNetworkReply>
#include "tile.h"

/**
 * @brief The TileReply class Die Klasse ordent einem Tile einen Reply zu und Schreibt sobald der Reply fertig ist die empfangenen
 *          Daten in die Kachel
 *
 */
class TileReply : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief TileReply Konstruktor der Klasse
     * @param reply Der Reply der dem Tile zugeordnet werden soll. Der Reply wird mit Finished und Error-slots verknüpft
     * @param tile Das Tile dem der Reply zugeordnet wird
     * @param parent
     */
    explicit TileReply(QNetworkReply *reply, Tile *tile, QObject *parent = 0);

signals:

    /**
     * @brief saveTile Signal wird ausgelöst sobald das Tile vollständig empfangen wurde.
     * @param tile Zeiger auf das fertige Tile
     */
    void saveTile(Tile *tile);

    /**
     * @brief errorOccured Signal das bei Fehlern gesendet wird.
     */
    void errorOccured();

public slots:

    /**
     * @brief networkReplyFinished Slot der mit dem Finished-Signal des NetworkManager verknüpft wird.
     * @param reply Reply der verknüpft wird
     */
    void networkReplyFinished(QNetworkReply* reply);

    /**
     * @brief networkErrorOccured Error-Slot der bei Fehlern im reply aufgerufen wird
     * @param error
     */
    void networkErrorOccured(QNetworkReply::NetworkError error);

private:
    /**
     * @brief m_tile Tile zu dem RReply
     */
    Tile * m_tile = Q_NULLPTR;

    /**
     * @brief m_reply Reply für das entsprechende Tile
      */
    QNetworkReply * m_reply = Q_NULLPTR;
};

#endif // TILEREPLY_H

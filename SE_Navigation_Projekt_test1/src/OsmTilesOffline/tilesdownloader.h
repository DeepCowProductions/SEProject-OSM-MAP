#ifndef TILESDOWNLOADER_H
#define TILESDOWNLOADER_H

#include <QGeoCoordinate>
#include <math.h>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>


#include "tile.h"
#include "tilereply.h"
#include "tileofflinemanager.h"

/**
 * @brief The TilesDownloader class Klasse zum runterladen von Tiles in Form von Bilddateien. Zunächst werden aus der Bildschirmgröße,
 *          dem Mittelpunkt des aktuell angezeigten Fensters und dem aktuellen Zoomlevel, die zu runterladenen Kacheln ermittelt und
 *          Requests dazu erzeugt. Falls sich die Kachel bereits in dem Cache Verzeichnis befindet, wird zu der Kachel kein Request
 *          erzeugt sondern direkt aus dem Cacheverzeichnis kopiert.
 *          Im Anschluß werden die noch fehlenden Kacheln nacheinander runtergeladen und in dem angegebenen Offlineverzeichnis
 *          abgespeichert.
 */
class TilesDownloader : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief TilesDownloader Konstruktor der Klasse TilesDownloader.
     * @param parent abgeleitetes Attribut von QObject.
     * @param screenSize die Größe der Anwendung um zu ermitteln wie viele Tiles runtergeladen werden müssen.
     */
    TilesDownloader(QObject *parent = 0);

    /**
     *  Destruktor der Klasse
     */
    ~TilesDownloader();

public slots:

    /**
     * @brief downloadTiles slot der den Download initialiesiert und startet.
     * @param center Der Mittelpunkt des aktuell angezeigten Bildschirm
     * @param tileProvider Der Provider von dem die Bilddateien heruntergeladen werden.
     * @param zoomLevel das aktuell angezeigte Zoomlevel.
     */
    void downloadTiles(QVariant center, QString tileProvider, int zoomLevel, int depth, QPoint screenSize);

    /**
     * @brief saveTile Slot der genutzt wird um das fertig geladene Teil abzuspeichern. Desweiteren wird mit Hilfe des Slots
     *          der Download des nächsten Tiles gestartet.
     * @param tile Das Tile das abgespeichert wird
     */
    void saveTile(Tile* tile);

signals:

    /**
     * @brief downloadFinished Signal, das ausgelöst wird sobald der Download fertig gestellt wird
     */
    void downloadFinished();

    /**
     * @brief nextTileDownloadStarted Signal für Update der Progress bar.
     * @param counter Die aktuelle Anzahl der runtergeladenen Kacheln
     * @param amount Die Anzahl an Kacheln die runtergeladen werden soll
     */
    void nextTileDownloadStarted(int counter, int amount);

    /**
     * @brief errorOccured Signal das bei Fehlern versendet wird
     */
    void errorOccured();

private:

    /**
     * @brief createRequest Methode zum erstellen eines Requests, der in einer Liste gespeichert wird. Diese Liste dient zum späteren
     *          runterladen der einzelnen Kacheln.
     * @param tile Kachel zu dem der Request erstellt werden soll
     */
    QNetworkRequest createRequest(Tile * tile);

    /**
     * @brief sendingRequests startet das eigentliche runterladen der Kacheln.
     */
    void sendingRequests();

    /**
     * @brief m_tileProvider der Provider der Kacheln
     */
    QString m_tileProvider;

    /**
     * @brief m_startTile die Ursprungkachel von der aus die restlichen Kacheln ermittelt werden
     */
    Tile * m_startTile;

    /**
     * @brief m_tom Klasse mit der die Bilddateien auf dem System verwaltet werden können.
     */
    TileOfflineManager *m_tom;

    /**
     * @brief m_screenSize die Bildschirmgröße der Anwendung
     */
    QPoint m_screenSize;

    /**
     * @brief m_downloadTiles Liste die die Daten zu den jeweiligen Kacheln enthält.
     */
    QList<Tile *> m_downloadTiles;

    /**
     * @brief m_downloadTiles Liste die die Daten zu den jeweiligen Kacheln enthält.
     */
    QList<Tile *> m_requests;

    /**
     * @brief m_counter Zählvariable in der die fertig runtergeladenen Kacheln mitgezählt werden.
     *          Dient zur Darstellung der Progressbar.
     */
    int m_counter;
};

#endif // TILESDOWNLOADER_H



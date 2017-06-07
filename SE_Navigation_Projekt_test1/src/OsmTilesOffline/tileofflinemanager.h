#ifndef TILEOFFLINEMANAGER_H
#define TILEOFFLINEMANAGER_H

#include "tile.h"
#include "src/settings.h"

#include <QObject>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QStorageInfo>

class TileOfflineManager : public QObject
{
    Q_OBJECT
public:
    explicit TileOfflineManager(QString format, QObject *parent = 0);

    /**
     * @brief saveToFile speichert das Tile in ein Standardverzeichnis
     *          Vorher sollte mit geprüft werden ob es im Cache oder im Offline Verzeichnis vorhanden ist.
     *          Methode: copyCacheFileIfPossible() (Siehe unten)
     * @param tile das Tile das gespeichert werden soll
     * @return gibt an ob das speichern erfolgreich war oder nicht.
     */
    bool saveToFile(Tile * tile);

    /**
     * @brief deleteAll Lösche alle gespeicherten Offline-Verzeichnisse.
     * @return Gibt an ob das Löschen erfolgreich war oder nicht.
     */
    bool deleteAll();

    /**
     * @brief deleteTile Lösche das angegebene Tile aus dem Offline-Verzeichnis.
     * @param das Tile das gelöscht werden soll.
     * @return Gibt an ob das Löschen des Tile erfolgreich war.
     */
    bool deleteTile(Tile *tile);

    /**
     * @brief contains überprüft ob ein Tile bereits in dem Offline Verzeichnis gespeichert ist
     * @param tile Tile das überprüft werden soll
     * @return Gibt true zurück falls das Tile schon vorhanden ist.
     *      Falls es nicht vorhanden ist gibt die Methode false zurück.
     */
    bool contains(Tile *tile, QStandardPaths::StandardLocation location);

    /**
     * @brief copyChacheTileIfPossible Prüft ob sich das Tile im Cache befindet und kopiert es falls nötig
     *          in das Offline Verzeichnis
     * @param tile das Tile, das auf Existenz geprüft werden soll.
     * @return Gibt true zurück falls es erfolgreich kopiert wurde oder es sich bereits in dem Verzeichnis befindet.
     *          Andernfalls false
     */
    bool copyChacheTileIfPossible(Tile *tile);

    /**
     * @brief searchSubdirectoriesForTile durchsucht das mitgegebene Verzeichnis nach dem tile und gibt den Pfad
     *          zum tile zurück.
     * @param tile das tile, das gesucht wird
     * @param directory das Verzeichnis in dem gesucht wird
     * @return Der Pfad zum Tile falls eins gefunden wurde ansonsten wird ein leerstring zurück gegeben.
     */
    QString searchSubdirectoriesForTile(Tile * tile, QString directory);



signals:

    void notEnoughSpace();

public slots:

private:
    Settings m_settings;

    int m_currentlyUsedSpace;

    /**
     * @brief calculateUsedSpace ermittelt wie viel Speicher bereits verbraucht wurde
     */
    void calculateUsedSpace();

    /**
     * @brief createFileName erstellt den Dateinamen unter dem das Tile gespeichert werden soll
     * @param tile wofür der Dateiname erstellt werden soll
     * @return der Dateiname für das Tile.
     */
    QString createFileName(Tile *tile);

    QString m_format;
};

#endif // TILEOFFLINEMANAGER_H

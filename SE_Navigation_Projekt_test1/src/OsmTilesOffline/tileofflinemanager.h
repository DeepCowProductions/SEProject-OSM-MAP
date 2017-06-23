#ifndef TILEOFFLINEMANAGER_H
#define TILEOFFLINEMANAGER_H

#include <QObject>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QStorageInfo>

#include "tile.h"
#include "src/settings.h"
class TileOfflineManager : public QObject
{
    Q_OBJECT
public:
    explicit TileOfflineManager(QObject *parent = 0);
    ~TileOfflineManager();

    /**
     * @brief saveToFile speichert das Tile in ein Standardverzeichnis
     *          Vorher sollte mit geprüft werden ob es im Cache oder im Offline Verzeichnis vorhanden ist.
     *          Methode: copyCacheFileIfPossible() (Siehe unten)
     * @param tile das Tile das gespeichert werden soll
     * @return gibt an ob das speichern erfolgreich war oder nicht.
     */
    bool saveToFile(Tile * tile);

    Q_INVOKABLE bool deleteAll();
    /**
     * @brief deleteTile Lösche das angegebene Tile aus dem Offline-Verzeichnis.
     * @param das Tile das gelöscht werden soll.
     * @return Gibt an ob das Löschen des Tile erfolgreich war.
     */
    bool deleteTile(Tile *tile);

    /**
     * @brief copyChacheTileIfPossible Prüft ob sich das Tile im Cache befindet und kopiert es falls nötig
     *          in das Offline Verzeichnis
     * @param tile das Tile, das auf Existenz geprüft werden soll.
     * @return Gibt true zurück falls es erfolgreich kopiert wurde oder es sich bereits in dem Verzeichnis befindet.
     *          Andernfalls false
     */
    bool copyChacheTileIfPossible(Tile *tile);

    /**
     * @brief changeOfflineDirectory Methode zum Wechseln des Offlineverzeichnis
     * @param newDirectory das neue Offlineverzeichnis
     * @return gibt an ob das Wechseln des Offlineverzeichnis erfolgreich war
     */
    bool changeOfflineDirectory(QString newDirectory);

    /**
     * @brief calculateUsedSpace ermittelt wie viel Speicher bereits verbraucht wurde
     */
    Q_INVOKABLE int calculateUsedSpace(QString directory);

    int offlineMapSize() const;
    void setOfflineMapSize(int offlineMapSize);

    QString offlinePath() const;
    void setOfflinePath(const QString &offlinePath);

signals:


    /**
     * @brief notEnoughSpace Signal das augelöst wird wennd er Speicher nicht ausreichend war
     */
    void notEnoughSpace();

public slots:

private:

    /**
     * @brief findCacheDirectory Methode die das Cacheverzeichnis anhand der Kachelsignatur findet und dies zwischensspeichert
     */
    void findCacheDirectory();

    /**
     * @brief m_settings Variable zum lesen der vorher eingestellten Optionen
     */
    QSettings *m_settings;

    /**
     * @brief m_offlineMapSize die maximale Größe des Offlineverzeichnis
     */
    int m_offlineMapSize;

    /**
     * @brief m_offlinePath Pfad zum Offlineverzeichnis
     */
    QString m_offlinePath;

    /**
     * @brief m_currentlyUsedSpace Variable für den bisher verbrauchten Speicherplatz
     */
    int m_currentlyUsedSpace;

    /**
     * @brief m_cachedirectory Variable zum speichern des Cachedirectory
     */
    QDir m_cachedirectory;

    /**
     * @brief createFileName erstellt den Dateinamen unter dem das Tile gespeichert werden soll
     * @param tile wofür der Dateiname erstellt werden soll
     * @return der Dateiname für das Tile.
     */
    QString createFileName(Tile *tile);


};

#endif // TILEOFFLINEMANAGER_H

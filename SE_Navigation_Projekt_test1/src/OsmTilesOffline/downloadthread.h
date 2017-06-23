#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include "tilesdownloader.h"
/**
 * @brief The DownloadThread class Klasse zum Runterladen von Bilddateien in einem eigenen Thread
 */
class DownloadThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief DownloadThread Konstruktor der Klasse Downloadthread
     * @param parent
     */
    DownloadThread(QObject *parent = 0);
    ~DownloadThread();

    /**
     * @brief run In der Run-Methode wird der Code definiert, der in dem Thread ausgeführt werden soll.
     */
    void run() Q_DECL_OVERRIDE;

signals:

    /**
     * @brief updateProgressBar Signal zum aktuallisieren der Progress Bar in der grafischen Oberfläche
     * @param current die aktuell runtergeladene Anzahl an kacheln
     * @param amount die Menge an kacheln die runtergeladen werden müssen
     */
    void updateProgressBar(int current, int amount);

    /**
     * @brief downloadFinished Signal um der Oberfläche mitzuteilen das der Download beendet wurde
     */
    void downloadFinished();

    /**
     * @brief downloadFailed Signal um der Oberfläche mitzuteilen das während dem Download ein Fehler aufgetreten ist
     */
    void downloadFailed();


public slots:

    /**
     * @brief startDownload Slot zum starten des Downloads. Die Parameter werden zunächst zwischengespeichert und im
     *          Anschluß an den Downloader weitergeleitet
     * @param center Der Mittelpunkt des aktuellen Kartenausschnitts
     * @param provider der Provider der Kacheln
     * @param zoomLevel das aktuelle Zoomlevel
     * @param depth Die Anzahl an Zoomlevel die runtergeladen werden sollen
     * @param width die Breite des Fensters
     * @param height die Höhe des Fensters
     */
    void startDownload(QVariant center, QString provider, int zoomLevel, int depth, int width, int height);


private:

    /**
     * @brief m_mutex Variable zum Blockieren der anderen Threads um Variablen threadsicher zu machen
     */
    QMutex m_mutex;

    /**
     * @brief m_center Zwischenvariable für das Center (siehe oben)
     */
    QVariant m_center;

    /**
     * @brief m_provider Zwischenvariable für den Provider(siehe oben)
     */
    QString m_provider;

    /**
     * @brief m_windowSize Zwischenvariable für die Fenstergröße(siehe oben)
     */
    QPoint m_windowSize;

    /**
     * @brief m_zoomLevel Zwischenvariable für das aktuelle Zoomlevel(siehe oben)
     */
    int m_zoomLevel;

    /**
     * @brief m_depth Zwischenvariable für runterzuladenden Zoomlevel(siehe oben)
     */
    int m_depth;
};

#endif // DOWNLOADTHREAD_H

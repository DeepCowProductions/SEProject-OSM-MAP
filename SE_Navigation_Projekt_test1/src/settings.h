#ifndef SETTINGS_H
#define SETTINGS_H

#include <QQuickItem>
#include <QObject>
#include <QSettings>
#include <QDir>
//#include "src/OsmTilesOffline/tileofflinemanager.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#endif
/**
 * @brief The Settings class
 * Settings-Klasse um Einstellungen der App abzurufen und zu speichern
 *
 * [...]
 */
class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString offlineDirectory READ offlineDirectory WRITE setOfflineDirectory NOTIFY offlineDirectoryChanged)
    Q_PROPERTY(int maxOfflineMapSize READ maxOfflineMapSize WRITE setMaxOfflineMapSize NOTIFY maxOfflineMapSizeChanged)
    Q_PROPERTY(bool sdCard READ sdCard WRITE setSdCard NOTIFY sdCardChanged)
    Q_PROPERTY(bool device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool existsSdCar READ existsSdCar WRITE setExistsSdCar NOTIFY existsSdCarChanged)

public:
    /**
     * @brief Settings Konstruktor der Klasse
     */
    Settings();
    ~Settings();

    int maxOfflineMapSize() const;
    QString offlineDirectory() const;
    int usedOfflineDirectorySize() const;
    bool sdCard() const;
    bool device() const;
    bool existsSdCar() const;


signals:

    void maxOfflineMapSizeChanged(int maxOfflineMapSize);
    void offlineDirectoryChanged(QString offlineDirectory);

    void sdCardChanged(bool sdCard);

    void deviceChanged(bool device);

    void existsSdCarChanged(bool existsSdCar);

public slots:
    void save();
    void load();

    void setMaxOfflineMapSize(int maxOfflineMapSize);
    void setOfflineDirectory(QString offlineDirectory);
    void setDevice(bool device);
    void setSdCard(bool sdCard);
    void setExistsSdCar(bool existsSdCar);

protected:
    virtual void readSettings();
    virtual void writeSettings();

private:

    /**
     * @brief m_settings Settingsklasse mit deren Hilfe die Einstellungen gesichert und gelesen werden
     */
    QSettings * m_settings = Q_NULLPTR;

    /**
     * @brief m_maxOfflineMapSize Maximale Offlineverzeichnisgröße
     */
    int m_maxOfflineMapSize;

    /**
     * @brief m_offlineDirectory Pfad zum Offlineverzeichnis
     */
    QString m_offlineDirectory;

    /**
     * @brief m_sdCard Variable ob SD-Karte gewählt wurde
     *      Noch nicht implementiert
     */
    bool m_sdCard;

    /**
     * @brief m_device Variable ob Gerätespeicher genutzt werden soll
     *      Noch nicht implementiert
     */
    bool m_device;

    /**
     * @brief m_existsSdCar Variable die angibt ob eine SD-Karte vorhanden ist
     *      Noch nicht implementiert
     */
    bool m_existsSdCar;

    /**
     * @brief m_sdCardPath Pfad zur SD-Karte
     */
    QString m_sdCardPath;
};

#endif // SETTINGS_H

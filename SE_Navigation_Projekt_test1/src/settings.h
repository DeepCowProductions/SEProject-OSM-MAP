#ifndef SETTINGS_H
#define SETTINGS_H

#include <QQuickItem>
#include <QObject>
#include <QSettings>
#include <QDir>
//#include "src/OsmTilesOffline/tileofflinemanager.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif
/**
 * @brief The Settings class
 * Settingsklasse specuhert und verwaltet Informationen und Einstellungen der App.
 * Diese Klasse macht intern gebrauch der QSettings Klasse um eine config Datei zu speichern,
 * welche global von der gesamten app gelesen werden kann.
 * Die hier definierten Properties stellen teilweise Einstellungen dar, die auf diese weise gespeichert werden.
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
    /**
     * @brief save ruft writeSettings auf.
     */
    void save();
    /**
     * @brief load ruft readSettings auf.
     */
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

    QSettings * m_settings = Q_NULLPTR;

    int m_maxOfflineMapSize;
    QString m_offlineDirectory;
    bool m_sdCard;
    bool m_device;
    bool m_existsSdCar;

    QString m_sdCardPath;
};

#endif // SETTINGS_H

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
 * Settings class to hold inforamtion about the current app status and settings.
 *
 * [...]
 */
class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString home READ home WRITE setHome NOTIFY homeChanged)
    Q_PROPERTY(int maxOfflineMapSize READ maxOfflineMapSize WRITE setMaxOfflineMapSize NOTIFY maxOfflineMapSizeChanged)
    Q_PROPERTY(int currentOfflineMapSize READ currentOfflineMapSize WRITE setCurrentOfflineMapSize NOTIFY currentOfflineMapSizeChanged)
    Q_PROPERTY(int  maxNormalMapChacheSize READ maxNormalMapChacheSize WRITE setMaxNormalMapChacheSize NOTIFY maxNormalMapChacheSizeChanged)
    Q_PROPERTY(QString offlineDirectory READ offlineDirectory WRITE setOfflineDirectory NOTIFY offlineDirectoryChanged)
    Q_PROPERTY(int usedOfflineDirectorySize READ usedOfflineDirectorySize WRITE setUsedOfflineDirectorySize NOTIFY usedOfflineDirectorySizeChanged)
    Q_PROPERTY(bool sdCard READ sdCard WRITE setSdCard NOTIFY sdCardChanged)
    Q_PROPERTY(bool device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool existsSdCar READ existsSdCar WRITE setExistsSdCar NOTIFY existsSdCarChanged)

public:
    Settings();
    ~Settings();

    QString home() const;
    int maxNormalMapChacheSize() const;
    int currentOfflineMapSize() const;
    int maxOfflineMapSize() const;
    QString offlineDirectory() const;
    int usedOfflineDirectorySize() const;
    bool sdCard() const;
    bool device() const;
    bool existsSdCar() const;


signals:

    void homeChanged(QString home);
    void maxNormalMapChacheSizeChanged(int maxNormalMapChacheSize);
    void currentOfflineMapSizeChanged(int currentOfflineMapSize);
    void maxOfflineMapSizeChanged(int maxOfflineMapSize);
    void offlineDirectoryChanged(QString offlineDirectory);
    void usedOfflineDirectorySizeChanged(int usedOfflineDirectorySize);

    void sdCardChanged(bool sdCard);

    void deviceChanged(bool device);

    void existsSdCarChanged(bool existsSdCar);

public slots:
    void save();
    void load();

    void setHome(QString home);
    void setMaxNormalMapChacheSize(int maxNormalMapChacheSize);
    void setCurrentOfflineMapSize(int currentOfflineMapSize);
    void setMaxOfflineMapSize(int maxOfflineMapSize);
    void setOfflineDirectory(QString offlineDirectory);
    void setUsedOfflineDirectorySize(int usedOfflineDirectorySize);
    void setDevice(bool device);
    void setSdCard(bool sdCard);
    void setExistsSdCar(bool existsSdCar);

protected:
    virtual void readSettings();
    virtual void writeSettings();

private:


    QSettings * m_settings = Q_NULLPTR;

    int m_maxNormalMapChacheSize;
    int m_currentOfflineMapSize;
    int m_maxOfflineMapSize;
    QString m_home;
    QString m_offlineDirectory;
    int m_usedOfflineDirectorySize;
    bool m_sdCard;
    bool m_device;
    bool m_existsSdCar;

    QString m_sdCardPath;
};

#endif // SETTINGS_H

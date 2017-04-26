#ifndef SETTINGS_H
#define SETTINGS_H

#include <QQuickItem>
#include <QObject>
#include <QSettings>

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
    Q_PROPERTY(bool useOfflineMap READ useOfflineMap WRITE setUseOfflineMap NOTIFY useOfflineMapChanged)
    Q_PROPERTY(int maxOfflineMapSize READ maxOfflineMapSize WRITE setMaxOfflineMapSize NOTIFY maxOfflineMapSizeChanged)
    Q_PROPERTY(int currentOfflineMapSize READ currentOfflineMapSize WRITE setCurrentOfflineMapSize NOTIFY currentOfflineMapSizeChanged)
    Q_PROPERTY(bool useNormalMapCache READ useNormalMapCache WRITE setUseNormalMapCache NOTIFY useNormalMapCacheChanged)
    Q_PROPERTY(int  maxNormalMapChacheSize READ maxNormalMapChacheSize WRITE setMaxNormalMapChacheSize NOTIFY maxNormalMapChacheSizeChanged)


public:
    Settings();
    ~Settings();

    QString home() const;
    bool useOfflineMap() const;
    int maxNormalMapChacheSize() const;
    int currentOfflineMapSize() const;
    int maxOfflineMapSize() const;
    bool useNormalMapCache() const;

signals:

    void homeChanged(QString home);
    void useOfflineMapChanged(bool useOfflineMap);
    void maxNormalMapChacheSizeChanged(int maxNormalMapChacheSize);
    void currentOfflineMapSizeChanged(int currentOfflineMapSize);
    void maxOfflineMapSizeChanged(int maxOfflineMapSize);
    void useNormalMapCacheChanged(bool useNormalMapCache);

public slots:
    void save();
    void load();

    void setHome(QString home);
    void setUseOfflineMap(bool useOfflineMap);
    void setMaxNormalMapChacheSize(int maxNormalMapChacheSize);
    void setCurrentOfflineMapSize(int currentOfflineMapSize);
    void setMaxOfflineMapSize(int maxOfflineMapSize);
    void setUseNormalMapCache(bool useNormalMapCache);

protected:
    virtual void readSettings();
    virtual void writeSettings();

private:


    QSettings * m_settings = Q_NULLPTR;

    int m_maxNormalMapChacheSize;
    int m_currentOfflineMapSize;
    int m_maxOfflineMapSize;
    QString m_home;
    bool m_useOfflineMap;
    bool m_useNormalMapCache;
};

#endif // SETTINGS_H

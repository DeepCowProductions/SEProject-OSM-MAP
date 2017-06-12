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
    Q_PROPERTY(int maxOfflineMapSize READ maxOfflineMapSize WRITE setMaxOfflineMapSize NOTIFY maxOfflineMapSizeChanged)
    Q_PROPERTY(int currentOfflineMapSize READ currentOfflineMapSize WRITE setCurrentOfflineMapSize NOTIFY currentOfflineMapSizeChanged)
    Q_PROPERTY(int  maxNormalMapChacheSize READ maxNormalMapChacheSize WRITE setMaxNormalMapChacheSize NOTIFY maxNormalMapChacheSizeChanged)
    Q_PROPERTY(QString offlineDirectory READ offlineDirectory WRITE setOfflineDirectory NOTIFY offlineDirectoryChanged)
    Q_PROPERTY(int usedOfflineDirectorySize READ usedOfflineDirectorySize WRITE setUsedOfflineDirectorySize NOTIFY usedOfflineDirectorySizeChanged)

public:
    Settings();
    ~Settings();

    QString home() const;
    int maxNormalMapChacheSize() const;
    int currentOfflineMapSize() const;
    int maxOfflineMapSize() const;
    QString offlineDirectory() const;
    int usedOfflineDirectorySize() const;

signals:

    void homeChanged(QString home);
    void maxNormalMapChacheSizeChanged(int maxNormalMapChacheSize);
    void currentOfflineMapSizeChanged(int currentOfflineMapSize);
    void maxOfflineMapSizeChanged(int maxOfflineMapSize);
    void offlineDirectoryChanged(QString offlineDirectory);
    void usedOfflineDirectorySizeChanged(int usedOfflineDirectorySize);

public slots:
    void save();
    void load();

    void setHome(QString home);
    void setMaxNormalMapChacheSize(int maxNormalMapChacheSize);
    void setCurrentOfflineMapSize(int currentOfflineMapSize);
    void setMaxOfflineMapSize(int maxOfflineMapSize);
    void setOfflineDirectory(QString offlineDirectory);
    void setUsedOfflineDirectorySize(int usedOfflineDirectorySize);

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
};

#endif // SETTINGS_H

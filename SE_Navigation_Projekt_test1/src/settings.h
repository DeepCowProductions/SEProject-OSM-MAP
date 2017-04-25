#ifndef SETTINGS_H
#define SETTINGS_H

#include <QQuickItem>
#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString home READ home WRITE setHome NOTIFY homeChanged)
    Q_PROPERTY(bool useOfflineCache READ useOfflineCache WRITE setUseOfflineCache NOTIFY useOfflineCacheChanged)

public:
    Settings();
    ~Settings();
    QString home() const;
    bool useOfflineCache() const;

signals:

    void homeChanged(QString home);
    void useOfflineCacheChanged(bool useOfflineCache);

public slots:
    void save();
    void load();

    void setHome(QString home);
    void setUseOfflineCache(bool useOfflineCache);

protected:
    void saveSettings();

private:
    QString m_home;
    bool m_useOfflineCache;

    QSettings * m_settings = Q_NULLPTR;

};

#endif // SETTINGS_H

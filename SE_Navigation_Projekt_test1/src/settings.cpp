#include "settings.h"

Settings::Settings()
{
    qDebug() << "Settings Construtor";
    setHome("Ierlohn");
    setUseOfflineCache(false);
    m_settings = new QSettings("FH-SWF",qApp->applicationName(), Q_NULLPTR);

    setUseOfflineCache(m_settings->value("useOfflineMapCache").toBool());
//    [...]
    qDebug() << m_settings->fileName() << m_settings->organizationName();
    m_settings->setValue("useOfflineMapCache",m_useOfflineCache);
    m_settings->sync();
}

Settings::~Settings()
{
    m_settings->sync();
    if (m_settings)
        delete m_settings;
}

QString Settings::home() const
{
    return m_home;
}

bool Settings::useOfflineCache() const
{
    return m_useOfflineCache;
}

void Settings::save()
{
    saveSettings();
    m_settings->sync();
}

void Settings::load()
{
    // entweder ?
    m_settings->sync();

    // oder ?
    setUseOfflineCache(m_settings->value("useOfflineMapCache").toBool());
//    [...]
}

void Settings::saveSettings()
{
    // entweder ?
    m_settings->sync();

    // oder ?
    m_settings->setValue("useOfflineMapCache",m_useOfflineCache);
//    [...]
}

void Settings::setHome(QString home)
{
    if (m_home == home)
        return;

    m_home = home;
    emit homeChanged(home);
}

void Settings::setUseOfflineCache(bool useOfflineCache)
{
    if (m_useOfflineCache == useOfflineCache)
        return;

    m_useOfflineCache = useOfflineCache;
    emit useOfflineCacheChanged(useOfflineCache);
}

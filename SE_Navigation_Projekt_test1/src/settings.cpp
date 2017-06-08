#include "settings.h"

Settings::Settings()
{
    qDebug() << "Settings Construtor";

//    m_settings = new QSettings("FH-SWF",qApp->applicationName(), Q_NULLPTR);
    m_settings = new QSettings();   // since we set app-name and company in main.cpp we can use dfault constructor

    // read settings
    readSettings();


    qDebug() << "settings saved at: " << m_settings->fileName() << "  with organisation name: " << m_settings->organizationName();
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

bool Settings::useOfflineMap() const
{
    return m_useOfflineMap;
}

int Settings::maxNormalMapChacheSize() const
{
    return m_maxNormalMapChacheSize;
}

int Settings::currentOfflineMapSize() const
{
    return m_currentOfflineMapSize;
}

int Settings::maxOfflineMapSize() const
{
    return m_maxOfflineMapSize;
}

bool Settings::useNormalMapCache() const
{
    return m_useNormalMapCache;
}

QString Settings::offlineDirectory() const
{
    return m_offlineDirectory;
}

int Settings::usedOfflineDirectorySize() const
{
    return m_usedOfflineDirectorySize;
}

void Settings::save()
{
    qDebug() << "invoke Settings:save";
//    m_settings->sync();
    writeSettings();
//    m_settings->sync();
}

void Settings::load()
{
    qDebug() << "invoke Settings::load";
//    m_settings->sync();
    readSettings();
//    m_settings->sync();
}

void Settings::readSettings()
{
    qDebug() << "Settings::readSettings: reading settings from file " << m_settings->fileName();
    // get properties from settings
    setHome(m_settings->value("home").toString());
    setUseOfflineMap(m_settings->value("useOfflineMap").toBool());
    setUseNormalMapCache(m_settings->value("useNormalMapCache").toBool());
    setMaxNormalMapChacheSize(m_settings->value("maxNormalMapChacheSize").toInt());
    setMaxOfflineMapSize(m_settings->value("maxOfflineMapSize").toInt());
    setCurrentOfflineMapSize(m_settings->value("currentOfflineMapSize").toInt());
    setOfflineDirectory(m_settings->value("offlineDirectory").toString());
    // #???#

}

void Settings::writeSettings()
{
    qDebug() << "Settings::writeSettings: writing settings to file " << m_settings->fileName();
    // write properties to settings
    m_settings->setValue("home",m_home);
    m_settings->setValue("useOfflineMap",m_useOfflineMap);
    m_settings->setValue("useNormalMapCache",m_useNormalMapCache);
    m_settings->setValue("maxNormalMapChacheSize",m_maxNormalMapChacheSize);
    m_settings->setValue("maxOfflineMapSize",m_maxOfflineMapSize);
    m_settings->setValue("currentOfflineMapSize",m_currentOfflineMapSize);
    m_settings->setValue("offlineDirectory", m_offlineDirectory);
    m_settings->setValue("usedOfflineDirectorySize", m_usedOfflineDirectorySize);

    // force writing to storage by calling sync - not neccessary but makes things easier
    m_settings->sync();
}

void Settings::setHome(QString home)
{
    if (m_home == home)
        return;

    m_home = home;
    emit homeChanged(home);
}

void Settings::setUseOfflineMap(bool useOfflineMap)
{
    if (m_useOfflineMap == useOfflineMap)
        return;

    m_useOfflineMap = useOfflineMap;
    emit useOfflineMapChanged(useOfflineMap);
    qDebug() << "useOfflineMap: " << m_useOfflineMap;
}

void Settings::setMaxNormalMapChacheSize(int maxNormalMapChacheSize)
{
    if (m_maxNormalMapChacheSize == maxNormalMapChacheSize)
        return;

    m_maxNormalMapChacheSize = maxNormalMapChacheSize;
    emit maxNormalMapChacheSizeChanged(maxNormalMapChacheSize);
}

void Settings::setCurrentOfflineMapSize(int currentOfflineMapSize)
{
    if (m_currentOfflineMapSize == currentOfflineMapSize)
        return;

    m_currentOfflineMapSize = currentOfflineMapSize;
    emit currentOfflineMapSizeChanged(currentOfflineMapSize);
}

void Settings::setMaxOfflineMapSize(int maxOfflineMapSize)
{
    if (m_maxOfflineMapSize == maxOfflineMapSize)
        return;

    m_maxOfflineMapSize = maxOfflineMapSize;
    emit maxOfflineMapSizeChanged(maxOfflineMapSize);
}

void Settings::setUseNormalMapCache(bool useNormalMapCache)
{
    if (m_useNormalMapCache == useNormalMapCache)
        return;

    m_useNormalMapCache = useNormalMapCache;
    emit useNormalMapCacheChanged(useNormalMapCache);
    qDebug() << "useNormalMapCache: " << m_useNormalMapCache;
}

void Settings::setOfflineDirectory(QString offlineDirectory)
{
    if (m_offlineDirectory == offlineDirectory)
        return;

    m_offlineDirectory = offlineDirectory;
    emit offlineDirectoryChanged(offlineDirectory);
}

void Settings::setUsedOfflineDirectorySize(int usedOfflineDirectorySize)
{
    if (m_usedOfflineDirectorySize == usedOfflineDirectorySize)
        return;

    m_usedOfflineDirectorySize = usedOfflineDirectorySize;
    emit usedOfflineDirectorySizeChanged(usedOfflineDirectorySize);
}

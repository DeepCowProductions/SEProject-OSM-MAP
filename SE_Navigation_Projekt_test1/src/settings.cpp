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

void Settings::save()
{
//    m_settings->sync();
    writeSettings();
//    m_settings->sync();
}

void Settings::load()
{
//    m_settings->sync();
    readSettings();
//    m_settings->sync();
}

void Settings::readSettings()
{
    // get properties from settings
    setHome(m_settings->value("home").toString());
    setUseOfflineMap(m_settings->value("useOfflineMap").toBool());
    setUseNormalMapCache(m_settings->value("useNormalMapCache").toBool());
    setMaxNormalMapChacheSize(m_settings->value("maxNormalMapChacheSize").toInt());
    setMaxOfflineMapSize(m_settings->value("maxOfflineMapSize").toInt());
    setCurrentOfflineMapSize(m_settings->value("currentOfflineMapSize").toInt()); // #???#

}

void Settings::writeSettings()
{
    // write properties to settings
    m_settings->setValue("home",m_home);
    m_settings->setValue("useOfflineMap",m_useOfflineMap);
    m_settings->setValue("useNormalMapCache",m_useNormalMapCache);
    m_settings->setValue("maxNormalMapChacheSize",m_maxNormalMapChacheSize);
    m_settings->setValue("maxOfflineMapSize",m_maxOfflineMapSize);
    m_settings->setValue("currentOfflineMapSize",m_currentOfflineMapSize);

    // force writeing to storage by calling sync - not neccessary but makes things easier
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
}

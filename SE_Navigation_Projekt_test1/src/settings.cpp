#include "settings.h"
#include <QStandardPaths>
#include "src/OsmTilesOffline/tileofflinemanager.h"

Settings::Settings()
{
    qDebug() << "Settings Construtor";

    //    m_settings = new QSettings("FH-SWF",qApp->applicationName(), Q_NULLPTR);
    m_settings = new QSettings();   // since we set app-name and company in main.cpp we can use dfault constructor

    // read settings
    readSettings();
    if(m_offlineDirectory.isEmpty())
        setOfflineDirectory(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if(m_maxOfflineMapSize <= 0)
        setMaxOfflineMapSize(1000);
    m_existsSdCar = false;

#ifdef Q_OS_ANDROID
    QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    QAndroidJniObject mediaPath = mediaDir.callObjectMethod( "getAbsolutePath", "()Ljava/lang/String;" );
    QDir sdCardDircectory(mediaPath.toString() + "/Android/data/");
    if(sdCardDircectory.exists()){
        m_existsSdCar = true;
        m_sdCardPath = sdCardDircectory.absolutePath() + "osm-tiles";
    }

#endif

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

QString Settings::offlineDirectory() const
{
    return m_offlineDirectory;
}

int Settings::usedOfflineDirectorySize() const
{
    return m_usedOfflineDirectorySize;
}

bool Settings::sdCard() const
{
    return m_sdCard;
}

bool Settings::device() const
{
    return m_device;
}

bool Settings::existsSdCar() const
{
    return m_existsSdCar;
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
    setMaxNormalMapChacheSize(m_settings->value("maxNormalMapChacheSize").toInt());
    setMaxOfflineMapSize(m_settings->value("maxOfflineMapSize").toInt());
    setCurrentOfflineMapSize(m_settings->value("currentOfflineMapSize").toInt());
    setOfflineDirectory(m_settings->value("offlineDirectory").toString());
    setUsedOfflineDirectorySize(m_settings->value("usedOfflineDirectorySize").toInt());
    setSdCard(m_settings->value("sdCard").toBool());
    setDevice(m_settings->value("deviceStorage").toBool());
    // #???#

}

void Settings::writeSettings()
{
    qDebug() << "Settings::writeSettings: writing settings to file " << m_settings->fileName();
    // write properties to settings
    m_settings->setValue("home",m_home);
    m_settings->setValue("maxNormalMapChacheSize",m_maxNormalMapChacheSize);
    m_settings->setValue("maxOfflineMapSize",m_maxOfflineMapSize);
    m_settings->setValue("currentOfflineMapSize",m_currentOfflineMapSize);
    m_settings->setValue("offlineDirectory", m_offlineDirectory);

    m_settings->setValue("sdCard", m_sdCard);
    m_settings->setValue("deviceStorage", m_device);

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
    m_settings->setValue("usedOfflineDirectorySize", m_usedOfflineDirectorySize);
    m_settings->sync();
    readSettings();
    emit usedOfflineDirectorySizeChanged(usedOfflineDirectorySize);
}

void Settings::setSdCard(bool sdCard)
{
    if (m_sdCard == sdCard)
        return;
    m_sdCard = sdCard;
    if(m_sdCard){
        TileOfflineManager offline;
        offline.changeOfflineDirectory(m_sdCardPath);
    }
    emit sdCardChanged(sdCard);
}

void Settings::setDevice(bool device)
{
    if (m_device == device)
        return;
    m_device = device;
    if(m_sdCard){
        TileOfflineManager offline;
        offline.changeOfflineDirectory(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }
    emit deviceChanged(device);
}

void Settings::setExistsSdCar(bool existsSdCar)
{
    if (m_existsSdCar == existsSdCar)
        return;

    m_existsSdCar = existsSdCar;
    emit existsSdCarChanged(existsSdCar);
}

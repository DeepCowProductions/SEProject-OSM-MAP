#include "tileofflinemanager.h"

TileOfflineManager::TileOfflineManager(QString format, QObject *parent) : QObject(parent)
{
    m_format = format;
    m_currentlyUsedSpace = calculateUsedSpace();
    m_settings.setUsedOfflineDirectorySize(m_currentlyUsedSpace);
}

bool TileOfflineManager::saveToFile(Tile *tile)
{
    bool ret = false;
    QStorageInfo info(m_settings.offlineDirectory());
    //    qDebug() << "Bytes available: " << info.bytesAvailable();
    if(m_currentlyUsedSpace < m_settings.maxOfflineMapSize() && info.bytesAvailable() - tile->imageData().size() > 0){
        if(tile->imageData().isEmpty()){
            qDebug() << "Datei ist leer";
            return false;
        }
        QDir saveDirectory;
        if(m_settings.offlineDirectory().isEmpty()){
            saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
            m_settings.setOfflineDirectory(saveDirectory.absolutePath());
        }
        else
            saveDirectory = QDir(m_settings.offlineDirectory());
        QDir dir;
        dir.mkpath(saveDirectory.path());
        QFile tileImage(saveDirectory.filePath(createFileName(tile)));
        if(tileImage.open(QFile::WriteOnly |QFile::Truncate)){
            if(tileImage.write(tile->imageData()) != -1){
                ret = true;
                m_currentlyUsedSpace += tileImage.size();
            }
        }
    }else{
        emit notEnoughSpace();
    }
    m_settings.setUsedOfflineDirectorySize(calculateUsedSpace());
    return ret;
}

bool TileOfflineManager::deleteAll(QString directory)
{
    QDir saveDirectory;

    if(directory == "offline"){
        if(m_settings.offlineDirectory().isEmpty()){
            saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        }
        else{
            saveDirectory = QDir(m_settings.offlineDirectory());
        }
    }
    else if(directory == "cache")
        saveDirectory = QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    else if(directory == "genericcache")
        saveDirectory = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + "/QtLocation/5.8/tiles/osm/");
    else
        return false;
QStringList filters;
filters << "*.jpg" << "*.png";
int entries = saveDirectory.entryList(filters).size();
int counter = 0;

foreach (QString file, saveDirectory.entryList(filters)) {
    if(QFile::remove(saveDirectory.filePath(file))){
        counter++;
    }
}
qDebug() << QString::number(counter) + "/" +  QString::number(entries) <<  " were deleted!";
return counter == entries;
}

bool TileOfflineManager::deleteTile(Tile * tile)
{
    bool ret = false;
    if(m_settings.offlineDirectory().isEmpty()){
        QDir saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        if(contains(tile, QStandardPaths::DataLocation)){
            ret = QFile::remove(saveDirectory.filePath(createFileName(tile)));
        }else{
            ret = true;
        }
    }else{
        QString directory = searchSubdirectoriesForTile(tile, m_settings.offlineDirectory());
        if(!(directory != "")){
            ret = QFile::remove(directory + createFileName(tile));
        }else{
            ret = true;
        }
    }
    return ret;
}

bool TileOfflineManager::contains(Tile* tile, QStandardPaths::StandardLocation location)
{
    QDir saveDirectory = QStandardPaths::writableLocation(location);
    bool ret = false;
    if(searchSubdirectoriesForTile(tile, saveDirectory.absolutePath()) != "")
        ret = true;
    return ret;
}


bool TileOfflineManager::copyChacheTileIfPossible(Tile * tile)
{
    //Tile schon im Verzeichnis
    if(m_settings.offlineDirectory() != "" && QDir(m_settings.offlineDirectory()).entryList().contains(createFileName(tile))){
        return true;
    }
    if(contains(tile, QStandardPaths::DataLocation))
        return true;

    //Tile im Cache Verzeichnis
    bool ret = false;
    QDir saveDirectory;
    if(m_settings.offlineDirectory().isEmpty()){
        saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        m_settings.setOfflineDirectory(saveDirectory.absolutePath());
    }
    else
        saveDirectory = QDir(m_settings.offlineDirectory());
    QString tileName = createFileName(tile);

    if(contains(tile, QStandardPaths::CacheLocation)){
        QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        QDir cacheDirectory(searchSubdirectoriesForTile(tile, path));
        QFile cacheFile(cacheDirectory.filePath(tileName));
        ret = cacheFile.copy(saveDirectory.filePath(tileName));
        cacheFile.remove();
        qDebug() << "Got tiles from Cache";

    }
    else if(contains(tile, QStandardPaths::GenericCacheLocation)){
        QDir generic(searchSubdirectoriesForTile(tile, QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation)));
        QFile cacheFile(generic.absolutePath().append("/" + tileName));
        ret = cacheFile.copy(saveDirectory.filePath(tileName));
        cacheFile.remove();
        qDebug() << "Got tile from generic Cache";
    }
    m_settings.setUsedOfflineDirectorySize(calculateUsedSpace());
    return ret;
}

QString TileOfflineManager::searchSubdirectoriesForTile(Tile *tile, QString directory)
{
    QString tileDirectory = "";
    bool ret = false;
    QDirIterator it(directory,QDir::Dirs, QDirIterator::Subdirectories );
    while(it.hasNext() && !ret){
        QDir dir(it.next());
        if(dir.entryList().contains(createFileName(tile))){
            tileDirectory = dir.absolutePath();
            ret = true;
        }
    }
    return tileDirectory;
}

int TileOfflineManager::calculateUsedSpace()
{
    int size = 0;
    QDir dir(m_settings.offlineDirectory());
    foreach (QString fileName, dir.entryList()) {
        QFile file(dir.absoluteFilePath(fileName));
        size += file.size();
    }
    return size;
}

QString TileOfflineManager::createFileName(Tile *tile)
{
    QString filename = tile->pluginName();
    filename += "_100-l";
    filename += QLatin1String("-");
    filename += QString::number(tile->mapId());
    filename += QLatin1String("-");
    filename += QString::number(tile->zoomlevel());
    filename += QLatin1String("-");
    filename += QString::number(tile->x());
    filename += QLatin1String("-");
    filename += QString::number(tile->y());
    filename += ".";
    filename += m_format;
    return filename;
}

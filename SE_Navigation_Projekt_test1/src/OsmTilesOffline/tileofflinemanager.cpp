#include "tileofflinemanager.h"

TileOfflineManager::TileOfflineManager(QString format, QObject *parent) : QObject(parent)
{
    m_format = format;
}

bool TileOfflineManager::saveToFile(Tile *tile)
{
    if(tile->imageData().isEmpty()){
        qDebug() << "Datei ist leer";
        return false;
    }
     QDir saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    bool ret = false;
    QDir dir;
    dir.mkpath(saveDirectory.path());
    QFile tileImage(saveDirectory.filePath(createFileName(tile)));
    if(tileImage.open(QFile::WriteOnly |QFile::Truncate))
        if(tileImage.write(tile->imageData()) != -1)
            ret = true;
    return ret;
}

bool TileOfflineManager::deleteAll()
{
    QDir saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    int entries = saveDirectory.AllEntries;
    int counter = 0;
    foreach (QString file, saveDirectory.entryList()) {
        if(QFile::remove(saveDirectory.filePath(file))){
            counter++;
        }
    }
    qDebug() << QString::number(counter) + "/" +  QString::number(entries) <<  " were deleted!";
    return counter == entries;
}

bool TileOfflineManager::deleteTile(Tile * tile)
{
    QDir saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    bool ret = false;
    if(contains(tile, QStandardPaths::DataLocation)){
        ret = QFile::remove(saveDirectory.filePath(createFileName(tile)));
    }else{
        ret = true;
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
    if(contains(tile, QStandardPaths::DataLocation))
        return true;

    //Tile im Cache Verzeichnis
    bool ret = false;
    QDir saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QString tileName = createFileName(tile);

    if(contains(tile, QStandardPaths::CacheLocation)){
        QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        QDir cacheDirectory(searchSubdirectoriesForTile(tile, path));
        QFile cacheFile(cacheDirectory.filePath(tileName));
        ret = cacheFile.copy(saveDirectory.filePath(tileName));
        qDebug() << "Got tiles from Cache";

    }
    else if(contains(tile, QStandardPaths::GenericCacheLocation)){
        QDir generic(searchSubdirectoriesForTile(tile, QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation)));
        QFile cacheFile(generic.absolutePath().append("/" + tileName));
        ret = cacheFile.copy(saveDirectory.filePath(tileName));
        qDebug() << "Got tile from generic Cache";
    }
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

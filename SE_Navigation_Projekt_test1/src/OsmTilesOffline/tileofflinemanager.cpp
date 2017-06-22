#include "tileofflinemanager.h"
#include <QTime>

TileOfflineManager::TileOfflineManager(QObject *parent) : QObject(parent)
{
    m_currentlyUsedSpace = calculateUsedSpace("offline");
    m_settings = new QSettings();
    setOfflineMapSize(m_settings->value("maxOfflineMapSize").toInt());
    setOfflinePath(m_settings->value("offlineDirectory").toString());
}

TileOfflineManager::~TileOfflineManager()
{
    if(m_settings)
        delete m_settings;

}

bool TileOfflineManager::saveToFile(Tile *tile)
{
    qDebug() << "Write files to: " << offlinePath();
    bool ret = false;
    QStorageInfo info(m_offlinePath);
    //    qDebug() << "Bytes available: " << info.bytesAvailable();
    if(m_currentlyUsedSpace < m_offlineMapSize && info.bytesAvailable() - tile->imageData().size() > 0){
        if(tile->imageData().isEmpty()){
            qDebug() << "Datei ist leer";
            return false;
        }
        QDir saveDirectory = QDir(m_offlinePath);
        QDir dir;
        dir.mkpath(saveDirectory.path());
        QFile tileImage(saveDirectory.filePath(createFileName(tile)));
        if(tileImage.open(QFile::WriteOnly |QFile::Truncate)){
            if(tileImage.write(tile->imageData()) != -1){
                ret = true;
                m_currentlyUsedSpace += tileImage.size();
                //                qDebug() << "Saved file in: " << saveDirectory.absolutePath();
            }
        }
    }else{
        emit notEnoughSpace();
    }
    return ret;
}

bool TileOfflineManager::deleteAll()
{
    QDir saveDirectory = QDir(m_offlinePath);
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
    if(m_offlinePath.isEmpty()){
        QDir saveDirectory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        if(contains(tile, QStandardPaths::DataLocation)){
            ret = QFile::remove(saveDirectory.filePath(createFileName(tile)));
        }else{
            ret = true;
        }
    }else{
        QString directory = searchSubdirectoriesForTile(tile, m_offlinePath);
        if(!(directory != "")){
            ret = QFile::remove(directory + createFileName(tile) );
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
    //    QTime time;
    //    time.start();
    //Tile schon im Verzeichnis
    if(m_offlinePath != "" && QDir(m_offlinePath).entryList().contains(createFileName(tile))){
        return true;
    }
    if(contains(tile, QStandardPaths::DataLocation))
        return true;

    //    qDebug() << time.elapsed()/1000.0;
    //Tile im Cache Verzeichnis
    bool ret = false;
    QDir saveDirectory;
    saveDirectory = QDir(m_offlinePath);
    tile->setFormat("jpg");
    QString tileName = createFileName(tile);
    qDebug() << "Try to copy: " << tileName;
    if(contains(tile, QStandardPaths::CacheLocation)){
        QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        QString oldDir = searchSubdirectoriesForTile(tile, path);
        QDir cacheDirectory(oldDir);
        QFile cacheFile(cacheDirectory.filePath(tileName));
        tile->setFormat("png");
        tileName = createFileName(tile);
        ret = cacheFile.copy(saveDirectory.filePath(tileName));
        cacheFile.remove();
    }
    else if(contains(tile, QStandardPaths::GenericCacheLocation)){

        QString oldDir = searchSubdirectoriesForTile(tile, QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation));
        QDir generic(oldDir);
        QFile cacheFile(generic.absolutePath().append("/" + tileName));
        tile->setFormat("png");
        tileName = createFileName(tile);
        ret = cacheFile.copy(saveDirectory.filePath(tileName));
        cacheFile.remove();
        qDebug() << "Got tile from generic Cache";
    }
    //    qDebug() << "poit4 " << time.elapsed()/1000.0;
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

bool TileOfflineManager::changeOfflineDirectory(QString newDirectory)
{
    QStorageInfo infoNewDirectory(newDirectory);
    //    QStorageInfo infoOldDirectory(m_offlinePath);

    QDir dir(m_offlinePath);
    int copiedFiles = 0;
    int filesInOldDirectory = dir.entryList().size();
    QDir newDir(newDirectory);

    if(newDir.mkpath(newDirectory)){
        if(infoNewDirectory.bytesAvailable() >= m_currentlyUsedSpace){
            foreach (QString filename, dir.entryList()) {
                QFile offlineFile(dir.absoluteFilePath(filename));
                if(offlineFile.fileName().contains(".jpg") || offlineFile.fileName().contains(".png")){
                    if(offlineFile.copy(newDir.filePath(newDirectory))){
                        qDebug() << "Copy file from " << m_offlinePath << " to " << newDirectory;
                        copiedFiles++;
                    }
                }
            }
        }
    }

    return copiedFiles +2 == filesInOldDirectory;
}

int TileOfflineManager::calculateUsedSpace(QString directory)
{
    int size = 0;
    QDir dir;
    if(directory == "offline")
        dir = QDir(m_offlinePath);
    else if(directory == "cache")
        dir = QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));


    foreach (QString fileName, dir.entryList()) {
        QFile file(dir.absoluteFilePath(fileName));
        size += file.size();
    }
    return size;
}

int TileOfflineManager::offlineMapSize() const
{
    return m_offlineMapSize;
}

void TileOfflineManager::setOfflineMapSize(int offlineMapSize)
{
    m_offlineMapSize = offlineMapSize;
}

QString TileOfflineManager::offlinePath() const
{
    return m_offlinePath;
}

void TileOfflineManager::setOfflinePath(const QString &offlinePath)
{
    m_offlinePath = offlinePath;
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
    filename += tile->format();
    //    filename += m_format;
    return filename;
}

#include "tileofflinemanager.h"
#include <QTime>

TileOfflineManager::TileOfflineManager(QObject *parent) : QObject(parent)
{
    m_currentlyUsedSpace = calculateUsedSpace("offline");
    m_settings = new QSettings();
    setOfflineMapSize(m_settings->value("maxOfflineMapSize").toInt());
    setOfflinePath(m_settings->value("offlineDirectory").toString());
    findCacheDirectory();
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
    if(!m_offlinePath.isEmpty()){
        ret = QFile::remove(m_offlinePath + "/" + createFileName(tile) );
    }else{
        ret = true;
    }
    return ret;
}

bool TileOfflineManager::copyChacheTileIfPossible(Tile * tile)
{
    //Tile schon im Verzeichnis
    if(m_offlinePath != "" && QDir(m_offlinePath).entryList().contains(createFileName(tile))){
        qDebug() << "Tile already in offline diretory";
        return true;
    }
    bool ret = false;
    QDir saveDirectory;
    saveDirectory = QDir(m_offlinePath);
    tile->setFormat("jpg");
    QString tileName = createFileName(tile);
    qDebug() << "Try to copy: " << tileName;
    if(!m_cachedirectory.isEmpty()){
        QDir saveDirectory = QDir(m_offlinePath);
        QStringList filters;
        filters << "*.jpg" << "*.png";
        if(m_cachedirectory.entryList(filters).contains(createFileName(tile))){
            QFile cacheFile(m_cachedirectory.absoluteFilePath(tileName));
            tile->setFormat("png");
            qDebug() << createFileName(tile);
            qDebug() << saveDirectory.filePath(createFileName(tile));
            ret = cacheFile.copy(saveDirectory.filePath(createFileName(tile)));
            cacheFile.remove();
        }
        tile->setFormat("png");
    }else{
        findCacheDirectory();
    }
    return ret;
}


bool TileOfflineManager::changeOfflineDirectory(QString newDirectory)
{
    QStorageInfo infoNewDirectory(newDirectory);

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
    else if(directory == "cache"){
        if(!m_cachedirectory.exists()){
            dir = QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
        }else{
            dir = m_cachedirectory;
        }
    }

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

void TileOfflineManager::findCacheDirectory()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    QDirIterator it(directory,QDir::Dirs, QDirIterator::Subdirectories );
    while(it.hasNext()){
        QDir dir(it.next());
        foreach (QString fileName, dir.entryList()) {
            QRegExp rx("osm_100\\-l\\-\\d{1,1}\\-\\d{1,2}\\-\\d+\\-\\d+\\.png");
            if(rx.exactMatch(fileName)){
                m_cachedirectory = QDir(fileName);
                return;
            }
        }
    }
    directory = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);
    QDirIterator it2(directory,QDir::Dirs, QDirIterator::Subdirectories );
    while(it2.hasNext()){
        QDir dir(it2.next());
        foreach (QString fileName, dir.entryList()) {
            QRegExp rx("osm_100-l-\\d{1,1}-\\d{1,2}-\\d+-\\d+\\.jpg");
            if(rx.exactMatch(fileName)){
                m_cachedirectory = dir;
                return;
            }
        }
    }
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
    return filename;
}

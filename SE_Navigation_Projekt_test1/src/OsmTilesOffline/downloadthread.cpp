#include "downloadthread.h"

DownloadThread::DownloadThread(QObject* parent) : QThread(parent)
{

}

void DownloadThread::run()
{
    TilesDownloader downloader;
    m_mutex.lock();
    QVariant center = m_center;
    QString provider = m_provider;
    QPoint windowSize = m_windowSize;
    int zoomLevel = m_zoomLevel;
    int depth = m_depth;
    connect(&downloader, SIGNAL(nextTileDownloadStarted(int,int)), this, SIGNAL(updateProgressBar(int,int)));
    connect(&downloader, SIGNAL(downloadFinished()), this, SIGNAL(downloadFinished()));
    QEventLoop loop;
    connect(&downloader, SIGNAL(downloadFinished()), &loop, SLOT(quit()));
    m_mutex.unlock();
    downloader.downloadTiles(center, provider, zoomLevel, depth, windowSize);
    loop.exec();
}

void DownloadThread::startDownload(QVariant center, QString provider, int zoomLevel, int depth, int width, int height)
{
    m_center = center;
    m_provider = provider;
    m_windowSize = QPoint(width, height);
    m_zoomLevel = zoomLevel;
    m_depth = depth;
    this->setPriority(QThread::HighPriority);
    this->start();
}

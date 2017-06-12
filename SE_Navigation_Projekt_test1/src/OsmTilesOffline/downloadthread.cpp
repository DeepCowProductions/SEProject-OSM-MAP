#include "downloadthread.h"

DownloadThread::DownloadThread(QObject* parent) : QThread(parent)
{

}

void DownloadThread::run()
{
    TilesDownloader downloader;

    QVariant center = m_center;
    QString provider = m_provider;
    QPoint windowSize = m_windowSize;
    int zoomLevel = m_zoomLevel;
    int depth = m_depth;
    QEventLoop loop;
    connect(&downloader, SIGNAL(downloadFinished()), this, SIGNAL(downloadFinished()));
    connect(&downloader, SIGNAL(downloadFinished()), &loop, SLOT(quit()));
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
    this->start();
}

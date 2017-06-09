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
    downloader.downloadTiles(center, provider, zoomLevel, depth, windowSize);
    connect(&downloader, SIGNAL(downloadFinished()), &loop, SLOT(quit()));
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

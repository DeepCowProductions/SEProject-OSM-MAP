#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include "tilesdownloader.h"

class DownloadThread : public QThread
{
    Q_OBJECT
public:
    DownloadThread(QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;

signals:

    void updateProgressBar(int current, int amount);

    void downloadFinished();

    void downloadFailed();


public slots:

    void startDownload(QVariant center, QString provider, int zoomLevel, int depth, int width, int height);


private:
    QMutex m_mutex;
    QVariant m_center;
    QString m_provider;
    QPoint m_windowSize;
    int m_zoomLevel;
    int m_depth;
};

#endif // DOWNLOADTHREAD_H

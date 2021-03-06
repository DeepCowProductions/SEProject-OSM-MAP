#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/settings.h"
#include "src/placesmodel.h"
#include "src/routesmodel.h"
#include "src/locationpin.h"
#include <QImage>
#include <QGeoCoordinate>
#include <QScreen>
#include "src/OsmTilesOffline/tilesdownloader.h"
#include "src/OsmTilesOffline/downloadthread.h"
#include "src/OsmTilesOffline/tileofflinemanager.h"
#include <stdexcept>
#include <QFile>

int main(int argc, char *argv[])
{
    // app eingenschaften
    QCoreApplication::setOrganizationName("FH-SWF");
    QCoreApplication::setOrganizationDomain("fh-swf.de");
    QCoreApplication::setApplicationName("SE-Projekt-Mobile-Navigation");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // eingene klassen in QML registieren:
    qmlRegisterType<Settings>("fhswf.se.nav.settings", 1, 0, "Settings");
    qmlRegisterType<PlacesModel>("fhswf.se.nav.models", 1, 0, "PlacesModel");
    qmlRegisterType<RoutesModel>("fhswf.se.nav.models", 1, 0, "RoutesModel");
    qmlRegisterType<LocationPin>("fhswf.se.nav.models", 1, 0, "LocationPin");
    qmlRegisterType<TileOfflineManager>("fhswf.se.nav.offlinemanager", 1, 0, "TileManager");

    // init engine und laden von qml
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));
    QObject *item = engine.rootObjects().first();
    Q_ASSERT(item);
    for(int i = 0; i < app.screens().size(); i++){
        QScreen* screen = app.screens().at(i);
        qDebug() << screen->name();
    }

    // einrichten des downloadthreads
    DownloadThread * thread = new DownloadThread(item);
    QObject::connect(item, SIGNAL(saveTiles(QVariant, QString, int, int, int, int)), thread, SLOT(startDownload(QVariant, QString, int, int, int, int)));

    QObject::connect(thread, SIGNAL(downloadFinished()), item, SIGNAL(downloadFinished()));
    QObject::connect(thread, SIGNAL(updateProgressBar(int,int)), item, SIGNAL(updateProgressBar(int, int )));

    QMetaObject::invokeMethod(item, "initApp"
                              //                             , Q_ARG(QVariant, QVariant::fromValue(1))
                              );
    // start des eventloops
    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/settings.h"
#include "src/placesmodel.h"
#include "src/roadsmodel.h"
#include <QImage>
#include <QGeoCoordinate>
#include "src/tilesdownloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("FH-SWF");
    QCoreApplication::setOrganizationDomain("fh-swf.de");
    QCoreApplication::setApplicationName("SE-Projekt-Mobile-Navigation");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Settings>("fhswf.se.nav.settings", 1, 0, "Settings");
    qmlRegisterType<PlacesModel>("fhswf.se.nav.models", 1, 0, "PlacesModel");
    qmlRegisterType<RoadsModel>("fhswf.se.nav.models", 1, 0, "RoadsModel");


    TilesDownloader downloader;
    //    saveTiles


    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));
    QObject *item = engine.rootObjects().first();
    Q_ASSERT(item);

    QObject::connect(item, SIGNAL(saveTiles(QVariant, int)), &downloader, SLOT(downloadTiles(QVariant, int)));

    QMetaObject::invokeMethod(item, "initApp",
                              Q_ARG(QVariant, QVariant::fromValue(1)));
    return app.exec();
}

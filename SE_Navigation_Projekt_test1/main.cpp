#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/settings.h"
#include "src/placesmodel.h"
#include "src/roadsmodel.h"
#include <QImage>
#include <QGeoCoordinate>
#include <QScreen>
#include "src/OsmTilesOffline/tilesdownloader.h"

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


    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));
    QObject *item = engine.rootObjects().first();
    Q_ASSERT(item);
    for(int i = 0; i < app.screens().size(); i++){
        QScreen* screen = app.screens().at(i);
        qDebug() << screen->name();
    }
    QPoint screenSize(item->property("width").toInt(), item->property("height").toInt());
    qDebug() << screenSize.x() << " " << screenSize.y();
    TilesDownloader * downloader = new TilesDownloader(item, screenSize);

    QObject::connect(downloader, SIGNAL(downloadFinished()), item, SIGNAL(enableButton()));

    QObject::connect(item, SIGNAL(saveTiles(QVariant,QString, int)), downloader, SLOT(downloadTiles(QVariant,QString, int)));
    QMetaObject::invokeMethod(item, "initApp"
//                             , Q_ARG(QVariant, QVariant::fromValue(1))
                              );
    return app.exec();
}

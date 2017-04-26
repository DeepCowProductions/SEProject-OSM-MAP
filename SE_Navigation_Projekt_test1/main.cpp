#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/settings.h"
#include "src/placesmodel.h"
#include <QImage>
int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("FH-SWF");
    QCoreApplication::setOrganizationDomain("fh-swf.de");
    QCoreApplication::setApplicationName("SE-Projekt-Mobile-Navigation");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Settings>("fhswf.se.tools.settings", 1, 0, "Settings");
    qmlRegisterType<PlacesModel>("fhswf.se.tools.settings", 1, 0, "PlacesModel");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));

    QObject *item = engine.rootObjects().first();
    Q_ASSERT(item);
    QMetaObject::invokeMethod(item, "initApp",
                              Q_ARG(QVariant, QVariant::fromValue(1)));
    return app.exec();
}

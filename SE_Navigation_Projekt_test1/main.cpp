#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "settings.h"
#include <QImage>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Settings>("fhswf.se.tools.settings", 1, 0, "Settings");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

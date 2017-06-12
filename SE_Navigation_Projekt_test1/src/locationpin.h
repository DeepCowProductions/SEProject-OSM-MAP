#ifndef LOCATIONPIN_H
#define LOCATIONPIN_H

#include <QObject>
#include <QDate>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <QStandardPaths>

#define saveFileNamePinned "pinned.json"

class LocationPin : public QObject, public QGeoLocation
{
    Q_OBJECT
public:
    explicit LocationPin(QObject *parent = 0);
    ~LocationPin();

    void readFromJason(QJsonObject &object);
    QJsonObject writeToJason();

signals:

public slots:
    Q_INVOKABLE QGeoCoordinate coordinateEx();
    Q_INVOKABLE void setCoordinateEx(const QGeoCoordinate &coordinate);
    Q_INVOKABLE bool readUserData();
    Q_INVOKABLE bool writeUserData();

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE QDate savedAtDate() const;

    Q_INVOKABLE void setSavedAtDate(QDate savedAtDate);
private:
    QString m_name = "Pinned Location";
    QDate m_savedAtDate;
};

#endif // LOCATIONPIN_H

#ifndef ROAD_H
#define ROAD_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>

class Road
{

public:
    Road();

    QList<QGeoCoordinate> coordinates() const;
    void setCoordinates(const QList<QGeoCoordinate> &coordinates);

    void addCoordinate(const QGeoCoordinate coord);
    void clearCoordinateList();
    void removeCoordinate(QGeoCoordinate coord);

    QString name() const;
    void setName(const QString &name);

    QDate savedAtDate() const;
    void setSavedAtDate(const QDate &savedAtDate);

    void readFromJason(QJsonObject &object);
    QJsonObject writeToJason();

private:
    QList<QGeoCoordinate> m_coordinates;

    QString m_name;
    QDate m_savedAtDate;
};

#endif // ROAD_H

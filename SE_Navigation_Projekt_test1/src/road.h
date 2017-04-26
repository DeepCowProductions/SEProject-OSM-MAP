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

    QString name() const;
    QDate savedAtDate() const;

    void setName(QString name);
    void setSavedAtDate(QDate savedAtDate);

private:
    QList<QGeoCoordinate> m_coordinates;

    QString m_name;
    QDate m_savedAtDate;
};

#endif // ROAD_H

#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include "place.h"
#include "road.h"

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = 0);

    QList<Place> places() const;
    void setPlaces(const QList<Place> &places);

    QList<Road> roads() const;
    void setRoads(const QList<Road> &roads);

    void addPlace(const Place &place);
    void addRoad(const Road &road);

signals:

public slots:

private:
    QList<Place> m_places;
    QList<Road> m_roads;

};

#endif // USERDATA_H

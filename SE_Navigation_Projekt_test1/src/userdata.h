#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include "place.h"
#include "route.h"

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = 0);

    QList<Place> places() const;
    void setPlaces(const QList<Place> &places);

    QList<Route> roads() const;
    void setRoads(const QList<Route> &roads);

    void addPlace(const Place &place);
    void addRoad(const Route &road);

signals:

public slots:

private:
    QList<Place> m_places;
    QList<Route> m_roads;

};

#endif // USERDATA_H

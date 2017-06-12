#include "userdata.h"

UserData::UserData(QObject *parent) : QObject(parent)
{

}

QList<Place> UserData::places() const
{
    return m_places;
}

void UserData::setPlaces(const QList<Place> &places)
{
    m_places = places;
}

QList<Route> UserData::roads() const
{
    return m_roads;
}

void UserData::setRoads(const QList<Route> &roads)
{
    m_roads = roads;
}

void UserData::addPlace(const Place &place)
{
    m_places.append(place);
}

void UserData::addRoad(const Route &road)
{
    m_roads.append(road);
}

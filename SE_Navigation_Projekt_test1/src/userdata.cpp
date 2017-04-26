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

QList<Road> UserData::roads() const
{
    return m_roads;
}

void UserData::setRoads(const QList<Road> &roads)
{
    m_roads = roads;
}

void UserData::addPlace(const Place &place)
{
    m_places.append(place);
}

void UserData::addRoad(const Road &road)
{
    m_roads.append(road);
}

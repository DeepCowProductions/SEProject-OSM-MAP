#include "route.h"

Route::Route()
{

}

QList<QGeoCoordinate> Route::coordinates() const
{
    return m_coordinates;
}

void Route::setCoordinates(const QList<QGeoCoordinate> &coordinates)
{
    m_coordinates = coordinates;
}

void Route::addCoordinate(const QGeoCoordinate coord)
{
    m_coordinates.append((coord));
}

void Route::clearCoordinateList()
{
    m_coordinates.clear();
}

void Route::removeCoordinate(QGeoCoordinate coord)
{
    m_coordinates.removeOne(coord);
}

QString Route::name() const
{
    return m_name;
}

void Route::setName(const QString &name)
{
    m_name = name;
}

QDate Route::savedAtDate() const
{
    return m_savedAtDate;
}

void Route::setSavedAtDate(const QDate &savedAtDate)
{
    m_savedAtDate = savedAtDate;
}

void Route::readFromJason(QJsonObject &object)
{
    if (!object["name"].isUndefined())
        m_name = object["name"].toString();
    else
        m_name = "name missing";
    if (!object["savedAtDate"].isUndefined())
        m_savedAtDate = QDate::fromString(object["savedAtDate"].toString());
    else
        m_savedAtDate = QDate::currentDate();

    QJsonArray ca;
    ca = object["coordinates"].toArray();
    for(int i=0; i < ca.size(); i++) {
        QGeoCoordinate r;
        QJsonObject ro = ca[i].toObject();

        if ((!ro["latitude"].isUndefined()) && (!ro["longitude"].isUndefined())){
            if (!ro["altitude"].isUndefined()){
                r =  QGeoCoordinate( ro["latitude"].toDouble(), ro["longitude"].toDouble() , ro["altitude"].isDouble() );
            } else {
                r =  QGeoCoordinate( ro["latitude"].toDouble(), ro["longitude"].toDouble() ) ;
            }
        } else {
            r = QGeoCoordinate( 0.0, 0.0 );
        }

        m_coordinates.append(r);
    }
}

QJsonObject Route::writeToJason()
{
    QJsonObject object;

    object["name"] = m_name;
    object["savedAtDate"] = m_savedAtDate.toString();

    QJsonArray ra;
    for (int i=0; i < m_coordinates.size(); i++) {
        QJsonObject ro;
        if (m_coordinates[i].isValid()) {
            ro["latitude"] = m_coordinates[i].latitude();
            ro["longitude"] = m_coordinates[i].longitude();
            if (m_coordinates[i].type() == QGeoCoordinate::Coordinate3D)
                ro["altitude"] = m_coordinates[i].altitude();
        } else {
            ro["latitude"] = "0.0";
            ro["longitude"] = "0.0";
        }
        ra.append(ro);
    }
    object["coordinates"] = ra;

    return object;
}

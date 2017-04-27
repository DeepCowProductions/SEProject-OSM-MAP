#include "place.h"

Place::Place() : QGeoLocation()
{

}

QString Place::name() const
{
    return m_name;
}

QDate Place::savedAtDate() const
{
    return m_savedAtDate;
}

void Place::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
}

void Place::setSavedAtDate(QDate savedAtDate)
{
    if (m_savedAtDate == savedAtDate)
        return;

    m_savedAtDate = savedAtDate;
}

void Place::readFromJason(QJsonObject &object)
{
    if (!object["name"].isUndefined())
        m_name = object["name"].toString();
    else
        m_name = "name missing";
    if (!object["savedAtDate"].isUndefined())
        m_savedAtDate = QDate::fromString(object["savedAtDate"].toString());
    else
        m_savedAtDate = QDate::currentDate();
    if (!object["coordinate"].isUndefined()){
        QJsonObject cj =  object["coordinate"].toObject();
        if ((!cj["latitude"].isUndefined()) && (!cj["longitude"].isUndefined())){
            if (!cj["altitude"].isUndefined()){
                setCoordinate( QGeoCoordinate( cj["latitude"].toDouble(), cj["longitude"].toDouble() , cj["altitude"].isDouble() ) );
            } else {
                setCoordinate( QGeoCoordinate( cj["latitude"].toDouble(), cj["longitude"].toDouble() ) );
            }
        } else {
            setCoordinate( QGeoCoordinate( 0.0, 0.0 ) );
        }
    }
    if (!object["address"].isUndefined()) {
        QJsonObject aj = object["address"].toObject();
        QGeoAddress a;
        if (!aj["city"].isUndefined())
            a.setCity(aj["city"].toString());
        if (!aj["country"].isUndefined())
            a.setCountry(aj["country"].toString());
        if (!aj["countryCode"].isUndefined())
            a.setCountryCode(aj["countryCode"].toString());
        if (!aj["county"].isUndefined())
            a.setCounty(aj["county"].toString());
        if (!aj["district"].isUndefined())
            a.setDistrict(aj["district"].toString());
        if (!aj["postalCode"].isUndefined())
            a.setPostalCode(aj["postalCode"].toString());
        if (!aj["state"].isUndefined())
            a.setState(aj["state"].toString());
        if (!aj["street"].isUndefined())
            a.setStreet(aj["street"].toString());
        if (!aj["text"].isUndefined())
            a.setText(aj["text"].toString());
        setAddress(a);
    }
    // boundingBox unused...
    //    if (!object["boundingBox"].isUndefined()) {
    //    QJsonObject bj = object["boundingBox"].toObject();
    //        bj["topLeft"].toObject(); // both are GeoCoords.
    //        bj["bottomRight"].toObject();
    //        [...]
    //    }
}

QJsonObject Place::writeToJason()
{
    QJsonObject object;

    object["name"] = m_name;
    object["savedAtDate"] = m_savedAtDate.toString();

    QJsonObject cj;
    if (coordinate().isValid()) {
        cj["latitude"] = coordinate().latitude();
        cj["longitude"] = coordinate().longitude();
        if (coordinate().type() == QGeoCoordinate::Coordinate3D)
            cj["altitude"] = coordinate().altitude();
    } else {
        cj["latitude"] = "0.0";
        cj["longitude"] = "0.0";
    }
    object["coordinate"] = cj;

    if (!address().isEmpty()) {
        QJsonObject aj;
        if (!address().city().isNull() &&!address().city().isEmpty())
            aj["city"]          = address().city();
        if (!address().country().isNull() &&!address().country().isEmpty())
            aj["country"]       = address().country();
        if (!address().countryCode().isNull() &&!address().city().isEmpty())
            aj["countryCode"]   = address().countryCode();
        if (!address().county().isNull() &&!address().county().isEmpty())
            aj["county"]        = address().county();
        if (!address().district().isNull() &&!address().district().isEmpty())
            aj["district"]      = address().district();
        if (!address().postalCode().isNull() &&!address().postalCode().isEmpty())
            aj["postalCode"]    = address().postalCode();
        if (!address().state().isNull() &&!address().state().isEmpty())
            aj["state"]         = address().state();
        if (!address().street().isNull() &&!address().street().isEmpty())
            aj["street"]        = address().street();
        if (!address().text().isNull() &&!address().text().isEmpty())
            aj["text"]          = address().text();
        object["address"] = aj;
    }

    // boundingBox unused...
    // [...]
    return object;
}


#ifndef PLACE_H
#define PLACE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QDate>

class Place : public QGeoLocation
{
public:
    Place();

    QString name() const;
    QDate savedAtDate() const;

    void setName(QString name);
    void setSavedAtDate(QDate savedAtDate);

    void readFromJason(QJsonObject &object);
    QJsonObject writeToJason();
private:
    QString m_name;
    QDate m_savedAtDate;
};

#endif // PLACE_H

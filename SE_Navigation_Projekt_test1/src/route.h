#ifndef ROAD_H
#define ROAD_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>

class Route
{

public:
    Route();

    QList<QGeoCoordinate> coordinates() const;
    void setCoordinates(const QList<QGeoCoordinate> &coordinates);

    void addCoordinate(const QGeoCoordinate coord);
    void clearCoordinateList();
    void removeCoordinate(QGeoCoordinate coord);

    QString name() const;
    void setName(const QString &name);

    QDate savedAtDate() const;
    void setSavedAtDate(const QDate &savedAtDate);

    /**
     * @brief readFromJason
     * Liest ein QJsonObject und extrahiert alle Informationen um die Propeties dieser Klasse zu füllen.
     *
     * @param object QJsonObject welches die gewünschten Informationen enthält.
     */
    void readFromJason(QJsonObject &object);
    /**
     * Schreibt ein QJsonObject mit den Informationen dieser Klasse.
     *
     * @return Ein fertiges QJsonObject mit den erwünschten Informationen.
     */
    QJsonObject writeToJason();

private:
    QList<QGeoCoordinate> m_coordinates;

    QString m_name;
    QDate m_savedAtDate;
};

#endif // ROAD_H

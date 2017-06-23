#ifndef ROAD_H
#define ROAD_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>

/**
 * @brief The Route class
 * Diese Klasse stellt eine Entität bzw Datensatz in der RoutesModel Klasse dar.
 * Sie Speichert name, datum und eine Liste aus geoLocations (Latitude+Longitude) ab, welche zusammen einen gespeicherten Route darstellen.
 * Sie besitzt zwei Funktionen readFromJason(...) und writeToJason() um eine Instanz diese Objektes in ein QJsonObject zu konverrtieren.
 */
class Route
{

public:
    Route();

    /**
     * @brief coordinates
     * getter für den pfad der route/ koordinatenliste.
     * @return QList mit QGeoCoordinate
     */
    QList<QGeoCoordinate> coordinates() const;
    /**
     * @brief setCoordinates
     * ersetzt das komplette array.
     * @param coordinates das neue koordinaten array
     */
    void setCoordinates(const QList<QGeoCoordinate> &coordinates);

    /**
     * @brief addCoordinate
     * fügt eine koordinate dem array hinzu
     * @param coord die hinzuzufügende koordinate
     */
    void addCoordinate(const QGeoCoordinate coord);
    /**
     * @brief clearCoordinateList
     * entfernt alle koordinaten aus dem koordinaten array.
     */
    void clearCoordinateList();
    /**
     * @brief removeCoordinate
     * löscht eine koordinate aus dem array
     * @param coord die zu löschende koordinate
     */
    void removeCoordinate(QGeoCoordinate coord);

    // simple getter
    QString name() const;
    // simple setter
    void setName(const QString &name);

    // simple getter
    QDate savedAtDate() const;
    // simple setter
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
    /**
     * @brief m_coordinates pfad = liste aus qgeocoordinate's
     */
    QList<QGeoCoordinate> m_coordinates;

    /**
     * @brief m_name name der route
     */
    QString m_name;
    /**
     * @brief m_savedAtDate speicher datum
     */
    QDate m_savedAtDate;
};

#endif // ROAD_H

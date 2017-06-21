#ifndef PLACE_H
#define PLACE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QDate>

/**
 * @brief The Place class
 * Diese Klasse stellt eine Entität bzw Datensatz in der PlacesModel Klasse dar.
 * Sie Speichert ähnlich der LocationPin Klasse name, datum und geoLocation ab, welche zusammen einen gespeicherten Standort darstellen.
 * Sie besitzt zwei Funktionen readFromJason(...) und writeToJason() um eine Instanz diese Objektes in ein QJsonObject zu konverrtieren.
 */
class Place : public QGeoLocation
{
public:
    /**
     * @brief Place Konstruktor, unused.
     */
    Place();

    // simple getter
    QString name() const;
    // simple getter
    QDate savedAtDate() const;

    // simple setter
    void setName(QString name);
    // simple setter
    void setSavedAtDate(QDate savedAtDate);

    /**
     * @brief readFromJason
     * Liest ein QJsonObject und extrahiert alle Informationen um die Propeties dieser Klasse zu füllen.
     * Latitude, Logitude, Altitude für QGeoLocation coordinate, geerbt von QGeoLocation.
     * name und savedAtDAte für die Member in dieser Klasse.
     * @param object QJsonObject welches die gewünschten Informationen enthält.
     */
    void readFromJason(QJsonObject &object);
    /**
     * Schreibt ein QJsonObject mit den Informationen dieser Klasse.
     * Latitude, Logitude, Altitude für QGeoLocation coordinate, geerbt von QGeoLocation.
     * name und savedAtDAte, Member in dieser Klasse.
     * @return Ein fertiges QJsonObject mit den erwünschten Informationen.
     */
    QJsonObject writeToJason();
private:
    // member name
    QString m_name;
    // member savedAtDate
    QDate m_savedAtDate;
};

#endif // PLACE_H

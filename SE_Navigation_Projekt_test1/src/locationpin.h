#ifndef LOCATIONPIN_H
#define LOCATIONPIN_H

#include <QObject>
#include <QDate>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <QStandardPaths>

#define saveFileNamePinned "pinned.json"

/**
 * @brief The LocationPin class
 * Diese Klasse wird zusmmen mit den ModelKlassen (PacesModel and RoutesModel) verwendet um die Nutzerdaten zu speichern.
 *
 * Sie ist kein QtModel Klasse da sie nicht von QAbstractItemModel erbt, kann aller dings trotzdem als Model betrachtet werden.
 * Sie besitzt eigentlich nur eine Property geerbt von QAbstractItemModel (vom typ QGeoCoordinate).
 * Sie kann angesteuert werden mit:
 *
 * coordinateEx() and setCoordinateEx(...)
 *
 * Sobalt diese gesetzt wurde, wird der entsprechende Wert in einer Json Datei zusammen mit einem Namen und dem Speicherdatum persitiert.
 * Diese klass erbt von QObject damit sie in der qml Oberfläche als Object registriert und verwendet werden kann.
 *
 * Funktionen die mit Q_INVOKABLE markiert sind, können in der qml augerufen werden.
 */
class LocationPin : public QObject, public QGeoLocation
{
    Q_OBJECT
public:
    /**
     * @brief LocationPin
     * KOnstruktor für diese Klasse. Ruft readUserDate() auf.
     * @param parent parent QObject.
     */
    explicit LocationPin(QObject *parent = 0);
    /**
     * @brief ~LocationPin desruktor für diese Klasse. Ruft writeUserDate() auf.
     */
    ~LocationPin();

signals:

public slots:
    /**
      * @brief coordinateEx
      * getter für die Koordinaten Informationen aus QGeoLocation.
      * Notwendig da der normale Getter nicht in qml zur verfügung steht.
      * @return ein QGeoCoordinate Objekt erhalten von QGeoCoordinate::coordinate() aus der Elternklasse.
      */
    Q_INVOKABLE QGeoCoordinate coordinateEx();
    /**
      * @brief setCoordinateEx
      * setter für die Koordinaten Informationen aus QGeoLocation.
      * Ruft QGeoCoordinate::setCoordinate() aus der Elternklasse auf.
      * Notwendig da dieser Setter nicht in qml zur verfügung steht.
      * @param coordinate ein QGeoCoordinate Objekt mit Koordinaten Informationen.
      */
    Q_INVOKABLE void setCoordinateEx(const QGeoCoordinate &coordinate);
    /**
      * @brief readUserData
      * Liest die Nutzerdaten aus der pinned.json Datei auf dem Storage und speichert diese in ein QJsonObject,
      *  welches dann von readFromJason() ausgewertet wird.
      * Pfad zur Datei ist QStandartPath::writableLocation.
      * @return true bei Erfolg.
      */
    Q_INVOKABLE bool readUserData();
    /**
      * @brief writeUserData
      * Schreibt die Nutzerdaten in die pinned.json Datei auf dem Storage von einem QJsonObject
      *  welches von writeToJason() erstellt wird.
      * Pfad zur Datei ist QStandartPath::writableLocation.
      * @return true bei Erfolg.
      */
    Q_INVOKABLE bool writeUserData();

    // simple getter, no setter for this property on purpose
    Q_INVOKABLE QString name() const;
    // simple getter
    Q_INVOKABLE QDate savedAtDate() const;
    // simple setter
    Q_INVOKABLE void setSavedAtDate(QDate savedAtDate);

protected:
    /**
     * @brief readFromJason
     * Liest ein QJsonObject und extrahiert alle Informationen um die Propeties dieser Klasse zu füllen.
     * Latitude, Logitude, Altitude für QGeoLocation coordinate, geerbt von QGeoLocation.
     * name und savedAtDAte für die Member in dieser Klasse.
     * @param object QJsonObject welches die gewünschten Informationen enthält.
     */
    void readFromJason(QJsonObject &object);
    /**
     * @brief writeToJason
     * Schreibt ein QJsonObject mit den Informationen dieser Klasse.
     * Latitude, Logitude, Altitude für QGeoLocation coordinate, geerbt von QGeoLocation.
     * name und savedAtDAte, Member in dieser Klasse.
     * @return Ein fertiges QJsonObject mit den erwünschten Informationen.
     */
    QJsonObject writeToJason();

private:
    // member für name property.
    QString m_name = "Pinned Location";
    // member für saveAtDate property.
    QDate m_savedAtDate;
};

#endif // LOCATIONPIN_H

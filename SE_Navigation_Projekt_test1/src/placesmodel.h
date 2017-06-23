#ifndef PLACESMODEL_H
#define PLACESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QFile>
#include "place.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QDate>

#define saveFileNamePlaces "places.json"

/**
 * @brief The PlacesModel class
 * Diese Klasse ist eine der zwei zentralen Model Klassen in in der qml Oberfläche verwendet werden,
 * um Nutzerdaten zu speichern und anzuzeigen. Die Klasse erbt dafür von QAbstractListModel.
 * Die Klasse verwaltet dazu ein Array aus Place Objekten (m_places) und speichert somit die vom Nutzer gespeicherten Standorte.
 *
 * Die Funktionen :
 * @code
 *      QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
 *      int rowCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
 *      int columnCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
 *      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
 *      bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
 * @endcode
 * der Basisklasse müssen dabei überschrieben werden um die Daten aus dem Array an ein ListView Item in der qml weiter zu reichen.
 *
 * @code
 *      bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
 * @endcode
 * dient zum ändern der Daten in dem Array.
 *
 * Zur einfacheren Handhabung der Properties dient die enum PlaceRoles,
 * wechle Rollen bereitstellt die die Properties der Datenobjekte representieren.
 * Diese werden dann zum  Beispiiel von der data() funktion verwendet um auf die daten im array zuzugreifen.
 *
 * Zusätzlich besitzt diese Klasse Funktionen um die gesamten Daten im Array m_places als Json Datei zu persitieren.
 * @code
 *      bool readUserDataFromJson (QJsonObject &object);
 *      bool writeUserDataToJson (QJsonObject &object);
 * @endcode
 * dienen dazu das Array in ein QJsonObjekt zu konvertieren und
 * @code
 *      Q_INVOKABLE bool readUserData();
 *      Q_INVOKABLE bool writeUserData();
 * @endcode
 * dienen zum Speichern in der Json Datei "places.json".
 */
class PlacesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
     * @brief The PlaceRoles enum
     * Rollen wechle die properties der Daten in dem Array representieren.
     */
    enum PlaceRoles {
        NameRole = Qt::UserRole + 1,
        //        CoordinateRole,
        LatitudeRole,
        LongitudeRole,
        SavedAtDateRole,
        //        AddressRole,
        //        BoundingBoxRole
    };
    /**
     * @brief PlacesModel
     * Konstruktor, ruft readUserData() auf.
     * @param parent
     */
    explicit PlacesModel(QObject *parent = 0);

    /**
     * @brief roleNames
     * Gibt die enum PlacesRoles an die ListView weiter.
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel
     * @return ein Hash der Rollen namen
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /**
     * @brief rowCount
     * Gibt die Anzahl der zu erwarteten Listeneinträge aus.
     * Hier ist das gleich der Größe des internen Array (m_places.size()).
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel.
     * @param parent = QModelIndex()
     * @return Anzahl
     */
    int rowCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * @brief columnCount
     * Gibt die Anzahl der Splaten der Liste zurück. Diese ist gleich der Anzahl der Rollen.
     * Hier 4.
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel
     * @param parent = QModelIndex()
     * @return Anzahl
     */
    int columnCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * @brief data
     * Hauptfunktion um die Daten des Arrays an die ListView weiter zu reichen.
     * Sie wird für jede Zelle der Tabelle einmal mit index und rolle aufgerufen.
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel
     * @param index index des ModelItems
     * @param role Rolle des Wertes
     * @return den wert der Rolle des Items mit entsprechendem Index als QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * @brief setData
     * Konvention für die Verwendung von ändern der Datensätzte im Model.
     * Ähnlicher Aufbau zu data(...).
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel
     * @param index index des ModelItems
     * @param value neuer wert der Rolle
     * @param role Rolle
     * @return true beu Erfolg
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

signals:

public slots:
    /**
      * @brief clearList
      * entfernt alle items aus dem Datenarray
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool clearList();
    /**
      * @brief readUserData
      * liest die gespeicherten nutzerdaten aus des datei saveFileNamePlaces
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool readUserData();
    /**
      * @brief writeUserData
      * schreibt die daten aus dem array in die datei saveFileNamePlaces
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool writeUserData();
    /**
      * @brief addItem
      * fügt ein item dem array hinzu. datum wird automatisch gesetzt.
      * @param name name des ortes
      * @param coord geolocation des ortes
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool addItem(QString name, QGeoCoordinate coord);
    /**
      * @brief deleteItem
      * entfernt das item mit index index an dieser stelle aus dem array.
      * @param index index des items.
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool deleteItem(const int &index);
    /**
      * @brief changeItemName
      * ändert den namen des items an der stelle i im array.
      * sendet dataCHanged signal
      * @param i index des items
      * @param value neuer name
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool changeItemName(const int &i, const QVariant &value);
    /**
      * @brief getName
      * gibt den namen des items im array an der stelle index zurück.
      * @param index index des items.
      * @return name des items.
      */
    Q_INVOKABLE QString getName(int index);
    /**
      * @brief getLatiAtIndex
      * gibt latitude des ortes des items im array an der stelle index zurück.
      * @param index index des items
      * @return latitude als winkel in grad
      */
    Q_INVOKABLE double getLatiAtIndex(int index);
    /**
      * @brief getLongiAtIndex
      * gibt longitude des ortes des items im array an der stelle index zurück.
      * @param index index des items
      * @return longitude als winkel in grad
      */
    Q_INVOKABLE double getLongiAtIndex(int index);

protected:

    /**
     * @brief readUserDataFromJson
     * Liest Daten aus einem QJsonObject in das Klassen eigene Array ein.
     * @param object
     * @return
     */
    bool readUserDataFromJson (QJsonObject &object);
    /**
     * @brief writeUserDataToJson
     * Schreibt Daten aus dem array in das QJsonObject.
     * @param object
     * @return
     */
    bool writeUserDataToJson (QJsonObject &object);

private:
    /**
     * @brief m_places array with model data
     */
    QVector<Place> m_places;
};

#endif // PLACESMODEL_H

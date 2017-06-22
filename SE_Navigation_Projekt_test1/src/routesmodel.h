#ifndef ROADSMODEL_H
#define ROADSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QFile>
#include "route.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QDate>
#include <QVariant>
#include <QJSEngine>

#define saveFileNameRoads "roads.json"

/**
 * @brief The RoutesModel class
 * Diese Klasse ist eine der zwei zentralen Model Klassen in in der qml Oberfläche verwendet werden,
 * um Nutzerdaten zu speichern und anzuzeigen. Die Klasse erbt dafür von QAbstractListModel.
 * Die Klasse verwaltet dazu ein Array aus Route Objekten (m_routes) und speichert somit die vom Nutzer gespeicherten Routen.
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
 * Zur einfacheren Handhabung der Properties dient die enum RouteRoles,
 * wechle Rollen bereitstellt die die Properties der Datenobjekte representieren.
 * Diese werden dann zum  Beispiiel von der data() funktion verwendet um auf die daten im array zuzugreifen.
 *
 * Zusätzlich besitzt diese Klasse Funktionen um die gesamten Daten im Array m_routes als Json Datei zu persitieren.
 * @code
 *      bool readUserDataFromJson (QJsonObject &object);
 *      bool writeUserDataToJson (QJsonObject &object);
 * @endcode
 * dienen dazu das Array in ein QJsonObjekt zu konvertieren und
 * @code
 *      Q_INVOKABLE bool readUserData();
 *      Q_INVOKABLE bool writeUserData();
 * @endcode
 * dienen zum Speichern in der Json Datei "roads.json".
 */
class RoutesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
     * @brief RoutesModel
     * Konstruktor, ruft readUserData() auf.
     * @param parent
     */
    explicit RoutesModel(QObject *parent = 0);

    /**
     * @brief The RouteRoles enum
     * Rollen wechle die properties der Daten in dem Array representieren.
     */
    enum RouteRoles {
        NameRole = Qt::UserRole + 1,
//        CoordinatesRole,
        SavedAtDateRole,
    };

    /**
     * @brief roleNames
     * Gibt die enum RouteRoles an die ListView weiter.
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel
     * @return ein Hash der Rollen namen
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /**
     * @brief rowCount
     * Gibt die Anzahl der zu erwarteten Listeneinträge aus.
     * Hier ist das gleich der Größe des internen Array (m_routes.size()).
     * Für nähere Informationen siehe QtDokumentation zu QAbstractItemModel.
     * @param parent = QModelIndex()
     * @return Anzahl
     */
    int rowCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * @brief columnCount
     * Gibt die Anzahl der Splaten der Liste zurück. Diese ist gleich der Anzahl der Rollen.
     * Hier 2.
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
      * liest die gespeicherten nutzerdaten aus des datei saveFileNameRoads
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool readUserData();
    /**
      * @brief writeUserData
      * schreibt die daten aus dem array in die datei saveFileNameRoads
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool writeUserData();
    /**
      * @brief addItem
      * fügt ein item dem array hinzu. datum wird automatisch gesetzt.
      * die koordinaten liste de Route wird als js array über geben und wird entsprechent geparst.
      * @param name name des ortes
      * @param value liste aus qgeocoordinates
      * @return true bei Erfolg
      */
    Q_INVOKABLE bool addItem(QString name, QJSValue value);
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
    Q_INVOKABLE bool changeItemName(const int &index, const QVariant &value);
    /**
      * @brief getCoordsAtIndex
      * gibt eine liste mit koordinaten zurück die den pfad der route darstellen.
      * @param index index des items.
      * @return QList mit QVariants welche qgeocoordinaten sind.
      */
    Q_INVOKABLE QList<QVariant> getCoordsAtIndex(int index);
    /**
      * @brief getName
      * gibt den namen des items im array an der stelle index zurück.
      * @param index index des items.
      * @return name des items.
      */
    Q_INVOKABLE QString getName(int index);

public slots:

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

    /**
     * @brief parseCoordinate
     * Parses a JS-value to a QGeoCoordinate.
     * Code snippet taken from the original qt location api source code.
     * @see http://code.qt.io/cgit/qt/qtlocation.git/tree/src/imports/location/locationvaluetypehelper.cpp#n40
     * @attention no copyright violation intended, no rights reserved.
     */
    QGeoCoordinate parseCoordinate(const QJSValue &value, bool *ok);

private:

    /**
     * @brief m_roads datenarray mit nutzerdaten (routen)
     */
    QVector<Route> m_roads;

};

#endif // ROADSMODEL_H

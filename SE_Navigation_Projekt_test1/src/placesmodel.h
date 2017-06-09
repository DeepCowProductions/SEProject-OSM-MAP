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

class PlacesModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum PlaceRoles {
        NameRole = Qt::UserRole + 1,
//        CoordinateRole,
        LatitudeRole,
        LongitudeRole,
        SavedAtDateRole,
        //        AddressRole,
        //        BoundingBoxRole
    };

    explicit PlacesModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

signals:

public slots:
    Q_INVOKABLE bool clearList();
    Q_INVOKABLE bool writeTestData();
    Q_INVOKABLE bool readUserData();
    Q_INVOKABLE bool writeUserData();
    Q_INVOKABLE bool addItem(QString name, QGeoCoordinate coord);
    Q_INVOKABLE bool removeItem(const QModelIndex &parent = QModelIndex());

protected:

    bool readUserDataFromJson (QJsonObject &object);
    bool writeUserDataToJson (QJsonObject &object);

private:
    QVector<Place> m_places;
};

#endif // PLACESMODEL_H

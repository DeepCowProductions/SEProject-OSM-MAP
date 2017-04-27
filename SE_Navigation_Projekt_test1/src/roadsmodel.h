#ifndef ROADSMODEL_H
#define ROADSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QFile>
#include "road.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPositioning>
#include <QDate>

#define saveFileNameRoads "roads.json"


class RoadsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoadsModel(QObject *parent = 0);

    enum PlaceRoles {
        NameRole = Qt::UserRole + 1,
//        CoordinatesRole,
        SavedAtDateRole,
    };

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
    Q_INVOKABLE QList<QVariant> getCoordsAtIndex(int index);

public slots:

protected:
    bool readUserDataFromJson (QJsonObject &object);
    bool writeUserDataToJson (QJsonObject &object);

private:

    QVector<Road> m_roads;

};

#endif // ROADSMODEL_H

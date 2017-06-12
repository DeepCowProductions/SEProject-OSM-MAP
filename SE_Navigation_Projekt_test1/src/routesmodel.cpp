#include "routesmodel.h"

RoutesModel::RoutesModel(QObject *parent) : QAbstractListModel(parent)
{
//    writeTestData();
    readUserData();
}

QHash<int, QByteArray> RoutesModel::roleNames() const
{

    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "name";
    //    roles[CoordinatesRole] = "coordinates";
    roles[SavedAtDateRole] = "savedAtDate";
    return roles;
}

int RoutesModel::rowCount(const QModelIndex &parent) const
{
    return m_roads.size();
}

int RoutesModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RoutesModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    int row = index.row();
    switch (role) {
    case NameRole       : value = m_roads[row].name();         break;
        //    case CoordinatesRole: value = m_roads[row];                break;
    case SavedAtDateRole: value = m_roads[row].savedAtDate().toString("yyyy-MM-dd");  break;
    }

    return QVariant(value);
}

// TODO
bool RoutesModel::readUserDataFromJson(QJsonObject &object)
{
    QJsonArray ra;
    if (object["roads"].isUndefined())
        return false;
    ra = object["roads"].toArray();
    beginInsertRows(QModelIndex(),m_roads.size(),m_roads.size() + ra.size() - 1 ); // for updating the listView inside qml (required)
    for(int i=0; i < ra.size(); i++) {
        Route r;
        QJsonObject roadJsonObject = ra[i].toObject();
        r.readFromJason(roadJsonObject);
        m_roads.append(r);
    }
    endInsertRows();
    return true;
}

bool RoutesModel::writeUserDataToJson(QJsonObject &object)
{
    QJsonArray ra;
    for (int i=0; i<m_roads.size(); i++) {
        ra.append(m_roads[i].writeToJason());
    }
    object["roads"] = ra;
    return true;
}

// TODO: needs work
bool RoutesModel::readUserData()
{
    clearList();
    QFile saveFile;
    saveFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileNameRoads );
    qDebug() << "saveFile Location: " << saveFile.fileName();
    // cal QDir::makePath?
    if (!saveFile.exists()){
        //        qDebug() << "saveFile not found - trying to create a fresh one";
        //        saveFile.open(QIODevice::ReadWrite);
        //        saveFile.close();
        return false;
        // TBI
    }
    if (saveFile.open(QIODevice::ReadOnly)){
        QByteArray saveData = saveFile.readAll();
        QJsonDocument placesJasonDoc (QJsonDocument::fromJson(saveData));
        // TODO: handle errors
        // TBI

        // finally get data into workable memory
        QJsonObject jsonObject = placesJasonDoc.object() ;
        readUserDataFromJson(jsonObject);
        saveFile.close();
        return true;
    } else
        return false;

}

// TODO: more error handling
bool RoutesModel::writeUserData()
{
    QFile saveFile;
    saveFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileNameRoads );
    if (!saveFile.exists()){
        QDir d;
        qDebug() << "saveFile not found - trying to create a fresh one";
        if (!d.mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))){
            qDebug() << "failed to mkdir of saveFilePath";
            //            return false;
        }
    }
    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "saveFile failed to open / create file";
        return false;
    }
    QJsonObject jasonObject;
    writeUserDataToJson(jasonObject);
    QJsonDocument saveDoc(jasonObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
    return true;
}

/* @see http://code.qt.io/cgit/qt/qtlocation.git/tree/src/imports/location/locationvaluetypehelper.cpp#n40 */
QGeoCoordinate RoutesModel::parseCoordinate(const QJSValue &value, bool *ok)
{
    QGeoCoordinate c;
    if (value.isObject()) {
        if (value.hasProperty(QStringLiteral("latitude")))
            c.setLatitude(value.property(QStringLiteral("latitude")).toNumber());
        if (value.hasProperty(QStringLiteral("longitude")))
            c.setLongitude(value.property(QStringLiteral("longitude")).toNumber());
        if (value.hasProperty(QStringLiteral("altitude")))
            c.setAltitude(value.property(QStringLiteral("altitude")).toNumber());
        if (ok)
            *ok = true;
    }
    return c;
}


bool RoutesModel::addItem( QString name, QJSValue value )
{
    if (!value.isArray())
        return false;

    QList<QGeoCoordinate> pathList;
    quint32 length = value.property(QStringLiteral("length")).toUInt();
    for (quint32 i = 0; i < length; ++i) {
        bool ok;
        QGeoCoordinate c = parseCoordinate(value.property(i), &ok);
        if (!ok || !c.isValid()) {
            qDebug() << "Unsupported path type";
            return false;
        }

        pathList.append(c);
    }

    qDebug() << name << pathList;
    beginInsertRows(QModelIndex(),m_roads.size(),m_roads.size() ); // for updating the listView inside qml (required)
    Route r;
    r.setName(name);
    r.setSavedAtDate(QDate::currentDate());
    r.setCoordinates(pathList);
    m_roads.append(r);
    endInsertRows();
    writeUserData();
    return true;
}

//bool RoadsModel::addItem( QString name, QList<QGeoCoordinate> coords )
//{
//    qDebug() << name << coords;
//    beginInsertRows(QModelIndex(),m_roads.size(),m_roads.size() ); // for updating the listView inside qml (required)
//    Road r;
//    r.setName(name);
//    r.setSavedAtDate(QDate::currentDate());
//    r.setCoordinates(coords);
//    m_roads.append(r);
//    endInsertRows();
//}

QList<QVariant> RoutesModel::getCoordsAtIndex(int index)
{
    //    return m_roads[index].coordinates();
    QVariantList tmp;

    tmp.reserve(m_roads[index].coordinates().size());

    for (const QGeoCoordinate& i: m_roads[index].coordinates())
        tmp.push_back(QVariant::fromValue(i));

    return tmp;
}

bool RoutesModel::clearList()
{
    qDebug() << "clearListcalled";
    beginRemoveRows(QModelIndex() , 0 , m_roads.size()-1);
    m_roads.clear();
    endRemoveRows();
    return true;
}

bool RoutesModel::writeTestData()
{
    Route p1;
    p1.addCoordinate(QGeoCoordinate(50.0,50.0));
    p1.addCoordinate(QGeoCoordinate(51.0,52.0));
    p1.setName("test1");
    p1.setSavedAtDate(QDate::currentDate());
    m_roads.append(p1);
    Route p2;
    p2.addCoordinate(QGeoCoordinate(10.0,42.0));
    p2.addCoordinate(QGeoCoordinate(8.0,20.0));
    p2.addCoordinate(QGeoCoordinate(6.0,40.0));
    p2.setName("test2");
    p2.setSavedAtDate(QDate::currentDate());
    m_roads.append(p2);
    Route p3;
    p3.addCoordinate(QGeoCoordinate(60.0,60.0));
    p3.setName("test3");
    p3.setSavedAtDate(QDate::currentDate());
    m_roads.append(p3);
    return true;
    //    writeUserData();
}

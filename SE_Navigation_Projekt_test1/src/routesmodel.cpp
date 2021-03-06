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
    Q_UNUSED(parent);
    return m_roads.size();
}

int RoutesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
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

bool RoutesModel::readUserData()
{
    clearList();
    QFile saveFile;
    saveFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileNameRoads );
    qDebug() << "saveFile Location: " << saveFile.fileName();
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
        QJsonObject jsonObject = placesJasonDoc.object() ;
        readUserDataFromJson(jsonObject);
        saveFile.close();
        return true;
    } else
        return false;

}

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

bool RoutesModel::deleteItem(const int &index)
{
    if (m_roads.isEmpty())
        return false;
    beginRemoveRows(QModelIndex() , index , index);
//    m_roads.clear();
    m_roads.removeAt(index);
    endRemoveRows();
    writeUserData();
    return true;
}

bool RoutesModel::changeItemName(const int &i, const QVariant &value)
{
    if (m_roads.isEmpty())
        return false;
//    if (m_roads[i].name() != value) {
//        m_roads[i].setName(value.toString());
//        emit dataChanged(index(i,-1), index(i,-1), QVector<int>() << NameRole); // maybe not correct...
//        return true;
//    }
//    return false;
    bool suc = setData(index(i,0),value,NameRole);
    writeUserData();
    return suc;
}

bool RoutesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        int row = index.row();
        switch (role) {
        case NameRole :
            m_roads[row].setName(value.toString());
            break;
//        case CoordinatesRole:
//            m_roads[row]; // not yet used or implemented
//            break;
        case SavedAtDateRole:
//            m_roads[row].setSavedAtDate(QDate::currentDate());
            m_roads[row].setSavedAtDate(m_roads[row].savedAtDate());
            break;
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

//Qt::ItemFlags RoutesModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable; // FIXME: Implement me!
//}


QList<QVariant> RoutesModel::getCoordsAtIndex(int index)
{
    //    return m_roads[index].coordinates();
    QVariantList tmp;

    if (m_roads.isEmpty())
        return tmp;

    tmp.reserve(m_roads[index].coordinates().size());

    for (const QGeoCoordinate& i: m_roads[index].coordinates())
        tmp.push_back(QVariant::fromValue(i));

    return tmp;
}

QString RoutesModel::getName(int index)
{
    if (m_roads.isEmpty())
        return "";
    return m_roads[index].name();
}

bool RoutesModel::clearList()
{
    qDebug() << "clearListcalled";
    beginRemoveRows(QModelIndex() , 0 , m_roads.size()-1);
    m_roads.clear();
    endRemoveRows();
    return true;
}


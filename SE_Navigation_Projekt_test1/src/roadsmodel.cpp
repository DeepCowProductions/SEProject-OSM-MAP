#include "roadsmodel.h"

RoadsModel::RoadsModel(QObject *parent) : QAbstractListModel(parent)
{
    writeTestData();
}

QHash<int, QByteArray> RoadsModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "name";
//    roles[CoordinatesRole] = "coordinates";
    roles[SavedAtDateRole] = "savedAtDate";
    return roles;
}

int RoadsModel::rowCount(const QModelIndex &parent) const
{
    return m_roads.size();
}

int RoadsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RoadsModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    int row = index.row();
    switch (role) {
    case NameRole       : value = m_roads[row].name();         break;
//    case CoordinatesRole: value = m_roads[row];                break;
    case SavedAtDateRole: value = m_roads[row].savedAtDate();  break;
    }

    return QVariant(value);
}

// TODO
bool RoadsModel::readUserDataFromJson(QJsonObject &object)
{
    QJsonArray ra;
    if (object["roads"].isUndefined())
        return false;
    ra = object["roads"].toArray();
    beginInsertRows(QModelIndex(),m_roads.size(),m_roads.size() + ra.size() - 1 ); // for updating the listView inside qml (required)
    for(int i=0; i < ra.size(); i++) {
        Road r;
        QJsonObject roadJsonObject = ra[i].toObject();
        r.readFromJason(roadJsonObject);
        m_roads.append(r);
    }
    endInsertRows();
    return true;
}

bool RoadsModel::writeUserDataToJson(QJsonObject &object)
{
    QJsonArray ra;
    for (int i=0; i<m_roads.size(); i++) {
        ra.append(m_roads[i].writeToJason());
    }
    object["roads"] = ra;
    return true;
}

// TODO: needs work
bool RoadsModel::readUserData()
{
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
bool RoadsModel::writeUserData()
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
}

bool RoadsModel::addItem( QString name, QList<QGeoCoordinate> coords )
{
    beginInsertRows(QModelIndex(),m_roads.size(),m_roads.size() ); // for updating the listView inside qml (required)
    Road r;
    r.setName(name);
    r.setSavedAtDate(QDate::currentDate());
    r.setCoordinates(coords);
    m_roads.append(r);
    endInsertRows();
}

QList<QVariant> RoadsModel::getCoordsAtIndex(int index)
{
//    return m_roads[index].coordinates();
    QVariantList tmp;

    tmp.reserve(m_roads[index].coordinates().size());

    for (const QGeoCoordinate& i: m_roads[index].coordinates())
      tmp.push_back(QVariant::fromValue(i));

    return tmp;
}

bool RoadsModel::clearList()
{
    qDebug() << "clearListcalled";
    beginRemoveRows(QModelIndex() , 0 , m_roads.size()-1);
    m_roads.clear();
    endRemoveRows();
}

bool RoadsModel::writeTestData()
{
    Road p1;
    p1.addCoordinate(QGeoCoordinate(50.0,50.0));
    p1.addCoordinate(QGeoCoordinate(51.0,52.0));
    p1.setName("test1");
    p1.setSavedAtDate(QDate::currentDate());
    m_roads.append(p1);
    Road p2;
    p2.addCoordinate(QGeoCoordinate(10.0,42.0));
    p2.addCoordinate(QGeoCoordinate(8.0,20.0));
    p2.addCoordinate(QGeoCoordinate(6.0,40.0));
    p2.setName("test2");
    p2.setSavedAtDate(QDate::currentDate());
    m_roads.append(p2);
    Road p3;
    p3.addCoordinate(QGeoCoordinate(60.0,60.0));
    p3.setName("test3");
    p3.setSavedAtDate(QDate::currentDate());
    m_roads.append(p3);

    //    writeUserData();
}

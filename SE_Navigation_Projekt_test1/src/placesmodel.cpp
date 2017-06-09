#include "placesmodel.h"
PlacesModel::PlacesModel(QObject *parent) : QAbstractListModel(parent)
{
//    writeTestData();
    readUserData();
}

QHash<int, QByteArray> PlacesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "name";
//    roles[CoordinateRole] = "coordinate";
    roles[LatitudeRole] = "latitude";
    roles[LongitudeRole] = "longitude";
    roles[SavedAtDateRole] = "savedAtDate";
//    roles[AddressRole] = "address";
//    roles[BoundingBoxRole] = "boundingBox";

    return roles;
}

int PlacesModel::rowCount(const QModelIndex &parent) const
{
    return m_places.size();
}

int PlacesModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant PlacesModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    int row = index.row();
    switch (role) {
    case NameRole       : value = m_places[row].name();         break;
//    case CoordinateRole : value = m_places[row].coordinate();   break;
    case LatitudeRole : value = m_places[row].coordinate().latitude();     break;
    case LongitudeRole : value = m_places[row].coordinate().longitude();   break;
    case SavedAtDateRole: value = m_places[row].savedAtDate().toString("yyyy-MM-dd");  break;
//    case AddressRole    : value = m_places[row].address();      break;
//    case BoundingBoxRole: value = m_places[row].boundingBox();  break;
    }

    return QVariant(value);
}

bool PlacesModel::readUserDataFromJson(QJsonObject &object)
{
    QJsonArray pa;
    if (object["places"].isUndefined())
        return false;
    pa = object["places"].toArray();
    beginInsertRows(QModelIndex(),m_places.size(),m_places.size() + pa.size() - 1 ); // for updating the listView inside qml (required)
    for(int i=0; i < pa.size(); i++) {
        Place p;
        QJsonObject placeJsonObject = pa[i].toObject();
        p.readFromJason(placeJsonObject);
        m_places.append(p);
    }
    endInsertRows();
    return true;
}

bool PlacesModel::writeUserDataToJson(QJsonObject &object)
{
    QJsonArray pa;
    if (m_places.size() > 0){
        for (int i=0; i<m_places.size(); i++) {
            pa.append(m_places[i].writeToJason());
        }
        object["places"] = pa;
    }
    return true;
}

// TODO: needs work
bool PlacesModel::readUserData()
{
    clearList();
    QFile saveFile;
    saveFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileNamePlaces );
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
        QJsonObject placesJsonObject = placesJasonDoc.object() ;
        readUserDataFromJson(placesJsonObject);
        saveFile.close();
        return true;
    } else
        return false;

}

// TODO: more error handling
bool PlacesModel::writeUserData()
{
    QFile saveFile;
    saveFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileNamePlaces );
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
    QJsonObject placesJasonObject;
    writeUserDataToJson(placesJasonObject);
    QJsonDocument saveDoc(placesJasonObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
    return true;
}

bool PlacesModel::addItem(QString name, QGeoCoordinate coord)
{
    beginInsertRows(QModelIndex(),m_places.size(),m_places.size() ); // for updating the listView inside qml (required)
    Place p;
    p.setName(name);
    p.setCoordinate(coord);
    p.setSavedAtDate(QDate::currentDate());
    m_places.append(p);
    endInsertRows();
    writeUserData();
    return true;
}

bool PlacesModel::removeItem(const QModelIndex &parent)
{
//    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
//    endRemoveRows();
}

bool PlacesModel::clearList()
{
    qDebug() << "clearListcalled";
    beginRemoveRows(QModelIndex() , 0 , m_places.size()-1);
    m_places.clear();
    endRemoveRows();
    return true;
}

bool PlacesModel::writeTestData()
{
    Place p1;
    p1.setCoordinate(QGeoCoordinate(50.0,50.0));
    p1.setName("test1");
    p1.setSavedAtDate(QDate::currentDate());
    m_places.append(p1);
    Place p2;
    p2.setCoordinate(QGeoCoordinate(10.0,42.0));
    p2.setName("test2");
    p2.setSavedAtDate(QDate::currentDate());
    m_places.append(p2);
    Place p3;
    p3.setCoordinate(QGeoCoordinate(60.0,60.0));
    p3.setName("test3");
    p3.setSavedAtDate(QDate::currentDate());
    m_places.append(p3);
    return true;
//    writeUserData();
}

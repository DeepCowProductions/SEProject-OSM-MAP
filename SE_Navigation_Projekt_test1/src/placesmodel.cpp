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
    Q_UNUSED(parent);
    return m_places.size();
}

int PlacesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
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

bool PlacesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        int row = index.row();
        switch (role) {
        case NameRole       : m_places[row].setName(value.toString());         break;
    //    case CoordinateRole : m_places[row].coordinate();   break;
        case LatitudeRole : m_places[row].coordinate().setLatitude(value.toDouble());     break;
        case LongitudeRole : m_places[row].coordinate().setLongitude(value.toDouble());   break;
        case SavedAtDateRole: m_places[row].setSavedAtDate(QDate::currentDate());   break;
    //    case AddressRole    : m_places[row].address();      break;
    //    case BoundingBoxRole: m_places[row].boundingBox();  break;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;

}

bool PlacesModel::clearList()
{
    qDebug() << "clearListcalled";
    beginRemoveRows(QModelIndex() , 0 , m_places.size()-1);
    m_places.clear();
    endRemoveRows();
    return true;
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

bool PlacesModel::readUserData()
{
    clearList();
    QFile saveFile;
    saveFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileNamePlaces );
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
        QJsonObject placesJsonObject = placesJasonDoc.object() ;
        readUserDataFromJson(placesJsonObject);
        saveFile.close();
        return true;
    } else
        return false;

}

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


bool PlacesModel::deleteItem(const int &index)
{
    if (m_places.isEmpty())
        return false;
    beginRemoveRows(QModelIndex() , index , index);
//    m_roads.clear();
    m_places.removeAt(index);
    endRemoveRows();
    writeUserData();
    return true;
}

bool PlacesModel::changeItemName(const int &i, const QVariant &value)
{
    if (m_places.isEmpty())
        return false;
    bool suc = setData(index(i,0),value,NameRole);
    writeUserData();
    return suc;
}

QString PlacesModel::getName(int index)
{
    if (m_places.isEmpty())
        return "";
    return m_places[index].name();
}

double PlacesModel::getLatiAtIndex(int index)
{
    if (m_places.isEmpty())
        return 0.0;
    return m_places[index].coordinate().latitude();
}

double PlacesModel::getLongiAtIndex(int index)
{
    if (m_places.isEmpty())
        return 0.0;
    return m_places[index].coordinate().longitude();
}

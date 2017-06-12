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

class LocationPin : public QObject, public QGeoLocation
{
    Q_OBJECT
public:
    explicit LocationPin(QObject *parent = 0);
    ~LocationPin();

    void readFromJason(QJsonObject &object);
    QJsonObject writeToJason();

    QString name() const;
    QDate savedAtDate() const;

    void setSavedAtDate(QDate savedAtDate);

signals:

public slots:
    Q_INVOKABLE bool readUserData();
    Q_INVOKABLE bool writeUserData();

private:
    QString m_name = "Pinned Location";
    QDate m_savedAtDate;
};

#endif // LOCATIONPIN_H
#include "tile.h"

Tile::Tile(int x, int y, int zoomlevel, QString pluginName, int mapId, QString format, QObject * parent) : QObject(parent)
{
    m_x = x;
    m_y = y;
    m_zoomlevel = zoomlevel;
    m_pluginName = pluginName;
    m_mapId = mapId;
    m_format = format;
}

Tile::Tile(double longitude, double latitude, int zoomlevel, QString pluginName, int mapId, QString format, QObject *parent) : QObject(parent)
{
    m_zoomlevel = zoomlevel;
    m_x = long2tilex(longitude);
    m_y = lat2tiley(latitude);

    m_pluginName = pluginName;
    m_mapId = mapId;
    m_format = format;
}

int Tile::long2tilex(double lon)
{
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, m_zoomlevel)));
}

int Tile::lat2tiley(double lat)
{
    return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, m_zoomlevel)));
}

QString Tile::format() const
{
    return m_format;
}

void Tile::setFormat(const QString &format)
{
    m_format = format;
}

QByteArray Tile::imageData() const
{
    return m_imageData;
}

void Tile::setImageData(const QByteArray &imageData)
{
    m_imageData = imageData;
}

int Tile::mapId() const
{
    return m_mapId;
}

void Tile::setMapId(int mapId)
{
    m_mapId = mapId;
}

QString Tile::pluginName() const
{
    return m_pluginName;
}

void Tile::setPluginName(const QString &pluginName)
{
    m_pluginName = pluginName;
}

int Tile::zoomlevel() const
{
    return m_zoomlevel;
}

void Tile::setZoomlevel(int zoomlevel)
{
    m_zoomlevel = zoomlevel;
}

int Tile::y() const
{
    return m_y;
}

void Tile::setY(int y)
{
    m_y = y;
}

int Tile::x() const
{
    return m_x;
}

void Tile::setX(int x)
{
    m_x = x;
}

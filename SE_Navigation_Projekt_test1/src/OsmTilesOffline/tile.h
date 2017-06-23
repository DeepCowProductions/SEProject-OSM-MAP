#ifndef TILE_H
#define TILE_H

#include <QString>
#include <QObject>
#include <math.h>


/**
 * @brief The Tile class
 *      Modelklasse eines Tiles
 */
class Tile : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Tile erstellt ein Objekt vom Typ tile
     * @param x X-Wert nach der Projektion
     * @param y Y-Wert nach der Projektion
     * @param zoomlevel Zoomlevel in der sich das tile befindet
     * @param pluginName Name des genutzten Plugin. Hier ist Standardmäßig OSM vorgegeben
     * @param mapId Die MapId bestimmt den Maptyp der vom Plugin genutzt wird. Wird von der Tile-Klasse um hinterher daraus
     *          einen Dateinamen zu bilden.
     */
    explicit Tile(int x , int y , int zoomlevel = 10, QString pluginName = "osm", int mapId = 0, QString format = "png", QObject *parent = 0);
    /**
     * @brief Tile Konstruktor falls die X- und Y-Werte nicht bekannt sind und diese per longitude und latitude ermittelt
     *          werden müssen.
     * @param longitude longitude des Tiles
     * @param latitude Latitude des Tiles
     * @param zoomlevel Zoomlevel in der sich das tile befindet
     * @param pluginName Name des genutzten Plugin. Hier ist Standardmäßig OSM vorgegeben
     * @param mapId Die MapId bestimmt den Maptyp der vom Plugin genutzt wird. Wird von der Tile-Klasse um hinterher daraus
     *          einen Dateinamen zu bilden.
     */
    explicit Tile(double longitude, double latitude , int zoomlevel = 10, QString pluginName = "osm", int mapId = 0, QString format = ".png", QObject *parent = 0);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int zoomlevel() const;
    void setZoomlevel(int zoomlevel);

    QString pluginName() const;
    void setPluginName(const QString &pluginName);

    int mapId() const;
    void setMapId(int mapId);

    QByteArray imageData() const;
    void setImageData(const QByteArray &imageData);

    QString format() const;
    void setFormat(const QString &format);

private:
    /**
     * @brief long2tilex Funktion zum umrechnen von Longitude zu dem gesuchten X-Wert
     * @param lon ist die Longitude die umgerechnet werden soll
     * @return Der X-Wert des Tiles auf Grundlage der Longitude
     */
    int long2tilex(double lon);
    /**
     * @brief lat2tiley Funktion zum umrechnen von Latitude zu dem gesuchten Y-Wert
     * @param lat ist die Latitude die umgerechnet werden soll
     * @return Der Y-Wert des Tiles auf Grundlage der Latitude
     */
    int lat2tiley(double lat);

    /**
     * @brief m_x X-Wert des Tiles
     */
    int m_x;

    /**
     * @brief m_y Y-Wert des Tiles
     */
    int m_y;

    /**
     * @brief m_zoomlevel Zoomlevel des Tiles.
     */
    int m_zoomlevel;

    /**
     * @brief m_pluginName Name des Plugintyps. (Hier OSM)
     */
    QString m_pluginName;

    /**
     * @brief m_mapId MapId wird für den Dateinamen benötigt. Anderer nutzen unklar
     */
    int m_mapId;
    /**
     * @brief m_imageData sind die Bilddaten des Tiles.
     */
    QByteArray m_imageData;

    /**
     * @brief m_format Format der Bilddatei.
     */
    QString m_format;

};

#endif // TILE_H

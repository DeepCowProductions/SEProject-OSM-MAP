#ifndef NETWORKACCESMANAGERSINGLETON_HPP
#define NETWORKACCESMANAGERSINGLETON_HPP

#include <QObject>
#include <QNetworkAccessManager>


/**
 * @brief The NetworkAccesManagerSingleton class Singleton-Klasse zum erstellen eines NetworkAccessMannager der im gesamten
 *  Kontext des Systems einmalig ist.
 *
 * TODO: Achtung die aktuelle Implementierung ist nicht Threadsicher. Wenn beim Rendern oder bei Netzwerkzugriffen Thread's
 *       genutzt werden möchten muss die Klasse nach folgendem Schema umgeschrieben werden:
 *
 *       https://wiki.qt.io/Qt_thread-safe_singleton
 */
class NetworkAccesManagerSingleton : public QObject
{

public:
    static QNetworkAccessManager * getInstance();

private:

    static QNetworkAccessManager * m_manager;

    NetworkAccesManagerSingleton(QObject * parent = 0) : QObject(parent){

    }

    ~NetworkAccesManagerSingleton();/*{
        if(m_manager)
            delete m_manager;
    }*/


};

QNetworkAccessManager * NetworkAccesManagerSingleton::m_manager = 0;

QNetworkAccessManager * NetworkAccesManagerSingleton::getInstance()
{
    if(!m_manager)
        m_manager = new QNetworkAccessManager();
    return m_manager;
}

#endif // NETWORKACCESMANAGERSINGLETON_HPP

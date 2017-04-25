#ifndef SETTINGS_H
#define SETTINGS_H

#include <QQuickItem>

class Settings : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString home READ home WRITE setHome NOTIFY homeChanged)
    QString m_home;

public:
    Settings();

    QString home() const;

signals:

    void homeChanged(QString home);

public slots:

void setHome(QString home);
};

#endif // SETTINGS_H

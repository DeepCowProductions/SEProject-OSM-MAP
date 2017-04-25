#include "settings.h"

Settings::Settings()
{
    setHome("Ierlohn");
}

QString Settings::home() const
{
    return m_home;
}

void Settings::setHome(QString home)
{
    if (m_home == home)
        return;

    m_home = home;
    emit homeChanged(home);
}

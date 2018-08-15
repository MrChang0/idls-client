#include "setting.h"

#include <QSettings>

Setting::Setting(const QString& filename)
{
    QSettings settings(filename,QSettings::IniFormat);

    uuid = settings.value("uuid").toString();
    type = settings.value("type").toString();
    name = settings.value("name").toString();
    description = settings.value("description").toString();
    signalstrs = settings.value("signals").toString().split('\n');
    eventstrs = settings.value("events").toString().split('\n');
}

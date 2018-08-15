#ifndef SETTING_H
#define SETTING_H

#include <QString>
#include <QStringList>

class Setting
{
public:
    Setting(const QString& filename);
    QString uuid;
    QString type;
    QString name;
    QString description;
    QStringList signalstrs;
    QStringList eventstrs;
};

#endif // SETTING_H

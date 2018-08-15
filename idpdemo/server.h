#ifndef SERVER_H
#define SERVER_H
#include <QString>
#include <QByteArray>
#include <QJsonObject>

#include "device.h"

class Server
{
public:
    QByteArray toJson() const;
    bool fromJson(QByteArray);
    void setcommand(const QString& cmd){command = cmd;}
	
    static QByteArray deal(const QByteArray&,Device&);
private:
    const QString proto = "idp.v1";
    QString command;
    QJsonObject data;
};

#endif // SERVER_H

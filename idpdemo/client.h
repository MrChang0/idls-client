#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>

#include "device.h"
class Client
{
public:
    bool fromJson(const QByteArray&);
    QByteArray toJson(const QJsonObject&) const;
    void setprototype(const QString& type){prototype = type;}
    QJsonObject getdata() const {return data;}

    static QByteArray online(const Device& device);
	static QByteArray reg(const Device& device);
	static QByteArray signal(const Signal& signal);
private:
    const QString proto = "idp.v1";
    QString prototype;
    QJsonObject data;
};

#endif // CLIENT_H

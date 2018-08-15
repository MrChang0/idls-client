#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QMap>
#include <functional>
#include "client.h"

bool Server::fromJson(QByteArray byte){
    QJsonParseError error;
    auto document = QJsonDocument::fromJson(byte,&error);
    if(document.isNull()){
        qDebug()<<error.error;
        return false;
    }
    auto object = document.object();
    if(object.contains("command"))
        command = object["command"].toString();
    if(object.contains("data"))
        data = object["data"].toObject();
    return true;
}

QByteArray Server::toJson() const
{
    QJsonObject json;
    json.insert("proto",proto);
    json.insert("command",command);

    QJsonDocument document;
    document.setObject(json);
    return document.toJson(QJsonDocument::Compact);
}

QMap<QString,std::function<QByteArray(Device&,const QJsonObject&)>> init()
{
    QMap<QString,std::function<QByteArray(Device&,const QJsonObject&)>> map;
    map["register"]=[](Device& device,const QJsonObject&)->QByteArray{return Client::reg(device);};
    map["event"]=[](Device& device,const QJsonObject& object)->QByteArray{
        device.setEvent(Event::parse(object));
        return QByteArray();
    };
	return map;
}

auto cmds = init();


QByteArray Server::deal(const QByteArray& byte,Device& device)
{
	Server server;
	if(!server.fromJson(byte))
		return QByteArray();
    return cmds[server.command](device,server.data);
}

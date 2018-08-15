#include "client.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

bool Client::fromJson(const QByteArray& byte){
    QJsonParseError jsonError;
    auto document = QJsonDocument::fromJson(byte,&jsonError);
    if(document.isNull()){
        qDebug()<<jsonError.error;
        return false;
    }
    auto object = document.object();
    if(object.contains("prototype"))
        prototype = object["prototype"].toString();
    if(object.contains("data"))
        data = object["data"].toObject();
    return true;
}

QByteArray Client::toJson(const QJsonObject& data) const
{
    QJsonObject json;
    json.insert("proto",proto);
    json.insert("prototype",prototype);
    json.insert("data",data);

    QJsonDocument document;
    document.setObject(json);
    return document.toJson(QJsonDocument::Compact);
}

QByteArray Client::online(const Device &device){
    Client client;
    client.setprototype("online");
    QJsonObject data;
    data.insert("uuid",device.getuuid());
    return client.toJson(data);
}

QByteArray Client::reg(const Device& device)
{
	Client client;
	client.setprototype("register");
	const auto data =  device.toJson();
	return client.toJson(data);
}

QByteArray Client::signal(const Signal& signal)
{
	Client client;
	client.setprototype("signal");
    const auto data = signal.toObject();
    return client.toJson(data);
}

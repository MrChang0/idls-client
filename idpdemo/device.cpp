#include "device.h"

#include <QJsonObject>
#include <QJsonDocument>

Device::Device(const Setting &setting){
    uuid = setting.uuid;
    type = setting.type;
    name = setting.name;
    description = setting.description;
    _signals = SignalType::Parse(setting.signalstrs);
    events = EventType::parse(setting.eventstrs);
}

QJsonObject Device::toJson() const
{
    QJsonObject object;
	object.insert("uuid",uuid);
	object.insert("type",type);
	object.insert("name",name);
	object.insert("description",description);
	object.insert("signals",_signals.toArray());
	object.insert("events",events.toArray());

	return object;
}

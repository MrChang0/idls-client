#include "event.h"

#include <QStringList>
#include <QDebug>

QJsonObject EventType::toObject() const
{
    QJsonObject object;
    object.insert("name",name);
    object.insert("description",description);
    object.insert("args",args.toArray());

    return object;
}

BaseJsonArray<EventType> EventType::parse(const QStringList &strs){
    BaseJsonArray<EventType> ret;
	for (const auto& str : strs) {
        EventType event;
		auto list = str.split(':');
		event.description = list[1];
		const auto index = list[0].indexOf('(');
		if (index == -1)
		{
			qDebug() << "parse error";
			continue;
		}
		event.name = list[0].left(index);
		auto args = list[0].mid(index + 1);
		event.args = ArgType::parse(args);
		ret.addObject(event);
	}
	return ret;
}

Event Event::parse(const QJsonObject &object){
    Event event;
    if(object.contains("name")){
        event.name = object["name"].toString();
    }
    auto arrays = object["args"].toArray();
    event.args = Arg::parse(arrays);
    return event;
}

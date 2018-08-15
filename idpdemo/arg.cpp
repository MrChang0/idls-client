#include "arg.h"
#include <QJsonDocument>
#include <QStringList>
#include <QJsonArray>

QJsonObject ArgType::toObject() const
{
    QJsonObject object;
    object.insert("name",name);
    object.insert("type",type);
    return object;
}

BaseJsonArray<ArgType> ArgType::parse(QString& text)
{
	if(text.startsWith('('))
		text.remove(1,1);
	if(text.endsWith(')'))
		text.chop(1);
	auto strs = text.split(',');

	BaseJsonArray<ArgType> ret;
	for(const auto& str:strs)
	{
		ArgType arg;
		auto list = str.split(' ');
		arg.settype(list[0]);
		arg.setname(list[1]);
		ret.addObject(arg);
	}
	return ret;
}

QJsonObject Arg::toObject() const{
    QJsonObject object;
    object.insert("name",Name);
    object.insert("data",Data);
    return object;
}

BaseJsonArray<Arg> Arg::parse(QJsonArray &arrags){
    BaseJsonArray<Arg> ret;
    for(const auto &object:arrags){
        Arg arg;
        arg.Name = object.toObject()["name"].toString();
        arg.Data = object.toObject()["data"].toString();
        ret.addObject(arg);
    }
    return ret;
}

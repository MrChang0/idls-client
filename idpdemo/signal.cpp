#include "signal.h"
#include <QStringList>
#include <QDebug>
#include <QMap>

QJsonObject SignalType::toObject() const
{
    QJsonObject object;
    object.insert("name",name);
    object.insert("description",description);
    object.insert("args",args.toArray());

    return object;
}

BaseJsonArray<SignalType> SignalType::Parse(const QStringList &strs){
    BaseJsonArray<SignalType> ret;
    for(const auto& str:strs){
        SignalType signal;
        auto list = str.split(':');
		signal.description = list[1];
		const auto index = list[0].indexOf('(');
		if(index == -1)
		{
			qDebug()<<"parse error";
			continue;
		}
		signal.name = list[0].left(index);
		auto args = list[0].mid(index + 1);
		signal.args = ArgType::parse(args);
		ret.addObject(signal);
	}
	return ret;
}

QMap<QString, std::function<QString(const QString&)>> init()
{
   QMap<QString, std::function<QString(const QString&)>> ret;
    ret["string"] = [](const QString& text) {return text.mid(1, text.length() - 2); };
    ret["number"] = [](const QString& text) {return text; };
    ret["bool"] = [](const QString& text) {return text; };
    return ret;
}


auto maps = init();

Signal Signal::Parse(const BaseJsonArray<SignalType>& signaltypes,QString &text){
    Signal signal;
    auto strs = text.split('(');
	const auto signalname = strs[0];
	strs[1].chop(1);
    auto siganltypesdata = signaltypes.getdata();

	SignalType signaltype;
    for(const auto& tmp:siganltypesdata){
		if(tmp.getname() == signalname)
		{
			signaltype = tmp;
			break;
		}
    }
	auto argstypes = signaltype.getArgTypes();
	const auto argstrs = strs[1].split(',');
	Q_ASSERT(argstrs.size() == argstypes.size());

	Signal ret;
	ret.Name = signalname;
	for(auto i = 0;i<argstrs.size();++i)
	{
		Arg arg;
		arg.setName(argstypes[i].getName());
		arg.setData(maps[argstypes[i].getType()](argstrs[i]));
		ret.addArg(arg);
	}
	return ret;
}

QJsonObject Signal::toObject() const
{
	QJsonObject object;
	object.insert("name", Name);
	object.insert("args", args.toArray());

	return object;
}


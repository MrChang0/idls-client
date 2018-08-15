#ifndef SIGNAL_H
#define SIGNAL_H

#include <QString>

#include "arg.h"
#include "basejsonobject.h"

class SignalType
{
public:
    QJsonObject toObject() const;
	void setdescription(const QString& des){description = des;}
	void setname(const QString& _name){name = _name;}
	QString getname()const {return name;}
    void setargs(const BaseJsonArray<ArgType>& arr){args = arr;}
	QVector<ArgType> getArgTypes()const {return args.getdata();}
    static BaseJsonArray<SignalType> Parse(const QStringList&);
private:
    QString name;
    QString description;
    BaseJsonArray<ArgType> args;
};

class Signal
{
public:
	void addArg(Arg arg){args.addObject(arg);}
	QJsonObject toObject()const ;

    static Signal Parse(const BaseJsonArray<SignalType>&,QString&);
private:
    QString Name;
    BaseJsonArray<Arg> args;
};

#endif // SIGNAL_H

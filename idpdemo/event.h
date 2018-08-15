#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include "arg.h"

class EventType
{
public:
    QJsonObject toObject() const;
    void setname(QString& _name){name = _name;}
    void setdescription(QString& _description){description = _description;}
    static BaseJsonArray<EventType> parse(const QStringList&);
private:
    QString name;
    QString description;
    BaseJsonArray<ArgType> args;
};

class Event{
public:

    static Event parse(const QJsonObject& object);
    QString toString(){
        QString str = name+"(";
        for(auto &arg:args.getdata()){
            str+=arg.getData()+",";
        }
        str[str.length() - 1] = ')';
        return str;
    }
private:
    QString name;
    BaseJsonArray<Arg> args;
};

#endif // EVENT_H

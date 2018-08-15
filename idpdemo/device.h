#ifndef DEVICE_H
#define DEVICE_H
#include <QString>
#include <QJsonArray>

#include "signal.h"
#include "event.h"
#include "setting.h"

class Device
{
public:
    Device(){}
    Device(const Setting&);
    QJsonObject toJson() const;
    void setuuid(const QString& _uuid){uuid = _uuid;}
    QString getuuid() const {return uuid;}
    void setname(const QString& _name){name = _name;}
	QString getname()const{return name;}
    void settype(const QString& _type){type = _type;}
	QString gettype() const {return type;}
    void setdescription(const QString& _description){description = _description;}
	QString getdescription()const{return description;}
	void setsignals(const BaseJsonArray<SignalType>& arr){_signals = arr;}
    void setevents(const BaseJsonArray<EventType>& arr){events = arr;}
    void setEvent(const Event& _event){event = _event;}
    BaseJsonArray<SignalType> getSignalTypes() const {return _signals;}
    QString EventString(){return event.toString();}
private:
    QString uuid;
    QString type;
    QString name;
    QString description;
    BaseJsonArray<SignalType> _signals;
    BaseJsonArray<EventType> events;
    Event event;
};

#endif // DEVICE_H

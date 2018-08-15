#ifndef ARGS_H
#define ARGS_H
#include <QString>
#include "basejsonobject.h"
class ArgType
{
public:
	ArgType(){}
    ArgType(QString name,QString type):name(name),type(type){}
    QJsonObject toObject() const;
    void setname(QString _name){name = _name;}
    void settype(QString _type){type = _type;}
	QString getType()const{return type;}
	QString getName()const{return name;}
    static BaseJsonArray<ArgType> parse(QString& str);
private:
    QString name;
    QString type;
}; 

class Arg
{
public:
	void setName(const QString name){Name = name;}
	void setData(const QString data){Data = data;}
    QString getData(){return Data;}
    QJsonObject toObject() const;

    static BaseJsonArray<Arg> parse(QJsonArray&);
private:
    QString Name;
    QString Data;
};

#endif // ARGS_H

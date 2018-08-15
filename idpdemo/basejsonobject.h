#ifndef BASEJSONOBJECT_H
#define BASEJSONOBJECT_H
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

template<class T>
class BaseJsonArray{
public:
	QJsonArray toArray() const {
		QJsonArray ret;
		for (const auto& data : datas)
			ret.push_back(data.toObject());
		return ret;
	}
    void addObject(const T& data){datas.push_back(data);}
    QVector<T> getdata() const {return datas;}
private:
    QVector<T> datas;
};

#endif // BASEJSONOBJECT_H

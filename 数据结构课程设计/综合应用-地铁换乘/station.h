#ifndef STATION_H

#define STATION_H

#include <QString>
#include <QPointF>
#include <QSet>

class SubwayGraph;
class QTextStream;

//地铁站点类定义与信息存储
class Station
{
protected:
    int id;
    QString name;
    double longitude, latitude;
    QSet<int> linesInfo;

    //所有站点的边界位置
    static double minLongitude, minLatitude, maxLongitude, maxLatitude;

public:
    Station();
    Station(QString nameStr, double longi, double lati, QList<int> linesList);

protected:
    int GetDistance(Station other);
    friend class SubwayGraph;
    friend class QTextStream;
};

#endif // STATION_H

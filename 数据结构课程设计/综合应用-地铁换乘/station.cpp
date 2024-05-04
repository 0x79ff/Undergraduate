#include "station.h"
#include <math.h>

#define pi 3.1415926
#define earth_radius 6378.137

//构造函数
Station::Station(){}
Station::Station(QString nameStr, double longi, double lati, QList<int> linesList):
    name(nameStr), longitude(longi), latitude(lati)
{
    linesInfo=linesList.toSet();
}
double Station::minLongitude = 200;
double Station::minLatitude = 200;
double Station::maxLongitude = 0;
double Station::maxLatitude = 0;

// 弧度转化
double GetRad(double x)
{
    return x * pi / 180.0;
}

int Station::GetDistance(Station other)
{
    double x1,y1,x2,y2;
    x1 = latitude;y1 = longitude;
    x2 = other.latitude;y2 = other.longitude;

    //通过精度纬度来得到直线距离
    double a = GetRad(x1) - GetRad(x2);
    double b = GetRad(y1) - GetRad(y2);
    double s = 2 * asin(sqrt(pow(sin(a/2),2) + cos(GetRad(x1))*cos(GetRad(x2))*pow(sin(b/2),2)));
    s *= earth_radius;
    s = (long long)(s * 10000000) / 10000;
    return s;
}

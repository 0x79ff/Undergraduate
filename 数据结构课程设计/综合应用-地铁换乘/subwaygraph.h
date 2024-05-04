#ifndef SUBWAYGRAPH_H

#define SUBWAYGRAPH_H

#include "station.h"
#include <QString>
#include <QPoint>
#include <QVector>
#include <QHash>
#include <QColor>
#include <QPair>
#include <QSet>


//定义边类型
typedef QPair<int,int> Edge;

class SubwayGraph;
class QTextStream;

//线路类
class Line
{
protected:
    //储存线路相关信息
    int id;
    QString name;
    QColor color;
    QVector <QString> fromTo;
    QSet<int> stationsSet;
    QSet<Edge> edges;

public:
    //构造函数
    Line(){};
    Line(QString lineName, QColor lineColor):name(lineName), color(lineColor)
    {};

    //声明友元
    friend class SubwayGraph;
    friend class QTextStream;
};



class Node{
public:
    int stationID;      //邻接点ID
    double distance;    //两点距离

    //构造函数
    Node(){};
    Node(int s, double dist) :stationID(s), distance(dist){};

    bool operator > (const Node& n) const
    {
        return this->distance>n.distance;
    }
};

//后端管理类
class SubwayGraph
{
protected:
    QVector<Station> stations;          //存储所有站点
    QVector<Line> lines;                //存储所有线路
    QHash<QString, int> stationsHash;   //站点名到存储位置的hash
    QHash<QString, int> linesHash;      //线路名到存储位置的hash
    QSet<Edge> edges;                   //所有边的集合
    QVector<QVector<Node>> graph;       //地铁线路网络图

public:
    //构造函数
    SubwayGraph();

    QString getLineName(int l);
    QColor getLineColor(int l);
    int getLineHash(QString lineName);
    QList<int> getLinesHash(QList<QString> linesList);
    QList<QString> getLinesNameList();
    QList<QString> getLineStationsList(int l);



    QList<int> getStationLinesInfo(int s);
    QList<int> getCommonLines(int s1, int s2);
    int getStationHash(QString stationName);
    QList<QString> getStationsNameList();
    QString getStationName(int s);
    QPointF getStationCoord(int s);
    QPointF getMinCoord();
    QPointF getMaxCoord();


    //添加新线路
    void addLine(QString lineName, QColor color);
    void addStation(Station s);
    void addConnection(int s1, int s2, int l);

    //获取网络结构，用于前端显示
    void getGraph(QList<int>&stationsList, QList<Edge>&edgesList);

    bool queryTransferMinTime(int x, int y,QList<int>&stationsList,QList<Edge>&edgesList);
    bool queryTransferMinTransfer(int x, int y,QList<int>&stationsList,QList<Edge>&edgesList);

    bool readFileData(QString fileName);

private:
    //清空数据
    void clearData();
    //插入一条边
    bool insertEdge(int s1, int s2);
    //更新边界经纬度
    void updateMinMaxLongiLati();
    //生成图结构
    void makeGraph();
};

#endif // SUBWAYGRAPH_H

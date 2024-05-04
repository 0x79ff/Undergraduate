#include "subwaygraph.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <queue> //搜索用到队列

// 构造函数
SubwayGraph::SubwayGraph()
{
    // 构造函数，不执行特殊操作
}

// 从文件读取数据
bool SubwayGraph::readFileData(QString fileName)
{
    QFile file(fileName);

    // 只读方式打开文件，避免文件损坏
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        Line line;
        QString id, name, colour, fromTo, totalStations;
        QString color, froms, tos;
        bool ok;
        int total;
        Station station;
        int lvIndex, svIndex1, svIndex2;

        // 读取地铁线路数据
        in >> id >> line.id;
        in >> name >> line.name;
        in >> colour >> color;
        line.color.setRgba(color.remove(0, 1).toUInt(&ok, 16));
        in >> fromTo >> froms >> tos;
        in >> totalStations >> total;

        line.fromTo.push_back(froms);
        line.fromTo.push_back(tos);

        // 如果线路名称已存在，则更新线路数据，否则添加新线路
        if (linesHash.count(line.name))
        {
            lvIndex = linesHash[line.name];
            lines[lvIndex].fromTo.push_back(froms);
            lines[lvIndex].fromTo.push_back(tos);
        }
        else
        {
            lvIndex = linesHash[line.name] = lines.size();
            lines.push_back(line);
        }

        QString longlat;
        QStringList strList;

        // 读取地铁站点数据
        for (int i = 0; !in.atEnd() && i < total; ++i)
        {
            in >> station.id >> station.name >> longlat;
            strList = longlat.split(QChar(','));
            station.longitude = strList.first().toDouble();
            station.latitude = strList.last().toDouble();

            if (stationsHash.count(station.name))
            {
                svIndex2 = stationsHash[station.name];
            }
            else
            {
                svIndex2 = stationsHash[station.name] = stations.size();
                stations.push_back(station);
            }

            stations[svIndex2].linesInfo.insert(lvIndex);
            lines[lvIndex].stationsSet.insert(svIndex2);

            if (i)
            {
                lines[lvIndex].edges.insert(Edge(svIndex1, svIndex2));
                lines[lvIndex].edges.insert(Edge(svIndex2, svIndex1));
                insertEdge(svIndex1, svIndex2);
            }
            svIndex1 = svIndex2;
        }

        // 检查文件格式是否正确
        bool flag = id == "id:" && name == "name:" && colour == "colour:" && fromTo == "fromTo:" && totalStations == "totalStations:" && ok && !in.atEnd();

        if (flag == false)
        {
            file.close();
            clearData();
            return false;
        }
        in.readLine();
    }

    file.close();

    updateMinMaxLongiLati();

    return true;
}

// 清空数据
void SubwayGraph::clearData()
{
    stations.clear();
    lines.clear();
    stationsHash.clear();
    linesHash.clear();
    edges.clear();
    graph.clear();
}

// 插入一条边
bool SubwayGraph::insertEdge(int x, int y)
{
    // 如果边(x, y)和边(y, x)都不存在，则插入边(x, y)
    if (!edges.contains(Edge(x, y)) && !edges.contains(Edge(y, x)))
    {
        edges.insert(Edge(x, y));
        return true;
    }
    return false;
}

// 生成图结构
void SubwayGraph::makeGraph()
{
    graph.clear();
    graph = QVector<QVector<Node>>(stations.size(), QVector<Node>());

    // 根据边的信息生成图的邻接表
    for (auto &a : edges)
    {
        double dist = stations[a.first].GetDistance(stations[a.second]);
        graph[a.first].push_back(Node(a.second, dist));
        graph[a.second].push_back(Node(a.first, dist));
    }
}

// 获取线路信息
QColor SubwayGraph::getLineColor(int x)
{
    return lines[x].color;
}

QString SubwayGraph::getLineName(int x)
{
    return lines[x].name;
}

int SubwayGraph::getLineHash(QString x)
{
    // 如果线路名称存在于哈希表中，返回线路索引，否则返回-1
    if (linesHash.contains(x))
    {
        return linesHash[x];
    }
    return -1;
}
// 获取线路哈希
QList<int> SubwayGraph::getLinesHash(QList<QString> x)
{
    QList<int> hashList;
    for (auto &a : x)
    {
        hashList.push_back(getLineHash(a));
    }
    return hashList;
}

// 获取线路名称列表
QList<QString> SubwayGraph::getLinesNameList()
{
    QList<QString> linesNameList;
    for (auto a : lines)
    {
        linesNameList.push_back(a.name);
    }
    return linesNameList;
}

// 获取线路对应站点列表
QList<QString> SubwayGraph::getLineStationsList(int l)
{
    QList<QString> stationsList;
    for (auto &a : lines[l].stationsSet)
    {
        stationsList.push_back(stations[a].name);
    }
    return stationsList;
}

// 更新最小和最大经纬度
void SubwayGraph::updateMinMaxLongiLati()
{
    double minLongitude = 200, minLatitude = 200;
    double maxLongitude = 0, maxLatitude = 0;

    for (auto &s : stations)
    {
        minLongitude = qMin(minLongitude, s.longitude);
        minLatitude = qMin(minLatitude, s.latitude);
        maxLongitude = qMax(maxLongitude, s.longitude);
        maxLatitude = qMax(maxLatitude, s.latitude);
    }
    Station::minLongitude = minLongitude;
    Station::minLatitude = minLatitude;
    Station::maxLongitude = maxLongitude;
    Station::maxLatitude = maxLatitude;
}

// 获取最大经纬度
QPointF SubwayGraph::getMaxCoord()
{
    return QPointF(Station::maxLongitude, Station::maxLatitude);
}

// 获取最小经纬度
QPointF SubwayGraph::getMinCoord()
{
    return QPointF(Station::minLongitude, Station::minLatitude);
}

// 获取两个站点的公共所属线路
QList<int> SubwayGraph::getCommonLines(int s1, int s2)
{
    QList<int> linesList;
    for (auto &s : stations[s1].linesInfo)
    {
        if (stations[s2].linesInfo.contains(s))
            linesList.push_back(s);
    }
    return linesList;
}

// 获取站点名称
QString SubwayGraph::getStationName(int s)
{
    return stations[s].name;
}

// 获取站点哈希值
int SubwayGraph::getStationHash(QString stationName)
{
    if (stationsHash.contains(stationName))
    {
        return stationsHash[stationName];
    }
    return -1;
}

// 获取站点名称列表
QList<QString> SubwayGraph::getStationsNameList()
{
    QList<QString> list;
    for (auto &a : stations)
    {
        list.push_back(a.name);
    }
    return list;
}

// 获取站点坐标
QPointF SubwayGraph::getStationCoord(int s)
{
    return QPointF(stations[s].longitude, stations[s].latitude);
}

// 获取站点所属线路信息
QList<int> SubwayGraph::getStationLinesInfo(int s)
{
    return stations[s].linesInfo.toList();
}



// 动态添加线路
void SubwayGraph::addLine(QString lineName, QColor color)
{
    // 在哈希表中添加线路名对应的索引
    linesHash[lineName] = lines.size();
    // 在线路列表中添加新线路
    lines.push_back(Line(lineName, color));
}

// 动态添加站点
void SubwayGraph::addStation(Station s)
{
    // 获取新站点的哈希值
    int hash = stations.size();
    // 在哈希表中添加站点名对应的索引
    stationsHash[s.name] = hash;
    // 在站点列表中添加新站点
    stations.push_back(s);

    // 更新线路信息
    for (auto &a : s.linesInfo)
    {
        lines[a].stationsSet.insert(hash);
    }

    // 更新最小和最大经纬度
    updateMinMaxLongiLati();
}

// 动态添加连接
void SubwayGraph::addConnection(int s1, int s2, int l)
{
    // 插入边(s1, s2)
    insertEdge(s1, s2);

    // 在线路l中添加边(s1, s2)和边(s2, s1)
    lines[l].edges.insert(Edge(s1, s2));
    lines[l].edges.insert(Edge(s2, s1));
}

// 获取图结构
void SubwayGraph::getGraph(QList<int>& stationsList, QList<Edge>& edgesList)
{
    // 清空输出参数
    stationsList.clear();

    // 将所有站点的索引添加到输出列表中
    for (int i = 0; i < stations.size(); ++i)
    {
        stationsList.push_back(i);
    }

    // 将所有边添加到输出列表中
    edgesList = edges.toList();
    return;
}

const double INF = 1e9+7;

//不同方式的线路搜索
bool SubwayGraph::queryTransferMinTransfer(int x, int y, QList<int>& stationsList, QList<Edge>& edgesList)
{
    // 清空输出参数
    edgesList.clear();
    stationsList.clear();

    // 如果起始站和目标站相同，直接添加到输出列表中并返回
    if (x == y)
    {
        stationsList.push_back(y);
        stationsList.push_back(x);
        return true;
    }

    // 记录每条线路是否被访问过
    std::vector<bool> lineVisited(lines.size(), false);

    // 记录最短换乘路径的前驱节点
    std::vector<int> prev(stations.size(), -1);

    // 起始站的前驱节点设置为-2，表示起始站点
    prev[x] = -2;

    // 使用队列实现广度优先搜索
    std::queue<int> queue;
    queue.push(x);

    // 开始广度优先搜索
    while (!queue.empty())
    {
        int currentStation = queue.front();
        queue.pop();

        // 遍历当前站点所属的线路
        for (auto &line : stations[currentStation].linesInfo)
        {
            if (!lineVisited[line])
            {
                lineVisited[line] = true;

                // 遍历当前线路的所有站点
                for (auto &nextStation : lines[line].stationsSet)
                {
                    if (prev[nextStation] == -1)
                    {
                        // 更新前驱节点，将当前站点设置为前驱节点
                        prev[nextStation] = currentStation;
                        queue.push(nextStation);
                    }
                }
            }
        }
    }

    // 如果目标站点不可达，返回false
    if (prev[y] == -1)
    {
        return false;
    }

    // 从目标站点回溯构建最短换乘路径
    int p = y;
    while (prev[p] != -2)
    {
        stationsList.push_front(p);
        edgesList.push_front(Edge(prev[p], p));
        p = prev[p];
    }

    // 添加起始站点到路径
    stationsList.push_front(x);
    return true;
}



bool SubwayGraph::queryTransferMinTime(int x, int y, QList<int>& stationsList, QList<Edge>& edgesList)
{
    // 清空输出参数
    edgesList.clear();
    stationsList.clear();

    // 如果起始站和目标站相同，直接添加到输出列表中并返回
    if (x == y)
    {
        stationsList.push_back(y);
        stationsList.push_back(x);
        return true;
    }

    // 构建地铁网络图，假设这里是 makeGraph() 函数的调用
    makeGraph();

    // 用于存储最短路径的前驱节点和最短距离
    std::vector<int> prev(stations.size(), -1); // 存储前驱节点
    std::vector<double> minDist(stations.size(), INF); // 存储最短距离

    // 起始站点的最短距离设为0
    minDist[x] = 0;

    // 使用优先队列来实现Dijkstra算法
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push(Node(x, 0));

    // 开始Dijkstra算法主循环
    while (!pq.empty())
    {
        // 弹出队列中距离最小的节点
        Node top = pq.top();
        pq.pop();

        // 如果当前节点是目标节点，退出循环
        if (top.stationID == y)
        {
            break;
        }

        // 遍历当前节点的邻接节点
        for (int i = 0; i < graph[top.stationID].size(); ++i)
        {
            Node &adjNode = graph[top.stationID][i];

            // 如果经过当前节点到达邻接节点的距离更短，则更新前驱节点和最短距离
            if (top.distance + adjNode.distance < minDist[adjNode.stationID])
            {
                prev[adjNode.stationID] = top.stationID;
                minDist[adjNode.stationID] = top.distance + adjNode.distance;
                pq.push(Node(adjNode.stationID, minDist[adjNode.stationID]));
            }
        }
    }

    // 如果目标站点不可达，返回false
    if (prev[y] == -1)
    {
        return false;
    }

    // 从目标站点回溯构建最短路径
    int p = y;
    while (prev[p] != -1)
    {
        stationsList.push_front(p);
        edgesList.push_front(Edge(prev[p], p));
        p = prev[p];
    }
    stationsList.push_front(x); // 添加起始站点到路径

    return true;
}




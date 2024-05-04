#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include "subwaygraph.h"
#include "managelines.h"
#include "help.h"
#include "mouseviewzoom.h"


#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>



#define LINE_INFO_WIDTH 0   //预留边框用于信息展示
#define MARGIN 30           //视图左边距
#define NET_WIDTH 2000      //网络图最大宽度
#define NET_HEIGHT 2000     //网络图最大高度
#define SCENE_WIDTH (LINE_INFO_WIDTH+MARGIN*2+NET_WIDTH)    //视图宽度
#define SCENE_HEIGHT (MARGIN*2+NET_HEIGHT)                  //视图高度

#define EDGE_PEN_WIDTH 2    //线路边宽
#define NODE_HALF_WIDTH 3   //节点大小


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    //换乘查询槽函数
    void updateTranserQueryInfo();
    void transferStartLineChanged(QString lineName);
    void transferDstLineChanged(QString lineNames);
    void transferQuery();
    //6个顶部按钮的槽函数
    void on_actionAddLine_triggered();
    void on_actionAddStation_triggered();
    void on_actionAddConnect_triggered();
    void on_actionAddByText_triggered();
    void on_actionLineMap_triggered();
    void on_actionuseHelp_triggered();
    //添加列表视图部件变化槽函数
    void tabWidgetCurrentChanged(int index);
    //动态添加槽函数
    void addLine();
    void addStation();
    void addConnection();
    void addByText();


protected:
    Ui::MainWindow *ui;             //主窗口UI
    Graphics_view_zoom *myView;     //自定义视图，用于鼠标缩放
    QGraphicsScene *scene;          //场景
    SubwayGraph* subwayGraph;       //后端管理类
    ManageLines* manageLines;       //添加功能前端管理类
    AppHelp* appHelp;               //帮助显示类

    //绘制网络图的边
    void drawEdges (const QList<Edge>& edgesList);
    //绘制网络图的站点节点
    void drawStations (const QList<int>& stationsList);
    //由线路表计算混合颜色
    QColor getLinesColor(const QList<int>& linesList);
    //获得线路表的名字集
    QString getLinesName(const QList<int>& linesList);
    //将站点的经纬度地理坐标转为视图坐标
    QPointF transferCoord(QPointF coord);


private:
    void MainConnect();
};



#endif // MAINWINDOW_H

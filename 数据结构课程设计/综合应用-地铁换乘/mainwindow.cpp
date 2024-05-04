#include "ui_mainwindow.h"
#include "ui_managelines.h"
#include "mainwindow.h"

#include <QGraphicsItem>
#include <QMessageBox>
#include <QColorDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 创建UI窗口
    ui->setupUi(this);

    // 初始化图形视图和场景
    myView = new Graphics_view_zoom(ui->graphicsView);
    myView->set_modifiers(Qt::NoModifier);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene = new QGraphicsScene;
    scene->setSceneRect(-LINE_INFO_WIDTH, 0, SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    // 初始化管理线路、地铁图和应用帮助对象
    manageLines = new ManageLines(this);
    subwayGraph = new SubwayGraph;
    appHelp = new AppHelp();

    // 从文件读取数据，读取失败则显示提示
    bool flag = subwayGraph->readFileData(":/data/data/SubwayInfo.txt");
    if (flag == false)
    {
        QMessageBox box;
        box.setWindowTitle(tr("错误信息"));
        box.setIcon(QMessageBox::Warning);
        box.setText("读取数据错误，请检查文件!\n");
        box.addButton(tr("确定"), QMessageBox::AcceptRole);
        if (box.exec() == QMessageBox::Accepted)
        {
            box.close();
        }
    }

    // 连接信号和槽函数
    MainConnect();

    // 更新换乘查询信息
    updateTranserQueryInfo();

    // 初始状态下加载地铁线路图
    on_actionLineMap_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myView;
    delete scene;
    delete subwayGraph;
    delete manageLines;
    delete appHelp;
}

// 连接信号和槽函数
void MainWindow::MainConnect()
{
    // ... 其他信号和槽的连接

    connect(ui->comboBoxDstLine, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(transferDstLineChanged(QString)));
    connect(ui->pushButtonTransfer, SIGNAL(clicked()), this, SLOT(transferQuery()));
}

QString MainWindow::getLinesName(const QList<int>& linesList)
{
    QString str;
    str += "\t";
    for (int i = 0; i < linesList.size(); ++i)
    {
        str += " ";
        str += subwayGraph->getLineName(linesList[i]);
    }

    return str;
}

// 混合颜色
QColor MainWindow::getLinesColor(const QList<int>& linesList)
{
    QColor re = QColor(255, 255, 255);
    QColor t;
    for (int i = 0; i < linesList.size(); ++i)
    {
        t = subwayGraph->getLineColor(linesList[i]);
        re.setRed(re.red() * t.red() / 255);
        re.setGreen(re.green() * t.green() / 255);
        re.setBlue(re.blue() * t.blue() / 255);
    }
    return re;
}


QPointF MainWindow::transferCoord(QPointF coord)
{
    // 将地理坐标映射到视图坐标
    QPointF minCoord = subwayGraph->getMinCoord();
    QPointF maxCoord = subwayGraph->getMaxCoord();

    // 计算视图坐标中的x和y值
    double x = (coord.x() - minCoord.x()) / (maxCoord.x() - minCoord.x()) * NET_WIDTH + MARGIN;
    double y = (maxCoord.y() - coord.y()) / (maxCoord.y() - minCoord.y()) * NET_HEIGHT + MARGIN;

    return QPointF(x, y);
}

// 绘制网络图的边
void MainWindow::drawEdges(const QList<Edge>& edgesList)
{
    for(int i = 0; i < edgesList.size(); ++i)
    {
        int x = edgesList[i].first;
        int y = edgesList[i].second;

        // 获取连接这两个站点的线路列表
        QList<int> linesList = subwayGraph->getCommonLines(x, y);

        // 获取混合颜色以表示线路之间的连接
        QColor color = getLinesColor(linesList);

        // 准备工具提示文本，显示站点连接和线路信息
        QString tip = "途经： " + subwayGraph->getStationName(x) + "--" + subwayGraph->getStationName(y) + "\n线路：";
        tip += getLinesName(linesList);

        // 获取起始站点和结束站点的视图坐标
        QPointF xPos = transferCoord(subwayGraph->getStationCoord(x));
        QPointF yPos = transferCoord(subwayGraph->getStationCoord(y));

        // 创建并配置边的图形项
        QGraphicsLineItem* edgeItem = new QGraphicsLineItem;
        edgeItem->setPen(QPen(color, EDGE_PEN_WIDTH));
        edgeItem->setCursor(Qt::PointingHandCursor);
        edgeItem->setToolTip(tip);
        edgeItem->setPos(xPos);
        edgeItem->setLine(0, 0, yPos.x() - xPos.x(), yPos.y() - xPos.y());

        // 将边添加到场景中
        scene->addItem(edgeItem);
    }
}

// 绘制网络图的站点节点
void MainWindow::drawStations(const QList<int>& stationsList)
{
    for (int i = 0; i < stationsList.size(); ++i)
    {
        int s = stationsList[i];
        QString name = subwayGraph->getStationName(s);

        // 获取站点所属的线路列表
        QList<int> linesList = subwayGraph->getStationLinesInfo(s);

        // 获取混合颜色以表示站点所属线路
        QColor color = getLinesColor(linesList);

        // 获取站点的地理坐标
        QPointF longiLati = subwayGraph->getStationCoord(s);

        // 获取站点的视图坐标
        QPointF coord = transferCoord(longiLati);

        // 准备工具提示文本，显示站点信息和所属线路
        QString tip = "站名：  " + name + "\n" +
                "经度：  " + QString::number(longiLati.x(), 'f', 7) + "\n" +
                "纬度：  " + QString::number(longiLati.y(), 'f', 7) + "\n" +
                "线路：" + getLinesName(linesList);

        // 创建并配置站点节点的图形项
        QGraphicsEllipseItem* stationItem = new QGraphicsEllipseItem;
        stationItem->setRect(-NODE_HALF_WIDTH, -NODE_HALF_WIDTH, NODE_HALF_WIDTH << 1, NODE_HALF_WIDTH << 1);
        stationItem->setPos(coord);
        stationItem->setPen(color);
        stationItem->setCursor(Qt::PointingHandCursor);
        stationItem->setToolTip(tip);

        // 如果站点只属于一个线路，用白色填充
        if (linesList.size() <= 1)
        {
            stationItem->setBrush(QColor(QRgb(0xffffff)));
        }

        // 添加站点节点到场景
        scene->addItem(stationItem);

        // 创建站点名称的图形项并添加到场景
        QGraphicsTextItem* textItem = new QGraphicsTextItem;
        textItem->setPlainText(name);
        textItem->setFont(QFont("consolas", 4, 1));
        textItem->setPos(coord.x(), coord.y() - NODE_HALF_WIDTH * 2);
        scene->addItem(textItem);
    }
}

// 更新换乘选择信息
void MainWindow::updateTranserQueryInfo()
{
    // 获取起始线路和目的线路的下拉框
    QComboBox* comboL1 = ui->comboBoxStartLine;
    QComboBox* comboL2 = ui->comboBoxDstLine;

    // 清空下拉框内容
    comboL1->clear();
    comboL2->clear();

    // 获取地铁线路的名称列表
    QList<QString> linesList = subwayGraph->getLinesNameList();
    for (auto& lineName : linesList)
    {
        // 将线路名称添加到下拉框
        comboL1->addItem(lineName);
        comboL2->addItem(lineName);
    }

    // 更新起始线路和目的线路的站点列表
    transferStartLineChanged(comboL1->itemText(0));
    transferDstLineChanged(comboL2->itemText(0));
}

// 换乘出发线路改变槽函数
void MainWindow::transferStartLineChanged(QString lineName)
{
    // 获取起始站点的下拉框
    QComboBox* comboS1 = ui->comboBoxStartStation;
    comboS1->clear();

    // 获取线路的哈希值
    int lineHash = subwayGraph->getLineHash(lineName);
    if (lineHash == -1)
    {
        return;
    }

    // 获取指定线路的站点列表
    QList<QString> stationsList = subwayGraph->getLineStationsList(lineHash);
    for (auto& stationName : stationsList)
    {
        // 将站点名称添加到下拉框
        comboS1->addItem(stationName);
    }
}

// 换乘目的线路改变槽函数
void MainWindow::transferDstLineChanged(QString lineName)
{
    // 获取目的站点的下拉框
    QComboBox* comboS2 = ui->comboBoxDstStation;
    comboS2->clear();

    // 获取线路的哈希值
    int lineHash = subwayGraph->getLineHash(lineName);
    if (lineHash == -1)
    {
        return;
    }

    // 获取指定线路的站点列表
    QList<QString> stationsList = subwayGraph->getLineStationsList(lineHash);
    for (auto& stationName : stationsList)
    {
        // 将站点名称添加到下拉框
        comboS2->addItem(stationName);
    }
}

// 换乘查询槽函数
void MainWindow::transferQuery()
{
    // 获取起始站点和目的站点的哈希值
    int s1 = subwayGraph->getStationHash(ui->comboBoxStartStation->currentText());
    int s2 = subwayGraph->getStationHash(ui->comboBoxDstStation->currentText());

    // 获取用户选择的查询方式（时间最短或换乘最少）
    int way = ui->radioButtonMinTime->isChecked() ? 1 : 2;

    if (s1 == -1 || s2 == -1)
    {
        // 如果起始站点或目的站点无效，显示错误提示
        QMessageBox box;
        box.setWindowTitle(tr("换乘查询"));
        box.setWindowIcon(QIcon(":/icon/icon/query.png"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("请选择有站点的线路"));
        box.addButton(tr("确定"), QMessageBox::AcceptRole);
        if (box.exec() == QMessageBox::Accepted)
        {
            box.close();
        }
    }
    else
    {
        QList<int> stationsList;
        QList<Edge> edgesList;
        bool flag = true;
        if (way == 1)
        {
            // 查询时间最短的换乘方案
            flag = subwayGraph->queryTransferMinTime(s1, s2, stationsList, edgesList);
        }
        else
        {
            // 查询换乘最少的换乘方案
            flag = subwayGraph->queryTransferMinTransfer(s1, s2, stationsList, edgesList);
        }

        if (flag)
        {
            // 如果找到了换乘方案，清空场景并绘制新的路线和站点
            scene->clear();
            drawEdges(edgesList);
            drawStations(stationsList);

            // 构建并显示换乘路线信息
            QString text = way == 1 ? ("以下线路时间最短，共换乘" + QString::number(stationsList.size() - 1) + "个站点\n\n") :
                ("以下线路换乘最少，共换乘" + QString::number(stationsList.size() - 1) + "条线路\n\n");
            for (int i = 0; i < stationsList.size(); ++i)
            {
                if (i)
                {
                    text += "\n  ↓\n";
                }
                text += subwayGraph->getStationName(stationsList[i]);
                QString linesStr = getLinesName(subwayGraph->getStationLinesInfo(stationsList[i]));
                text += linesStr;
            }
            QTextBrowser* browser = ui->textBrowserRoute;
            browser->clear();
            browser->setText(text);
        }
        else
        {
            // 如果未找到换乘方案，显示错误提示
            QMessageBox box;
            box.setWindowTitle(tr("换乘查询"));
            box.setWindowIcon(QIcon(":/icon/icon/query.png"));
            box.setIcon(QMessageBox::Warning);
            box.setText(tr("您选择的起始和终止站点暂时无法到达！"));
            box.addButton(tr("确定"), QMessageBox::AcceptRole);
            if (box.exec() == QMessageBox::Accepted)
            {
                box.close();
            }
       }
   }
}
// 添加列表视图部件变化槽函数
void MainWindow::tabWidgetCurrentChanged(int index)
{
    // 获取当前的部件
    QWidget* widget = manageLines->ui->tabWidget->currentWidget();

    if (widget == manageLines->tabWigetsVector[1])
    {
        // 当前部件为线路列表部件
        manageLines->linesNameList = subwayGraph->getLinesNameList();
        manageLines->updateLinesListWidget();
    }
    else if (widget == manageLines->tabWigetsVector[2])
    {
        // 当前部件为连接站点部件
        manageLines->linesNameList = subwayGraph->getLinesNameList();
        manageLines->stationsNameList = subwayGraph->getStationsNameList();
        manageLines->ui->comboBoxConnectStation1->setMaxCount(manageLines->stationsNameList.size());
        manageLines->ui->comboBoxConnectStation2->setMaxCount(manageLines->stationsNameList.size());
        manageLines->ui->comboBoxConnectLine->setMaxCount(manageLines->linesNameList.size());
        manageLines->updateComboBox();
    }
    Q_UNUSED(index);
}

// 添加线路的槽函数
void MainWindow::addLine()
{
    QMessageBox box;
    box.setWindowTitle(tr("添加线路"));
    box.setWindowIcon(QIcon(":/icon/icon/subway.png"));

    if (manageLines->lineName.isEmpty())
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("请输入线路名称！"));
    }
    else if (subwayGraph->getLineHash(manageLines->lineName) == -1)
    {
        // 添加线路成功的情况
        box.setIcon(QMessageBox::Information);
        box.setText(tr("线路：") + manageLines->lineName + tr(" 添加成功！"));
        subwayGraph->addLine(manageLines->lineName, manageLines->lineColor);
        updateTranserQueryInfo();
    }
    else
    {
        // 添加线路失败的情况
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("添加失败！\n错误原因：线路名已存在！"));
    }

    box.addButton(tr("确定"), QMessageBox::AcceptRole);
    if (box.exec() == QMessageBox::Accepted)
    {
        box.close();
    }
    updateTranserQueryInfo();
}

// 添加连接的槽函数
void MainWindow::addConnection()
{
    // 获取连接信息
    QString station1 = manageLines->ui->comboBoxConnectStation1->currentText();
    QString station2 = manageLines->ui->comboBoxConnectStation2->currentText();
    int s1 = subwayGraph->getStationHash(station1);
    int s2 = subwayGraph->getStationHash(station2);
    int l = subwayGraph->getLineHash(manageLines->ui->comboBoxConnectLine->currentText());

    QMessageBox box;
    box.setWindowTitle(tr("添加连接"));
    box.setWindowIcon(QIcon(":/icon/icon/connect.png"));

    if (s1 == -1 || s2 == -1 || l == -1)
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("请选择已有的站点和线路！"));
    }
    else if (s1 == s2)
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("同一站点不需要连接！"));
    }
    else if (!subwayGraph->getStationLinesInfo(s1).contains(l))
    {
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("连接失败！\n错误原因：所属线路不包含站点1"));
    }
    else if (!subwayGraph->getStationLinesInfo(s2).contains(l))
    {
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("连接失败！\n错误原因：所属线路不包含站点2"));
    }
    else
    {
        // 添加连接成功的情况
        box.setIcon(QMessageBox::Information);
        box.setText(tr("添加连接成功！"));
        subwayGraph->addConnection(s1, s2, l);
    }
    if (box.exec() == QMessageBox::Accepted)
    {
        box.close();
    }
    updateTranserQueryInfo();
    on_actionLineMap_triggered();
}

// 通过文本添加信息的槽函数
void MainWindow::addByText()
{
    QString writeFile = "userAdd.txt";
    QFile file(writeFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "提示", "无法创建添加文件");
        return;
    }
    QTextStream out(&file);
    out << manageLines->ui->textEdit->toPlainText();
    file.close();

    QMessageBox box;
    box.setWindowTitle(tr("文本添加"));
    box.setWindowIcon(QIcon(":/icon/icon/add.png"));

    bool flag = subwayGraph->readFileData(writeFile);
    if (flag)
    {
        // 添加成功的情况
        box.setIcon(QMessageBox::Information);
        box.setText(tr("添加成功"));
    }
    else
    {
        // 添加失败的情况
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("添加失败，数据被擦除！"));
    }
    box.addButton(tr("确定"), QMessageBox::AcceptRole);
    if (box.exec() == QMessageBox::Accepted)
    {
        box.close();
    }
    updateTranserQueryInfo();
    on_actionLineMap_triggered();
    return;
}

// 添加站点的槽函数
void MainWindow::addStation()
{
    QMessageBox box;
    box.setWindowTitle(tr("添加站点"));
    box.setWindowIcon(QIcon(":/icon/icon/station.png"));

    if (manageLines->stationName.isEmpty())
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("请输入站点名称！"));
    }
    else if (manageLines->linesSelected.isEmpty())
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("请选择站点所属线路！"));
    }
    else
    {
        if (subwayGraph->getStationHash(manageLines->stationName) != -1)
        {
            // 添加站点失败的情况
            box.setIcon(QMessageBox::Critical);
            box.setText(tr("添加失败！\n错误原因：站点已存在！"));
        }
        else
        {
            // 添加站点成功的情况
            Station s(manageLines->stationName, manageLines->longitude, manageLines->latitude,
                      subwayGraph->getLinesHash(manageLines->linesSelected));
            subwayGraph->addStation(s);
            box.setText(tr("站点：") + manageLines->stationName + tr(" 添加成功！"));
            updateTranserQueryInfo();
        }
    }

    box.addButton(tr("确定"), QMessageBox::AcceptRole);
    if (box.exec() == QMessageBox::Accepted)
    {
        box.close();
    }
    updateTranserQueryInfo();
    on_actionLineMap_triggered();
}


//Help
void MainWindow::on_actionuseHelp_triggered()
{
    appHelp->show();
}


//动态添加槽函数
void MainWindow::on_actionAddLine_triggered()
{
    manageLines->setAddLineVisible();
    manageLines->show();
}

void MainWindow::on_actionAddStation_triggered()
{
    manageLines->setAddStationVisible();
    manageLines->show();
}

void MainWindow::on_actionAddConnect_triggered()
{
    manageLines->setAddConnectionVisible();
    manageLines->show();
}

void MainWindow::on_actionAddByText_triggered()
{
    manageLines->setAddByTextVisible();
    manageLines->show();
}


void MainWindow::on_actionLineMap_triggered()
{
    scene->clear();
    QList<int> stationsList;
    QList<Edge> edgesList;
    subwayGraph->getGraph(stationsList,edgesList);
    drawEdges(edgesList);
    drawStations(stationsList);
}


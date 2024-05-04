#include "ui_managelines.h"
#include "managelines.h"

#include <QPixmap>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//构造函数
ManageLines::ManageLines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageLines)
{
    ui->setupUi(this);
    tabWigetsVector.push_back(ui->tabAddLine);
    tabWigetsVector.push_back(ui->tabAddStation);
    tabWigetsVector.push_back(ui->tabAddConnection);
    tabWigetsVector.push_back(ui->tabAddByText);

    tabIconVector.push_back(QIcon(QPixmap(":/icon/icon/subway.png")));
    tabIconVector.push_back(QIcon(QPixmap(":/icon/icon/station.png")));
    tabIconVector.push_back(QIcon(QPixmap(":/icon/icon/connect.png")));
    tabIconVector.push_back(QIcon(QPixmap(":/icon/icon/text.png")));

    tabTextVector.push_back("线路");
    tabTextVector.push_back("站点");
    tabTextVector.push_back("连接");
    tabTextVector.push_back("文本方式");

    QString outputtext;
    outputtext+=tr("使用此文本快捷方式需严格按照如下格式\n");
    outputtext+=tr("具体信息可见DemoInput.txt\n");

    QFile file(":/data/data/DemoInput.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString str=in.readLine();
            outputtext+="\n";
            outputtext+=str;
        }
        file.close();
        ui->textEdit->setPlaceholderText(outputtext);

    }
    else
    {
         outputtext=file.errorString();
    }
}

//析构函数
ManageLines::~ManageLines()
{
    delete ui;
}

//根据选择不同呈现不同的添加界面
void ManageLines::setAddConnectionVisible()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(tabWigetsVector[2],tabIconVector[2],tabTextVector[2]);
}
void ManageLines::setAddLineVisible()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(tabWigetsVector[0],tabIconVector[0],tabTextVector[0]);
}
void ManageLines::setAddStationVisible()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(tabWigetsVector[1],tabIconVector[1],tabTextVector[1]);
}

void ManageLines::setAddByTextVisible()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(tabWigetsVector[3],tabIconVector[3],tabTextVector[3]);
}


//更新线路列表信息
void ManageLines::updateLinesListWidget()
{
    QListWidget* listWidget=ui->listWidget;
    for(int i=0; i<linesNameList.size(); ++i)
    {
        QListWidgetItem *item =listWidget->takeItem(i);
        delete item;
    }
    listWidget->clear();
    linesSelected.clear();
    ui->textBrowserLinesSelected->clear();

    for(int i=0; i<linesNameList.size(); ++i)
    {
        QListWidgetItem *item=new QListWidgetItem(linesNameList[i]);
        item->setFlags(item->flags()|Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        listWidget->addItem(item);
    }
}

//更新选择部件
void ManageLines::updateComboBox()
{
    ui->comboBoxConnectStation1->clear();
    ui->comboBoxConnectStation2->clear();
    ui->comboBoxConnectLine->clear();

    for (auto &a: stationsNameList)
    {
        ui->comboBoxConnectStation1->addItem(a);
        ui->comboBoxConnectStation2->addItem(a);
    }
    for (auto &a: linesNameList)
    {
        ui->comboBoxConnectLine->addItem(a);
    }
}


//添加线路部分
void ManageLines::on_lineEditLineName_textChanged(const QString &x)
{
    lineName=x;
}
void ManageLines::on_pushButtonChooseColor_clicked()
{
    QColorDialog colorDialog;
    colorDialog.setOptions(QColorDialog::ShowAlphaChannel);
    colorDialog.exec();
    lineColor=colorDialog.currentColor();
    return ;
}

//添加站点部分
void ManageLines::on_lineEditStationName_textChanged(const QString &x)
{
    stationName=x;
}
void ManageLines::on_doubleSpinBoxLatitude_valueChanged(double x)
{
    latitude=x;
}
void ManageLines::on_doubleSpinBoxLongitude_valueChanged(double x)
{
    longitude=x;
}


//列表部件选择项改变
void ManageLines::on_listWidget_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    QString str;
    linesSelected.clear();

    for (int i=0; i<ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item=ui->listWidget->item(i);
        if(item->checkState()==Qt::Checked)
        {
            linesSelected.push_back(item->text());
            str+=item->text();
            str+="\n";
        }
    }
    ui->textBrowserLinesSelected->setText(str);
}


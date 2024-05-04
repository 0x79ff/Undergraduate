#ifndef MANAGELINES_H

#define MANAGELINES_H

#include <QDialog>
#include <QVector>
#include <QTabWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QString>

class MainWindow;

namespace Ui {
class ManageLines;
}

class ManageLines : public QDialog
{
    Q_OBJECT

private slots:
    void on_doubleSpinBoxLatitude_valueChanged(double x);
    void on_doubleSpinBoxLongitude_valueChanged(double x);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_lineEditLineName_textChanged(const QString &x);
    void on_pushButtonChooseColor_clicked();
    void on_lineEditStationName_textChanged(const QString &x);


public:
    explicit ManageLines(QWidget *parent = 0);
    ~ManageLines();

    //设置不同部件可见
    void setAddLineVisible();
    void setAddStationVisible();
    void setAddConnectionVisible();
    void setAddByTextVisible();

    void updateLinesListWidget();
    void updateComboBox();

protected:
    Ui::ManageLines *ui;
    QVector<QWidget*> tabWigetsVector;  //保存tab部件指针
    QVector<QIcon> tabIconVector;       //保存tab部件Icon
    QVector<QString> tabTextVector;     //保存tab部件标题

    QList<QString> linesNameList,linesSelected,stationsNameList;
    QString lineName,stationName;
    QColor lineColor;
    double longitude,latitude;


    //声明友元
    friend class MainWindow;
};

#endif // MANAGELINES_H

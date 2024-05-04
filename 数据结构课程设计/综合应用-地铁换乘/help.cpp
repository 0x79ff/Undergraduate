#include "help.h"

#include <QIcon>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <QFile>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>

AppHelp::AppHelp(QWidget *parent):QWidget(parent)
{
    //创建新界面
    CreateHelpWindow();

    //设置标题 图标以及大小
    setWindowTitle(tr("程序使用说明"));
    setWindowIcon(QIcon(":/icon/icon/help.png"));
    setFixedSize(650,450);


    QDesktopWidget computer_desktop;
    QRect rect = computer_desktop.availableGeometry(computer_desktop.primaryScreen());
    QPoint target = rect.center();

    target.setX(target.x() - this->width()/2);
    target.setY(target.y() - this->height()/2);
    move(target);

    connect(help_left, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(listWidgetChanged(QListWidgetItem*)));
}


void AppHelp::CreateHelpWindow()
{
    QHBoxLayout *help_main = new QHBoxLayout;
    setLayout(help_main);

    help_left = new QListWidget;
    help_left->addItem(tr("地铁网络图及地铁换乘"));
    help_left->addItem(tr("关于动态添加"));
    help_left->setFixedWidth(160);

    QVBoxLayout *help_right = new QVBoxLayout;
    html_content = new QTextBrowser;
    html_content->setFont(QFont("consolas"));
    html_content->setOpenLinks(true);
    html_content->setOpenExternalLinks(true);

    //各部分组合起来
    help_right->addWidget(html_content);

    help_main->addWidget(help_left);
    help_main->addLayout(help_right);

    help_left->setCurrentItem(help_left->item(0));
    listWidgetChanged(help_left->item(0));
}



void AppHelp::listWidgetChanged(QListWidgetItem* item) {
    QString htmlfile_path;
    if(help_left->item(0) == item){
        htmlfile_path = ":/html/html/ViewAndQuery.html";
    }
    else{
        htmlfile_path = ":/html/html/DynamicAddition.html";
    }

    QFile htmlfile(htmlfile_path);
    htmlfile.open(QIODevice::ReadOnly);
    html_content->setHtml(htmlfile.readAll());
    htmlfile.close();

}

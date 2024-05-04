#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QTime>
#include <QPixmap>
#include <qthread.h>

//sleep函数用来使程序暂停
void sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
        QApplication::processEvents(QEventLoop::AllEvents,100);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置启动图标 显示2s
    QPixmap splash(":/icon/icon/splash.png");
    QSplashScreen splashScreen(splash);
    splashScreen.show();
    sleep(2000);


    //进入主界面
    MainWindow w;
    w.show();

    splashScreen.finish(&w);

    return a.exec();
}

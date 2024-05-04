/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddLine;
    QAction *actionAddStation;
    QAction *actionAddConnect;
    QAction *actionAddByText;
    QAction *actiontoolBar;
    QAction *actionLineMap;
    QAction *actionWheel;
    QAction *actionuseHelp;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTransfer;
    QHBoxLayout *horizontalLayout4;
    QLabel *labelStart;
    QComboBox *comboBoxStartLine;
    QComboBox *comboBoxStartStation;
    QHBoxLayout *horizontalLayout5;
    QLabel *labelDestination;
    QComboBox *comboBoxDstLine;
    QComboBox *comboBoxDstStation;
    QHBoxLayout *horizontalLayout6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonMinTransfer;
    QRadioButton *radioButtonMinTime;
    QPushButton *pushButtonTransfer;
    QLabel *labelTransferRoute;
    QTextBrowser *textBrowserRoute;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu_H;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1030, 684);
        MainWindow->setMinimumSize(QSize(1030, 680));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/metro-shanghai.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(24, 24));
        actionAddLine = new QAction(MainWindow);
        actionAddLine->setObjectName(QString::fromUtf8("actionAddLine"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/subway.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddLine->setIcon(icon1);
        actionAddLine->setFont(font);
        actionAddStation = new QAction(MainWindow);
        actionAddStation->setObjectName(QString::fromUtf8("actionAddStation"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icon/station.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddStation->setIcon(icon2);
        actionAddStation->setFont(font);
        actionAddConnect = new QAction(MainWindow);
        actionAddConnect->setObjectName(QString::fromUtf8("actionAddConnect"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icon/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddConnect->setIcon(icon3);
        actionAddConnect->setFont(font);
        actionAddByText = new QAction(MainWindow);
        actionAddByText->setObjectName(QString::fromUtf8("actionAddByText"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icon/text.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddByText->setIcon(icon4);
        actionAddByText->setFont(font);
        actiontoolBar = new QAction(MainWindow);
        actiontoolBar->setObjectName(QString::fromUtf8("actiontoolBar"));
        actiontoolBar->setCheckable(true);
        actiontoolBar->setChecked(true);
        actiontoolBar->setFont(font);
        actionLineMap = new QAction(MainWindow);
        actionLineMap->setObjectName(QString::fromUtf8("actionLineMap"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icon/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLineMap->setIcon(icon5);
        actionLineMap->setFont(font);
        actionWheel = new QAction(MainWindow);
        actionWheel->setObjectName(QString::fromUtf8("actionWheel"));
        actionWheel->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/icon/mouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWheel->setIcon(icon6);
        actionWheel->setFont(font);
        actionuseHelp = new QAction(MainWindow);
        actionuseHelp->setObjectName(QString::fromUtf8("actionuseHelp"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/icon/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionuseHelp->setIcon(icon7);
        actionuseHelp->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(1030, 600));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelTransfer = new QLabel(centralWidget);
        labelTransfer->setObjectName(QString::fromUtf8("labelTransfer"));
        labelTransfer->setMinimumSize(QSize(280, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        labelTransfer->setFont(font1);

        verticalLayout_2->addWidget(labelTransfer);

        horizontalLayout4 = new QHBoxLayout();
        horizontalLayout4->setSpacing(10);
        horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
        labelStart = new QLabel(centralWidget);
        labelStart->setObjectName(QString::fromUtf8("labelStart"));
        labelStart->setEnabled(true);
        labelStart->setMinimumSize(QSize(70, 20));
        labelStart->setFont(font);

        horizontalLayout4->addWidget(labelStart);

        comboBoxStartLine = new QComboBox(centralWidget);
        comboBoxStartLine->addItem(QString());
        comboBoxStartLine->setObjectName(QString::fromUtf8("comboBoxStartLine"));
        comboBoxStartLine->setMinimumSize(QSize(90, 20));
        comboBoxStartLine->setFont(font);

        horizontalLayout4->addWidget(comboBoxStartLine);

        comboBoxStartStation = new QComboBox(centralWidget);
        comboBoxStartStation->addItem(QString());
        comboBoxStartStation->setObjectName(QString::fromUtf8("comboBoxStartStation"));
        comboBoxStartStation->setMinimumSize(QSize(90, 20));
        comboBoxStartStation->setFont(font);

        horizontalLayout4->addWidget(comboBoxStartStation);

        horizontalLayout4->setStretch(0, 7);

        verticalLayout_2->addLayout(horizontalLayout4);

        horizontalLayout5 = new QHBoxLayout();
        horizontalLayout5->setSpacing(10);
        horizontalLayout5->setObjectName(QString::fromUtf8("horizontalLayout5"));
        labelDestination = new QLabel(centralWidget);
        labelDestination->setObjectName(QString::fromUtf8("labelDestination"));
        labelDestination->setMinimumSize(QSize(70, 20));
        labelDestination->setFont(font);

        horizontalLayout5->addWidget(labelDestination);

        comboBoxDstLine = new QComboBox(centralWidget);
        comboBoxDstLine->addItem(QString());
        comboBoxDstLine->setObjectName(QString::fromUtf8("comboBoxDstLine"));
        comboBoxDstLine->setEnabled(true);
        comboBoxDstLine->setMinimumSize(QSize(90, 20));
        comboBoxDstLine->setFont(font);
        comboBoxDstLine->setEditable(false);

        horizontalLayout5->addWidget(comboBoxDstLine);

        comboBoxDstStation = new QComboBox(centralWidget);
        comboBoxDstStation->addItem(QString());
        comboBoxDstStation->setObjectName(QString::fromUtf8("comboBoxDstStation"));
        comboBoxDstStation->setMinimumSize(QSize(90, 20));
        comboBoxDstStation->setFont(font);
        comboBoxDstStation->setEditable(false);

        horizontalLayout5->addWidget(comboBoxDstStation);

        horizontalLayout5->setStretch(0, 7);

        verticalLayout_2->addLayout(horizontalLayout5);

        horizontalLayout6 = new QHBoxLayout();
        horizontalLayout6->setSpacing(10);
        horizontalLayout6->setObjectName(QString::fromUtf8("horizontalLayout6"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(190, 30));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButtonMinTransfer = new QRadioButton(groupBox);
        radioButtonMinTransfer->setObjectName(QString::fromUtf8("radioButtonMinTransfer"));
        radioButtonMinTransfer->setMinimumSize(QSize(100, 15));
        radioButtonMinTransfer->setFont(font);

        verticalLayout->addWidget(radioButtonMinTransfer);

        radioButtonMinTime = new QRadioButton(groupBox);
        radioButtonMinTime->setObjectName(QString::fromUtf8("radioButtonMinTime"));
        radioButtonMinTime->setMinimumSize(QSize(100, 15));
        radioButtonMinTime->setFont(font);
        radioButtonMinTime->setChecked(true);

        verticalLayout->addWidget(radioButtonMinTime);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        horizontalLayout6->addWidget(groupBox);

        pushButtonTransfer = new QPushButton(centralWidget);
        pushButtonTransfer->setObjectName(QString::fromUtf8("pushButtonTransfer"));
        pushButtonTransfer->setMinimumSize(QSize(70, 30));
        pushButtonTransfer->setFont(font);

        horizontalLayout6->addWidget(pushButtonTransfer);


        verticalLayout_2->addLayout(horizontalLayout6);

        labelTransferRoute = new QLabel(centralWidget);
        labelTransferRoute->setObjectName(QString::fromUtf8("labelTransferRoute"));
        labelTransferRoute->setMinimumSize(QSize(280, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        labelTransferRoute->setFont(font2);

        verticalLayout_2->addWidget(labelTransferRoute);

        textBrowserRoute = new QTextBrowser(centralWidget);
        textBrowserRoute->setObjectName(QString::fromUtf8("textBrowserRoute"));
        textBrowserRoute->setMinimumSize(QSize(300, 300));
        textBrowserRoute->setFont(font);

        verticalLayout_2->addWidget(textBrowserRoute);

        verticalLayout_2->setStretch(1, 2);
        verticalLayout_2->setStretch(3, 5);
        verticalLayout_2->setStretch(4, 2);
        verticalLayout_2->setStretch(5, 32);

        horizontalLayout->addLayout(verticalLayout_2);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(700, 580));

        horizontalLayout->addWidget(graphicsView);

        horizontalLayout->setStretch(1, 11);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1030, 26));
        menuBar->setMinimumSize(QSize(0, 25));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QString::fromUtf8("menu_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 0));
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
#if QT_CONFIG(shortcut)
        labelStart->setBuddy(comboBoxStartLine);
        labelDestination->setBuddy(comboBoxDstLine);
#endif // QT_CONFIG(shortcut)

        menuBar->addAction(menu_H->menuAction());
        menu_H->addAction(actionuseHelp);
        mainToolBar->addAction(actionAddLine);
        mainToolBar->addAction(actionAddStation);
        mainToolBar->addAction(actionAddConnect);
        mainToolBar->addAction(actionAddByText);
        mainToolBar->addAction(actionLineMap);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\234\260\351\223\201\346\215\242\344\271\230\346\214\207\345\215\227", nullptr));
        actionAddLine->setText(QCoreApplication::translate("MainWindow", "\347\272\277\350\267\257(&L)", nullptr));
#if QT_CONFIG(shortcut)
        actionAddLine->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddStation->setText(QCoreApplication::translate("MainWindow", "\347\253\231\347\202\271(&S)", nullptr));
#if QT_CONFIG(shortcut)
        actionAddStation->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245(&C)", nullptr));
#if QT_CONFIG(shortcut)
        actionAddConnect->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddByText->setText(QCoreApplication::translate("MainWindow", "\346\226\207\346\234\254\346\226\271\345\274\217(&T)", nullptr));
#if QT_CONFIG(shortcut)
        actionAddByText->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actiontoolBar->setText(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        actionLineMap->setText(QCoreApplication::translate("MainWindow", "\345\234\260\351\223\201\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actionLineMap->setToolTip(QCoreApplication::translate("MainWindow", "\345\234\260\351\223\201\347\275\221\347\273\234\347\272\277\350\267\257\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionLineMap->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_CONFIG(shortcut)
        actionWheel->setText(QCoreApplication::translate("MainWindow", "\351\274\240\346\240\207\345\217\257\347\274\251\346\224\276", nullptr));
        actionuseHelp->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\350\257\264\346\230\216", nullptr));
        labelTransfer->setText(QCoreApplication::translate("MainWindow", "\345\234\260\351\223\201\346\215\242\344\271\230\346\214\207\345\215\227", nullptr));
        labelStart->setText(QCoreApplication::translate("MainWindow", "\350\265\267\347\202\271\357\274\232", nullptr));
        comboBoxStartLine->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\347\272\277", nullptr));

        comboBoxStartLine->setCurrentText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\347\272\277", nullptr));
        comboBoxStartStation->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\231\347\202\271", nullptr));

        comboBoxStartStation->setCurrentText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\231\347\202\271", nullptr));
        labelDestination->setText(QCoreApplication::translate("MainWindow", "\347\233\256\347\232\204\345\234\260\357\274\232", nullptr));
        comboBoxDstLine->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\347\272\277", nullptr));

        comboBoxDstLine->setCurrentText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\347\272\277", nullptr));
        comboBoxDstStation->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\231\347\202\271", nullptr));

        groupBox->setTitle(QString());
        radioButtonMinTransfer->setText(QCoreApplication::translate("MainWindow", "\345\260\221\346\215\242\344\271\230", nullptr));
        radioButtonMinTime->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264\347\237\255", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\350\267\257\347\272\277", nullptr));
        labelTransferRoute->setText(QCoreApplication::translate("MainWindow", "\346\216\250\350\215\220\350\267\257\347\272\277\357\274\232", nullptr));
        menu_H->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

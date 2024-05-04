/********************************************************************************
** Form generated from reading UI file 'managelines.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGELINES_H
#define UI_MANAGELINES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageLines
{
public:
    QTabWidget *tabWidget;
    QWidget *tabAddLine;
    QLabel *label_3;
    QLineEdit *lineEditLineName;
    QPushButton *pushButtonAddLine;
    QLabel *label_8;
    QPushButton *pushButtonChooseColor;
    QWidget *tabAddStation;
    QDoubleSpinBox *doubleSpinBoxLatitude;
    QLabel *labelLatitude;
    QLabel *labelLongitude;
    QDoubleSpinBox *doubleSpinBoxLongitude;
    QLineEdit *lineEditStationName;
    QTextBrowser *textBrowserLinesSelected;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButtonAddStation;
    QLabel *label_11;
    QListWidget *listWidget;
    QWidget *tabAddConnection;
    QComboBox *comboBoxConnectStation1;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBoxConnectStation2;
    QPushButton *pushButtonConnect;
    QLabel *label_7;
    QComboBox *comboBoxConnectLine;
    QWidget *tabAddByText;
    QTextEdit *textEdit;
    QPushButton *pushButtonAddByText;

    void setupUi(QDialog *ManageLines)
    {
        if (ManageLines->objectName().isEmpty())
            ManageLines->setObjectName(QString::fromUtf8("ManageLines"));
        ManageLines->setEnabled(true);
        ManageLines->resize(600, 400);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        ManageLines->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        ManageLines->setWindowIcon(icon);
        tabWidget = new QTabWidget(ManageLines);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 0, 600, 400));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabAddLine = new QWidget();
        tabAddLine->setObjectName(QString::fromUtf8("tabAddLine"));
        tabAddLine->setFont(font);
        label_3 = new QLabel(tabAddLine);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 40, 131, 61));
        lineEditLineName = new QLineEdit(tabAddLine);
        lineEditLineName->setObjectName(QString::fromUtf8("lineEditLineName"));
        lineEditLineName->setGeometry(QRect(120, 50, 141, 31));
        pushButtonAddLine = new QPushButton(tabAddLine);
        pushButtonAddLine->setObjectName(QString::fromUtf8("pushButtonAddLine"));
        pushButtonAddLine->setGeometry(QRect(240, 260, 91, 41));
        pushButtonAddLine->setMinimumSize(QSize(0, 0));
        pushButtonAddLine->setFont(font);
        label_8 = new QLabel(tabAddLine);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 110, 141, 51));
        pushButtonChooseColor = new QPushButton(tabAddLine);
        pushButtonChooseColor->setObjectName(QString::fromUtf8("pushButtonChooseColor"));
        pushButtonChooseColor->setGeometry(QRect(120, 120, 111, 31));
        pushButtonChooseColor->setMinimumSize(QSize(0, 0));
        pushButtonChooseColor->setMaximumSize(QSize(16777215, 16777215));
        pushButtonChooseColor->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/subway.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAddLine, icon1, QString());
        tabAddStation = new QWidget();
        tabAddStation->setObjectName(QString::fromUtf8("tabAddStation"));
        doubleSpinBoxLatitude = new QDoubleSpinBox(tabAddStation);
        doubleSpinBoxLatitude->setObjectName(QString::fromUtf8("doubleSpinBoxLatitude"));
        doubleSpinBoxLatitude->setGeometry(QRect(70, 230, 111, 20));
        doubleSpinBoxLatitude->setMinimumSize(QSize(85, 20));
        doubleSpinBoxLatitude->setDecimals(7);
        doubleSpinBoxLatitude->setMinimum(30.899999999999999);
        doubleSpinBoxLatitude->setMaximum(31.449999999999999);
        doubleSpinBoxLatitude->setSingleStep(0.100000000000000);
        doubleSpinBoxLatitude->setValue(30.899999999999999);
        labelLatitude = new QLabel(tabAddStation);
        labelLatitude->setObjectName(QString::fromUtf8("labelLatitude"));
        labelLatitude->setGeometry(QRect(14, 230, 51, 20));
        labelLatitude->setMinimumSize(QSize(35, 20));
        labelLatitude->setFont(font);
        labelLongitude = new QLabel(tabAddStation);
        labelLongitude->setObjectName(QString::fromUtf8("labelLongitude"));
        labelLongitude->setGeometry(QRect(14, 200, 51, 20));
        labelLongitude->setMinimumSize(QSize(35, 20));
        labelLongitude->setFont(font);
        doubleSpinBoxLongitude = new QDoubleSpinBox(tabAddStation);
        doubleSpinBoxLongitude->setObjectName(QString::fromUtf8("doubleSpinBoxLongitude"));
        doubleSpinBoxLongitude->setGeometry(QRect(70, 200, 111, 20));
        doubleSpinBoxLongitude->setMinimumSize(QSize(85, 20));
        doubleSpinBoxLongitude->setDecimals(7);
        doubleSpinBoxLongitude->setMinimum(121.000000000000000);
        doubleSpinBoxLongitude->setMaximum(122.000000000000000);
        doubleSpinBoxLongitude->setSingleStep(0.100000000000000);
        doubleSpinBoxLongitude->setValue(121.000000000000000);
        lineEditStationName = new QLineEdit(tabAddStation);
        lineEditStationName->setObjectName(QString::fromUtf8("lineEditStationName"));
        lineEditStationName->setGeometry(QRect(20, 50, 80, 20));
        lineEditStationName->setMinimumSize(QSize(0, 0));
        lineEditStationName->setMaximumSize(QSize(16777215, 16777215));
        lineEditStationName->setFont(font);
        textBrowserLinesSelected = new QTextBrowser(tabAddStation);
        textBrowserLinesSelected->setObjectName(QString::fromUtf8("textBrowserLinesSelected"));
        textBrowserLinesSelected->setEnabled(false);
        textBrowserLinesSelected->setGeometry(QRect(440, 50, 140, 201));
        label_4 = new QLabel(tabAddStation);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 20, 91, 20));
        label_9 = new QLabel(tabAddStation);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 170, 101, 20));
        label_10 = new QLabel(tabAddStation);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(440, 20, 80, 20));
        pushButtonAddStation = new QPushButton(tabAddStation);
        pushButtonAddStation->setObjectName(QString::fromUtf8("pushButtonAddStation"));
        pushButtonAddStation->setGeometry(QRect(470, 280, 80, 30));
        pushButtonAddStation->setMinimumSize(QSize(0, 0));
        pushButtonAddStation->setFont(font);
        label_11 = new QLabel(tabAddStation);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(200, 20, 200, 20));
        listWidget = new QListWidget(tabAddStation);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(200, 50, 200, 270));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icon/station.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAddStation, icon2, QString());
        tabAddConnection = new QWidget();
        tabAddConnection->setObjectName(QString::fromUtf8("tabAddConnection"));
        tabAddConnection->setEnabled(true);
        comboBoxConnectStation1 = new QComboBox(tabAddConnection);
        comboBoxConnectStation1->setObjectName(QString::fromUtf8("comboBoxConnectStation1"));
        comboBoxConnectStation1->setEnabled(true);
        comboBoxConnectStation1->setGeometry(QRect(150, 20, 100, 20));
        comboBoxConnectStation1->setMinimumSize(QSize(0, 0));
        comboBoxConnectStation1->setMaximumSize(QSize(16777215, 16777215));
        comboBoxConnectStation1->setFont(font);
        comboBoxConnectStation1->setEditable(true);
        label_5 = new QLabel(tabAddConnection);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 80, 20));
        label_6 = new QLabel(tabAddConnection);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 60, 80, 20));
        comboBoxConnectStation2 = new QComboBox(tabAddConnection);
        comboBoxConnectStation2->setObjectName(QString::fromUtf8("comboBoxConnectStation2"));
        comboBoxConnectStation2->setGeometry(QRect(150, 60, 100, 20));
        comboBoxConnectStation2->setMinimumSize(QSize(0, 0));
        comboBoxConnectStation2->setMaximumSize(QSize(16777215, 16777215));
        comboBoxConnectStation2->setFont(font);
        comboBoxConnectStation2->setEditable(true);
        pushButtonConnect = new QPushButton(tabAddConnection);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));
        pushButtonConnect->setGeometry(QRect(240, 290, 80, 30));
        pushButtonConnect->setMinimumSize(QSize(0, 0));
        pushButtonConnect->setFont(font);
        label_7 = new QLabel(tabAddConnection);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 100, 101, 20));
        comboBoxConnectLine = new QComboBox(tabAddConnection);
        comboBoxConnectLine->setObjectName(QString::fromUtf8("comboBoxConnectLine"));
        comboBoxConnectLine->setGeometry(QRect(150, 100, 100, 20));
        comboBoxConnectLine->setMinimumSize(QSize(0, 0));
        comboBoxConnectLine->setMaximumSize(QSize(16777215, 16777215));
        comboBoxConnectLine->setFont(font);
        comboBoxConnectLine->setEditable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icon/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAddConnection, icon3, QString());
        tabAddByText = new QWidget();
        tabAddByText->setObjectName(QString::fromUtf8("tabAddByText"));
        textEdit = new QTextEdit(tabAddByText);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 20, 560, 300));
        pushButtonAddByText = new QPushButton(tabAddByText);
        pushButtonAddByText->setObjectName(QString::fromUtf8("pushButtonAddByText"));
        pushButtonAddByText->setGeometry(QRect(360, 330, 131, 30));
        pushButtonAddByText->setMinimumSize(QSize(0, 0));
        pushButtonAddByText->setFont(font);
        tabWidget->addTab(tabAddByText, QString());
#if QT_CONFIG(shortcut)
        label_3->setBuddy(lineEditLineName);
        label_8->setBuddy(pushButtonChooseColor);
        labelLatitude->setBuddy(doubleSpinBoxLatitude);
        labelLongitude->setBuddy(doubleSpinBoxLongitude);
        label_4->setBuddy(lineEditStationName);
        label_9->setBuddy(doubleSpinBoxLongitude);
        label_5->setBuddy(comboBoxConnectStation1);
        label_6->setBuddy(comboBoxConnectStation2);
        label_7->setBuddy(comboBoxConnectLine);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ManageLines);

        tabWidget->setCurrentIndex(0);
        pushButtonAddLine->setDefault(true);
        pushButtonAddStation->setDefault(true);
        comboBoxConnectStation1->setCurrentIndex(-1);
        pushButtonConnect->setDefault(true);
        pushButtonAddByText->setDefault(true);


        QMetaObject::connectSlotsByName(ManageLines);
    } // setupUi

    void retranslateUi(QDialog *ManageLines)
    {
        ManageLines->setWindowTitle(QCoreApplication::translate("ManageLines", "\346\267\273\345\212\240", nullptr));
        label_3->setText(QCoreApplication::translate("ManageLines", "<html><head/><body><p>\347\272\277\350\267\257\345\220\215\347\247\260\357\274\232</p></body></html>", nullptr));
        lineEditLineName->setPlaceholderText(QCoreApplication::translate("ManageLines", "\350\257\267\350\276\223\345\205\245\347\272\277\350\267\257\345\220\215", nullptr));
        pushButtonAddLine->setText(QCoreApplication::translate("ManageLines", "\346\267\273\345\212\240\350\267\257\347\272\277", nullptr));
        label_8->setText(QCoreApplication::translate("ManageLines", "<html><head/><body><p>\347\272\277\350\267\257\351\242\234\350\211\262\357\274\232</p></body></html>", nullptr));
        pushButtonChooseColor->setText(QCoreApplication::translate("ManageLines", "\351\200\211\346\213\251\351\242\234\350\211\262", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAddLine), QCoreApplication::translate("ManageLines", "\347\272\277\350\267\257(&L)", nullptr));
        labelLatitude->setText(QCoreApplication::translate("ManageLines", "\345\214\227\347\272\254&N", nullptr));
        labelLongitude->setText(QCoreApplication::translate("ManageLines", "\344\270\234\347\273\217&E", nullptr));
        lineEditStationName->setText(QString());
        lineEditStationName->setPlaceholderText(QCoreApplication::translate("ManageLines", "\346\267\273\345\212\240\347\253\231\347\202\271\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("ManageLines", "\347\253\231\347\202\271\345\220\215\347\247\260\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("ManageLines", " \347\273\217\347\272\254\345\272\246\345\235\220\346\240\207\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("ManageLines", "\345\267\262\351\200\211\346\213\251\357\274\232", nullptr));
        pushButtonAddStation->setText(QCoreApplication::translate("ManageLines", "\346\267\273\345\212\240\347\253\231\347\202\271", nullptr));
        label_11->setText(QCoreApplication::translate("ManageLines", "\351\200\211\346\213\251 \346\267\273\345\212\240\345\210\260\347\272\277\350\267\257\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAddStation), QCoreApplication::translate("ManageLines", "\347\253\231\347\202\271(&S)", nullptr));
        label_5->setText(QCoreApplication::translate("ManageLines", "<html><head/><body><p>\347\253\231\347\202\2711\357\274\232</p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("ManageLines", "<html><head/><body><p>\347\253\231\347\202\2712\357\274\232</p></body></html>", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("ManageLines", "\350\277\236\346\216\245", nullptr));
        label_7->setText(QCoreApplication::translate("ManageLines", "<html><head/><body><p>\346\211\200\345\261\236\347\272\277\350\267\257\357\274\232</p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAddConnection), QCoreApplication::translate("ManageLines", "\350\277\236\346\216\245(&C)", nullptr));
        pushButtonAddByText->setText(QCoreApplication::translate("ManageLines", "\344\273\245\346\226\207\346\234\254\346\226\271\345\274\217\346\267\273\345\212\240", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAddByText), QCoreApplication::translate("ManageLines", "\346\226\207\346\234\254\346\226\271\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageLines: public Ui_ManageLines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGELINES_H

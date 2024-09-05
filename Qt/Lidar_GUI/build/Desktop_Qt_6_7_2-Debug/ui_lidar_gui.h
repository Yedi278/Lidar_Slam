/********************************************************************************
** Form generated from reading UI file 'lidar_gui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIDAR_GUI_H
#define UI_LIDAR_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Lidar_GUI
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Lidar_GUI)
    {
        if (Lidar_GUI->objectName().isEmpty())
            Lidar_GUI->setObjectName("Lidar_GUI");
        Lidar_GUI->resize(568, 361);
        centralwidget = new QWidget(Lidar_GUI);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName("widget");

        verticalLayout->addWidget(widget);

        Lidar_GUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Lidar_GUI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 568, 23));
        Lidar_GUI->setMenuBar(menubar);
        statusbar = new QStatusBar(Lidar_GUI);
        statusbar->setObjectName("statusbar");
        Lidar_GUI->setStatusBar(statusbar);

        retranslateUi(Lidar_GUI);

        QMetaObject::connectSlotsByName(Lidar_GUI);
    } // setupUi

    void retranslateUi(QMainWindow *Lidar_GUI)
    {
        Lidar_GUI->setWindowTitle(QCoreApplication::translate("Lidar_GUI", "Lidar_GUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lidar_GUI: public Ui_Lidar_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIDAR_GUI_H

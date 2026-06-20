/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "simview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnHistorique;
    QPushButton *btnEnregistrer;
    QPushButton *btnExportTrace;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnTemplates;
    QPushButton *btnAddExperience;
    QComboBox *cbIntegrateur;
    SimView *simWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(846, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnHistorique = new QPushButton(widget);
        btnHistorique->setObjectName("btnHistorique");
        btnHistorique->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #1a3a5c; color: white;\n"
"    font-weight: bold; border-radius: 4px; padding: 2px 6px; }\n"
"    QPushButton:hover { background-color: #1f4e79; }\n"
"    QPushButton:pressed { background-color: #154360; }"));

        horizontalLayout->addWidget(btnHistorique);

        btnEnregistrer = new QPushButton(widget);
        btnEnregistrer->setObjectName("btnEnregistrer");
        btnEnregistrer->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #f39c12; color: white;\n"
"    font-weight: bold; border-radius: 4px; padding: 2px 6px; }\n"
"    QPushButton:hover { background-color: #e67e22; }\n"
"    QPushButton:pressed { background-color: #d35400; }\n"
"    QPushButton:disabled { background-color: #7f6030; color: #aaaaaa; }"));

        horizontalLayout->addWidget(btnEnregistrer);

        btnExportTrace = new QPushButton(widget);
        btnExportTrace->setObjectName("btnExportTrace");
        btnExportTrace->setStyleSheet(QString::fromUtf8("\n"
"    QPushButton { background-color: #8e44ad; color: white;\n"
"    font-weight: bold; border-radius: 4px; padding: 2px 6px; }\n"
"    QPushButton:hover { background-color: #7d3c98; }\n"
"    QPushButton:pressed { background-color: #6c3483; }\n"
""));

        horizontalLayout->addWidget(btnExportTrace);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnTemplates = new QPushButton(widget);
        btnTemplates->setObjectName("btnTemplates");

        horizontalLayout->addWidget(btnTemplates);

        btnAddExperience = new QPushButton(widget);
        btnAddExperience->setObjectName("btnAddExperience");

        horizontalLayout->addWidget(btnAddExperience);

        cbIntegrateur = new QComboBox(widget);
        cbIntegrateur->setObjectName("cbIntegrateur");

        horizontalLayout->addWidget(cbIntegrateur);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(widget);

        simWidget = new SimView(centralwidget);
        simWidget->setObjectName("simWidget");
        simWidget->setStyleSheet(QString::fromUtf8("background-color: #0a0a1a;"));

        verticalLayout->addWidget(simWidget);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnHistorique->setText(QCoreApplication::translate("MainWindow", "Historique", nullptr));
        btnEnregistrer->setText(QCoreApplication::translate("MainWindow", " Enregistrer", nullptr));
        btnExportTrace->setText(QCoreApplication::translate("MainWindow", "Exporter Trace", nullptr));
        btnTemplates->setText(QCoreApplication::translate("MainWindow", "Templates", nullptr));
        btnAddExperience->setText(QCoreApplication::translate("MainWindow", "Nouvelle Experience", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

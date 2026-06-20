/********************************************************************************
** Form generated from reading UI file 'templatedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATEDIALOG_H
#define UI_TEMPLATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QPushButton *btnTerreSoleilLune;
    QPushButton *btnTriSoleils;
    QPushButton *btnGalaxie15;
    QPushButton *btnInfinity;
    QPushButton *btnTerreSoleilMars;
    QPushButton *btnTerreSoleil;
    QPushButton *btnBiSoleilsPlanete;
    QPushButton *btnBiSoleils;
    QPushButton *btnDoubleBiSoleils;
    QPushButton *btnSystemeSolaire;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnAddTemplate;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *TemplateDialog)
    {
        if (TemplateDialog->objectName().isEmpty())
            TemplateDialog->setObjectName("TemplateDialog");
        TemplateDialog->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(TemplateDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(TemplateDialog);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #ffffff;"));
        label->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(label);

        widget = new QWidget(TemplateDialog);
        widget->setObjectName("widget");
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        btnTerreSoleilLune = new QPushButton(widget);
        btnTerreSoleilLune->setObjectName("btnTerreSoleilLune");

        gridLayout_3->addWidget(btnTerreSoleilLune, 2, 0, 1, 1);

        btnTriSoleils = new QPushButton(widget);
        btnTriSoleils->setObjectName("btnTriSoleils");

        gridLayout_3->addWidget(btnTriSoleils, 1, 1, 1, 1);

        btnGalaxie15 = new QPushButton(widget);
        btnGalaxie15->setObjectName("btnGalaxie15");

        gridLayout_3->addWidget(btnGalaxie15, 2, 1, 1, 1);

        btnInfinity = new QPushButton(widget);
        btnInfinity->setObjectName("btnInfinity");

        gridLayout_3->addWidget(btnInfinity, 3, 1, 1, 1);

        btnTerreSoleilMars = new QPushButton(widget);
        btnTerreSoleilMars->setObjectName("btnTerreSoleilMars");

        gridLayout_3->addWidget(btnTerreSoleilMars, 3, 0, 1, 1);

        btnTerreSoleil = new QPushButton(widget);
        btnTerreSoleil->setObjectName("btnTerreSoleil");

        gridLayout_3->addWidget(btnTerreSoleil, 0, 0, 1, 1);

        btnBiSoleilsPlanete = new QPushButton(widget);
        btnBiSoleilsPlanete->setObjectName("btnBiSoleilsPlanete");

        gridLayout_3->addWidget(btnBiSoleilsPlanete, 1, 0, 1, 1);

        btnBiSoleils = new QPushButton(widget);
        btnBiSoleils->setObjectName("btnBiSoleils");

        gridLayout_3->addWidget(btnBiSoleils, 0, 1, 1, 1);

        btnDoubleBiSoleils = new QPushButton(widget);
        btnDoubleBiSoleils->setObjectName("btnDoubleBiSoleils");

        gridLayout_3->addWidget(btnDoubleBiSoleils, 4, 0, 1, 1);

        btnSystemeSolaire = new QPushButton(widget);
        btnSystemeSolaire->setObjectName("btnSystemeSolaire");

        gridLayout_3->addWidget(btnSystemeSolaire, 4, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);


        verticalLayout_2->addLayout(verticalLayout);

        widget_2 = new QWidget(TemplateDialog);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnAddTemplate = new QPushButton(widget_2);
        btnAddTemplate->setObjectName("btnAddTemplate");

        horizontalLayout->addWidget(btnAddTemplate);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(widget_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(TemplateDialog);

        QMetaObject::connectSlotsByName(TemplateDialog);
    } // setupUi

    void retranslateUi(QDialog *TemplateDialog)
    {
        TemplateDialog->setWindowTitle(QCoreApplication::translate("TemplateDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("TemplateDialog", "Templates", nullptr));
        btnTerreSoleilLune->setText(QCoreApplication::translate("TemplateDialog", "Terre-Soleil-Lune", nullptr));
        btnTriSoleils->setText(QCoreApplication::translate("TemplateDialog", "Tri Soleils", nullptr));
        btnGalaxie15->setText(QCoreApplication::translate("TemplateDialog", "Galaxie \303\240 15 corps", nullptr));
        btnInfinity->setText(QCoreApplication::translate("TemplateDialog", "\342\210\236", nullptr));
        btnTerreSoleilMars->setText(QCoreApplication::translate("TemplateDialog", "Terre-Soleil-Mars", nullptr));
        btnTerreSoleil->setText(QCoreApplication::translate("TemplateDialog", "Terre-Soleil", nullptr));
        btnBiSoleilsPlanete->setText(QCoreApplication::translate("TemplateDialog", "Bi Soleils-Plan\303\250te", nullptr));
        btnBiSoleils->setText(QCoreApplication::translate("TemplateDialog", "Bi Soleils", nullptr));
        btnDoubleBiSoleils->setText(QCoreApplication::translate("TemplateDialog", "Double Bi Soleils", nullptr));
        btnSystemeSolaire->setText(QCoreApplication::translate("TemplateDialog", "Syst\303\250me Solaire", nullptr));
        btnAddTemplate->setText(QCoreApplication::translate("TemplateDialog", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TemplateDialog: public Ui_TemplateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATEDIALOG_H

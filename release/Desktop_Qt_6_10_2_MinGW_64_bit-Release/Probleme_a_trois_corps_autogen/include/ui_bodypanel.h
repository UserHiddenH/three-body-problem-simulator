/********************************************************************************
** Form generated from reading UI file 'bodypanel.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BODYPANEL_H
#define UI_BODYPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BodyPanel
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelNomCorps;
    QWidget *widget_2;
    QFormLayout *formLayout_6;
    QFormLayout *formLayout_5;
    QLabel *label;
    QLineEdit *editNom;
    QLabel *label_2;
    QLineEdit *editMasse;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *editX;
    QLabel *label_5;
    QLineEdit *editY;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *editVx;
    QLabel *label_8;
    QLineEdit *editVy;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *BodyPanel)
    {
        if (BodyPanel->objectName().isEmpty())
            BodyPanel->setObjectName("BodyPanel");
        BodyPanel->setEnabled(true);
        BodyPanel->resize(1019, 691);
        verticalLayout_3 = new QVBoxLayout(BodyPanel);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(BodyPanel);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelNomCorps = new QLabel(widget);
        labelNomCorps->setObjectName("labelNomCorps");
        labelNomCorps->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #ffffff;"));

        horizontalLayout_2->addWidget(labelNomCorps);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(BodyPanel);
        widget_2->setObjectName("widget_2");
        formLayout_6 = new QFormLayout(widget_2);
        formLayout_6->setObjectName("formLayout_6");
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName("formLayout_5");

        formLayout_6->setLayout(0, QFormLayout::ItemRole::LabelRole, formLayout_5);

        label = new QLabel(widget_2);
        label->setObjectName("label");

        formLayout_6->setWidget(1, QFormLayout::ItemRole::LabelRole, label);

        editNom = new QLineEdit(widget_2);
        editNom->setObjectName("editNom");
        editNom->setReadOnly(true);

        formLayout_6->setWidget(1, QFormLayout::ItemRole::FieldRole, editNom);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        formLayout_6->setWidget(2, QFormLayout::ItemRole::LabelRole, label_2);

        editMasse = new QLineEdit(widget_2);
        editMasse->setObjectName("editMasse");
        editMasse->setReadOnly(true);

        formLayout_6->setWidget(2, QFormLayout::ItemRole::FieldRole, editMasse);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #888888;"));

        formLayout_6->setWidget(3, QFormLayout::ItemRole::LabelRole, label_3);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");

        formLayout_6->setWidget(4, QFormLayout::ItemRole::LabelRole, label_4);

        editX = new QLineEdit(widget_2);
        editX->setObjectName("editX");
        editX->setReadOnly(true);

        formLayout_6->setWidget(4, QFormLayout::ItemRole::FieldRole, editX);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName("label_5");

        formLayout_6->setWidget(5, QFormLayout::ItemRole::LabelRole, label_5);

        editY = new QLineEdit(widget_2);
        editY->setObjectName("editY");
        editY->setReadOnly(true);

        formLayout_6->setWidget(5, QFormLayout::ItemRole::FieldRole, editY);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #888888;"));

        formLayout_6->setWidget(6, QFormLayout::ItemRole::LabelRole, label_6);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName("label_7");

        formLayout_6->setWidget(7, QFormLayout::ItemRole::LabelRole, label_7);

        editVx = new QLineEdit(widget_2);
        editVx->setObjectName("editVx");
        editVx->setReadOnly(true);

        formLayout_6->setWidget(7, QFormLayout::ItemRole::FieldRole, editVx);

        label_8 = new QLabel(widget_2);
        label_8->setObjectName("label_8");

        formLayout_6->setWidget(8, QFormLayout::ItemRole::LabelRole, label_8);

        editVy = new QLineEdit(widget_2);
        editVy->setObjectName("editVy");
        editVy->setReadOnly(true);

        formLayout_6->setWidget(8, QFormLayout::ItemRole::FieldRole, editVy);


        verticalLayout_2->addWidget(widget_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        widget_3 = new QWidget(BodyPanel);
        widget_3->setObjectName("widget_3");
        verticalLayout_12 = new QVBoxLayout(widget_3);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");

        verticalLayout_12->addLayout(verticalLayout_11);


        verticalLayout_3->addWidget(widget_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        retranslateUi(BodyPanel);

        QMetaObject::connectSlotsByName(BodyPanel);
    } // setupUi

    void retranslateUi(QWidget *BodyPanel)
    {
        BodyPanel->setWindowTitle(QCoreApplication::translate("BodyPanel", "Form", nullptr));
        labelNomCorps->setText(QCoreApplication::translate("BodyPanel", "Param\303\250tres - Corps", nullptr));
        label->setText(QCoreApplication::translate("BodyPanel", "Nom", nullptr));
        label_2->setText(QCoreApplication::translate("BodyPanel", "Masse", nullptr));
        label_3->setText(QCoreApplication::translate("BodyPanel", " \342\224\200\342\224\200 Position \342\224\200\342\224\200", nullptr));
        label_4->setText(QCoreApplication::translate("BodyPanel", "X", nullptr));
        label_5->setText(QCoreApplication::translate("BodyPanel", "Y", nullptr));
        label_6->setText(QCoreApplication::translate("BodyPanel", "\342\224\200\342\224\200 Vecteur Vitesse \342\224\200\342\224\200", nullptr));
        label_7->setText(QCoreApplication::translate("BodyPanel", "Vx", nullptr));
        label_8->setText(QCoreApplication::translate("BodyPanel", "Vy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BodyPanel: public Ui_BodyPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BODYPANEL_H

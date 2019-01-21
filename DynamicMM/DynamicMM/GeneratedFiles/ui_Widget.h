/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetClass
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Openfile_Btn;
    QPushButton *StartBtn;
    QPushButton *FF_Btn;
    QPushButton *BF_Btn;
    QPushButton *WF_Btn;
    QPushButton *Clear_Btn;
    QPushButton *Restore_Btn;
    QPushButton *Save_Btn;
    QTextEdit *textEdit;

    void setupUi(QWidget *WidgetClass)
    {
        if (WidgetClass->objectName().isEmpty())
            WidgetClass->setObjectName(QString::fromUtf8("WidgetClass"));
        WidgetClass->resize(1027, 809);
        label = new QLabel(WidgetClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 10, 241, 31));
        horizontalLayoutWidget = new QWidget(WidgetClass);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(210, 700, 795, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Openfile_Btn = new QPushButton(horizontalLayoutWidget);
        Openfile_Btn->setObjectName(QString::fromUtf8("Openfile_Btn"));

        horizontalLayout_2->addWidget(Openfile_Btn);

        StartBtn = new QPushButton(horizontalLayoutWidget);
        StartBtn->setObjectName(QString::fromUtf8("StartBtn"));

        horizontalLayout_2->addWidget(StartBtn);

        FF_Btn = new QPushButton(horizontalLayoutWidget);
        FF_Btn->setObjectName(QString::fromUtf8("FF_Btn"));
        FF_Btn->setEnabled(false);

        horizontalLayout_2->addWidget(FF_Btn);

        BF_Btn = new QPushButton(horizontalLayoutWidget);
        BF_Btn->setObjectName(QString::fromUtf8("BF_Btn"));
        BF_Btn->setEnabled(false);

        horizontalLayout_2->addWidget(BF_Btn);

        WF_Btn = new QPushButton(horizontalLayoutWidget);
        WF_Btn->setObjectName(QString::fromUtf8("WF_Btn"));
        WF_Btn->setEnabled(false);

        horizontalLayout_2->addWidget(WF_Btn);

        Clear_Btn = new QPushButton(horizontalLayoutWidget);
        Clear_Btn->setObjectName(QString::fromUtf8("Clear_Btn"));
        Clear_Btn->setEnabled(false);

        horizontalLayout_2->addWidget(Clear_Btn);

        Restore_Btn = new QPushButton(horizontalLayoutWidget);
        Restore_Btn->setObjectName(QString::fromUtf8("Restore_Btn"));
        Restore_Btn->setEnabled(false);

        horizontalLayout_2->addWidget(Restore_Btn);

        Save_Btn = new QPushButton(horizontalLayoutWidget);
        Save_Btn->setObjectName(QString::fromUtf8("Save_Btn"));
        Save_Btn->setEnabled(false);

        horizontalLayout_2->addWidget(Save_Btn);

        textEdit = new QTextEdit(WidgetClass);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(210, 50, 801, 631));

        retranslateUi(WidgetClass);

        QMetaObject::connectSlotsByName(WidgetClass);
    } // setupUi

    void retranslateUi(QWidget *WidgetClass)
    {
        WidgetClass->setWindowTitle(QApplication::translate("WidgetClass", "Widget", nullptr));
        label->setText(QString());
        Openfile_Btn->setText(QApplication::translate("WidgetClass", "Open", nullptr));
        StartBtn->setText(QApplication::translate("WidgetClass", "Start", nullptr));
        FF_Btn->setText(QApplication::translate("WidgetClass", "First Fit", nullptr));
        BF_Btn->setText(QApplication::translate("WidgetClass", "Best Fit", nullptr));
        WF_Btn->setText(QApplication::translate("WidgetClass", "Worst Fit", nullptr));
        Clear_Btn->setText(QApplication::translate("WidgetClass", "Clear", nullptr));
        Restore_Btn->setText(QApplication::translate("WidgetClass", "Restore", nullptr));
        Save_Btn->setText(QApplication::translate("WidgetClass", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetClass: public Ui_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

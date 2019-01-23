/********************************************************************************
** Form generated from reading UI file 'PictureDecoder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREDECODER_H
#define UI_PICTUREDECODER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PictureDecoderClass
{
public:
    QTextEdit *textEdit;
    QPushButton *OpenFile_Btn;

    void setupUi(QWidget *PictureDecoderClass)
    {
        if (PictureDecoderClass->objectName().isEmpty())
            PictureDecoderClass->setObjectName(QString::fromUtf8("PictureDecoderClass"));
        PictureDecoderClass->resize(1064, 672);
        textEdit = new QTextEdit(PictureDecoderClass);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 1041, 611));
        OpenFile_Btn = new QPushButton(PictureDecoderClass);
        OpenFile_Btn->setObjectName(QString::fromUtf8("OpenFile_Btn"));
        OpenFile_Btn->setGeometry(QRect(480, 630, 93, 28));

        retranslateUi(PictureDecoderClass);

        QMetaObject::connectSlotsByName(PictureDecoderClass);
    } // setupUi

    void retranslateUi(QWidget *PictureDecoderClass)
    {
        PictureDecoderClass->setWindowTitle(QApplication::translate("PictureDecoderClass", "PictureDecoder", nullptr));
        OpenFile_Btn->setText(QApplication::translate("PictureDecoderClass", "Open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PictureDecoderClass: public Ui_PictureDecoderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREDECODER_H

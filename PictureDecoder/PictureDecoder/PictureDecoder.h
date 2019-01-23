#pragma once

#include <QtWidgets/QWidget>
#include <qfiledialog.h>
#include "ui_PictureDecoder.h"

class PictureDecoder : public QWidget
{
	Q_OBJECT

private slots:
	void on_OpenFile_Btn_clicked();


public:
	PictureDecoder(QWidget *parent = Q_NULLPTR);

private:
	Ui::PictureDecoderClass ui;
};

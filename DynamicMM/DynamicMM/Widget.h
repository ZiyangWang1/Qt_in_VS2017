#pragma once

#include <QtWidgets/QWidget>
#include "ui_Widget.h"
#include <QWidget>
#include <QList>
#include <QBrush>
#include <QPainter>
#include <QColor>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <qtimer.h>

#define MEMERY_SIZE		(u32)200
#define JOB_NUMBER		(u32)20
#define random(x)		(rand()%x)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct
{
	u32 u32JobNum;
	u32 u32Size;
	u32 u32ProcessTime;
} JobNodeType;

typedef struct
{
	u32 u32PartitionNum;
	u32 u32StartAddress;
	u32 u32Length;
	u32 u32OccupyedMark;
	u32 u32RemainTime;
} AllocatedNodeType;

typedef struct
{
	u32 u32PartitionNum;
	u32 u32StartAddress;
	u32 u32Length;
	u32 u32OccupyedMark;
} UnallocatedNodeType;

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);

	Ui::WidgetClass ui;
	QTimer *t;

private slots:
	void on_StartBtn_clicked();

	void on_FF_Btn_clicked();

	void on_Clear_Btn_clicked();

	void on_Restore_Btn_clicked();

	void on_BF_Btn_clicked();

	void on_WF_Btn_clicked();

	void on_Openfile_Btn_clicked();

	void on_Save_Btn_clicked();

	void ProcessFF();

private:

	QPen pen;
	QBrush brush;
	Qt::GlobalColor color = Qt::red;
};



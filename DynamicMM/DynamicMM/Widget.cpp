#include "Widget.h"

static QList<JobNodeType*> JobList;
static QList<UnallocatedNodeType*> UnallocatedList;
static QList<AllocatedNodeType*> AllocatedList;
static u32 u32Timer = 0;
static u32 u32WaitingTask = 0;

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void Widget::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	QString num, num1;

	p.setPen(pen);
	p.setBrush(brush);

	p.drawRect(40, 20, 100, 750);
	for (int i = 0; i < AllocatedList.size(); i++)
	{
		p.drawRect(40, (AllocatedList.at(i)->u32StartAddress * 750 / MEMERY_SIZE) + 20,
			100, AllocatedList.at(i)->u32Length * 750 / MEMERY_SIZE);
		p.fillRect(40, (AllocatedList.at(i)->u32StartAddress * 750 / MEMERY_SIZE) + 21,
			100, (AllocatedList.at(i)->u32Length * 750 / MEMERY_SIZE) - 1, color);
		p.drawText(150, (AllocatedList.at(i)->u32StartAddress + AllocatedList.at(i)->u32Length) * 750 / MEMERY_SIZE + 25,
			num.setNum(AllocatedList.at(i)->u32StartAddress + AllocatedList.at(i)->u32Length));
		p.drawText(70, (AllocatedList.at(i)->u32StartAddress * 750 / MEMERY_SIZE) + 25 +
			AllocatedList.at(i)->u32Length * 750 / MEMERY_SIZE / 2,
			"JOB" + num.setNum(AllocatedList.at(i)->u32OccupyedMark) + ":" + num1.setNum(AllocatedList.at(i)->u32RemainTime));
	}

	// p.fillRect(100,100,20,20,color);
}

void GenerateJobList(void)
{
	for (u32 i = 0; i < JOB_NUMBER; i++)
	{
		JobNodeType* pJobNode = (JobNodeType*)malloc(12);
		pJobNode->u32JobNum = i + 1;
		pJobNode->u32Size = random(50) + 5;
		pJobNode->u32ProcessTime = random(10) + 5;
		JobList.append(pJobNode);
	}
}

void UnallocatedList_Init(void)
{
	UnallocatedNodeType* pUnallocatedNode = (UnallocatedNodeType*)malloc(16);
	pUnallocatedNode->u32PartitionNum = 1;
	pUnallocatedNode->u32StartAddress = 0;
	pUnallocatedNode->u32Length = MEMERY_SIZE;
	pUnallocatedNode->u32OccupyedMark = 0;
	UnallocatedList.append(pUnallocatedNode);
}

void UnallocatedList_Delete(int i)
{
	free(UnallocatedList.at(i));
	UnallocatedList.removeAt(i);
	for (int j = i; i < UnallocatedList.size(); i++)
	{
		UnallocatedList.at(j)->u32PartitionNum--;
	}
}

void UnallocatedList_Combine(void)
{
	for (int i = 0; i < UnallocatedList.size() - 1; i++)
	{
		if (UnallocatedList.at(i + 1)->u32StartAddress ==
			(UnallocatedList.at(i)->u32StartAddress + UnallocatedList.at(i)->u32Length))
		{
			UnallocatedList.at(i)->u32Length += UnallocatedList.at(i + 1)->u32Length;
			UnallocatedList_Delete(i + 1);
			i--;
		}
	}
}

void UnallocatedList_Insert(u32 _u32StartAddress, u32 _u32Length)
{
	if (UnallocatedList.isEmpty())
	{
		UnallocatedNodeType* pUnallocatedNode = (UnallocatedNodeType*)malloc(16);
		pUnallocatedNode->u32PartitionNum = 1;
		pUnallocatedNode->u32StartAddress = _u32StartAddress;
		pUnallocatedNode->u32Length = _u32Length;
		pUnallocatedNode->u32OccupyedMark = 0;
		UnallocatedList.append(pUnallocatedNode);
	}
	else
	{
		if (UnallocatedList.at(UnallocatedList.size() - 1)->u32StartAddress < _u32StartAddress)
		{
			UnallocatedNodeType* pUnallocatedNode = (UnallocatedNodeType*)malloc(16);
			pUnallocatedNode->u32PartitionNum = UnallocatedList.size() + 1;
			pUnallocatedNode->u32StartAddress = _u32StartAddress;
			pUnallocatedNode->u32Length = _u32Length;
			pUnallocatedNode->u32OccupyedMark = 0;
			UnallocatedList.append(pUnallocatedNode);
		}
		else
		{
			for (int i = 0; i < UnallocatedList.size(); i++)
			{
				if (UnallocatedList.at(i)->u32StartAddress > _u32StartAddress)
				{
					UnallocatedNodeType* pUnallocatedNode = (UnallocatedNodeType*)malloc(16);
					pUnallocatedNode->u32PartitionNum = UnallocatedList.at(i)->u32PartitionNum;
					pUnallocatedNode->u32StartAddress = _u32StartAddress;
					pUnallocatedNode->u32Length = _u32Length;
					pUnallocatedNode->u32OccupyedMark = 0;
					UnallocatedList.insert(i, pUnallocatedNode);

					for (int j = i + 1; j < UnallocatedList.size(); j++)
					{
						UnallocatedList.at(j)->u32PartitionNum++;
					}
					break;
				}
			}
		}
		UnallocatedList_Combine();
	}
}

void AllocatedList_Delete(int i)
{
	free(AllocatedList.at(i));
	AllocatedList.removeAt(i);
	for (int j = i; j < AllocatedList.size(); j++)
	{
		AllocatedList.at(j)->u32PartitionNum--;
	}
}

void Process(void)
{
	for (int i = 0; i < AllocatedList.size(); i++)
	{
		AllocatedList.at(i)->u32RemainTime--;
		if (AllocatedList.at(i)->u32RemainTime == 0)
		{
			UnallocatedList_Insert(AllocatedList.at(i)->u32StartAddress, AllocatedList.at(i)->u32Length);
			AllocatedList_Delete(i);
			i--;
		}
	}

}

void InsertJob(int _UnallocatedNum, int _JobNumber)
{
	AllocatedNodeType* pAllocatedNode = (AllocatedNodeType*)malloc(20);
	pAllocatedNode->u32PartitionNum = AllocatedList.size() + 1;
	pAllocatedNode->u32StartAddress = UnallocatedList.at(_UnallocatedNum)->u32StartAddress;
	pAllocatedNode->u32Length = JobList.at(_JobNumber)->u32Size;
	pAllocatedNode->u32OccupyedMark = JobList.at(_JobNumber)->u32JobNum;
	pAllocatedNode->u32RemainTime = JobList.at(_JobNumber)->u32ProcessTime;
	AllocatedList.append(pAllocatedNode);

	UnallocatedList.at(_UnallocatedNum)->u32StartAddress =
		UnallocatedList.at(_UnallocatedNum)->u32StartAddress + JobList.at(_JobNumber)->u32Size;
	UnallocatedList.at(_UnallocatedNum)->u32Length =
		UnallocatedList.at(_UnallocatedNum)->u32Length - JobList.at(_JobNumber)->u32Size;
	if (UnallocatedList.at(_UnallocatedNum)->u32Length == 0)
	{
		UnallocatedList_Delete(_UnallocatedNum);
	}
}

void FreeJobList(void)
{
	for (int i = 0; i < JobList.size(); i++)
	{
		free(JobList.at(i));
	}
	JobList.clear();
}

void FreeUnallocatedList(void)
{
	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		free(UnallocatedList.at(i));
	}
	UnallocatedList.clear();
}

void FreeAllocatedList(void)
{
	for (int i = 0; i < AllocatedList.size(); i++)
	{
		free(AllocatedList.at(i));
	}
	AllocatedList.clear();
}

void Widget::on_StartBtn_clicked()
{
	QString num1, num2, num3, num4;

	ui.label->setText("Start");
	GenerateJobList();
	UnallocatedList_Init();

	ui.textEdit->append("*****Job List*****");
	for (int i = 0; i < JobList.size(); i++)
	{
		ui.textEdit->append("Job number: " + num1.setNum(JobList.at(i)->u32JobNum) +
			" Process time: " + num3.setNum(JobList.at(i)->u32ProcessTime) +
			" Size: " + num4.setNum(JobList.at(i)->u32Size)
		);
	}

	ui.textEdit->append("*****Unallocated List*****");
	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		ui.textEdit->append("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark)
		);
	}

	ui.BF_Btn->setEnabled(true);
	ui.FF_Btn->setEnabled(true);
	ui.WF_Btn->setEnabled(true);
	ui.StartBtn->setEnabled(false);
	ui.Clear_Btn->setEnabled(true);
	ui.Openfile_Btn->setEnabled(false);

}

void Widget::on_FF_Btn_clicked()
{
	t= new QTimer(this);
	connect(t, SIGNAL(timeout()), this, SLOT(ProcessFF()));
	t->start(100);
}

void Widget::on_BF_Btn_clicked()
{
	QString num1, num2, num3, num4;
	int s32MinGap = 0x0fffffff;
	int CurrentSpace = -1;

	Process();
	u32Timer++;

	ui.label->setText("Best Fit:" + num1.setNum(u32Timer));
	ui.textEdit->clear();

	if (u32Timer == 1)
	{
		ui.FF_Btn->setEnabled(false);
		ui.WF_Btn->setEnabled(false);
		ui.Restore_Btn->setEnabled(true);
	}

	ui.textEdit->append("Waiting task:");
	ui.textEdit->append("Job number: " + num1.setNum(JobList.at(u32WaitingTask)->u32JobNum) +
		" Process time: " + num3.setNum(JobList.at(u32WaitingTask)->u32ProcessTime) +
		" Size: " + num4.setNum(JobList.at(u32WaitingTask)->u32Size)
	);

	ui.textEdit->append("\n\r*****Unallocated List*****");

	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		ui.textEdit->append("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark)
		);
	}

	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		if (UnallocatedList.at(i)->u32Length >= JobList.at(u32WaitingTask)->u32Size)
		{
			if (s32MinGap > (int)(UnallocatedList.at(i)->u32Length - JobList.at(u32WaitingTask)->u32Size))
			{
				s32MinGap = UnallocatedList.at(i)->u32Length - JobList.at(u32WaitingTask)->u32Size;
				CurrentSpace = i;
			}

		}
	}

	if (CurrentSpace == -1)
	{
		ui.textEdit->append("Insert faild! Waiting for memory!");
	}
	else
	{
		InsertJob(CurrentSpace, u32WaitingTask);
		u32WaitingTask++;
		ui.textEdit->append("Insert successful!\n\r*****Allocated list*****");

		for (int i = 0; i < AllocatedList.size(); i++)
		{
			ui.textEdit->append("Partition number: " + num1.setNum(AllocatedList.at(i)->u32PartitionNum) +
				" Start address: " + num2.setNum(AllocatedList.at(i)->u32StartAddress) +
				" Length: " + num3.setNum(AllocatedList.at(i)->u32Length) +
				" Mark: " + num4.setNum(AllocatedList.at(i)->u32OccupyedMark)
			);
		}

		if (u32WaitingTask == (u32)JobList.size())
		{
			ui.textEdit->append("All jobs are inserted!");
			ui.BF_Btn->setEnabled(false);
			ui.Save_Btn->setEnabled(true);
		}
	}

	this->update();

}

void Widget::on_WF_Btn_clicked()
{
	QString num1, num2, num3, num4;
	int s32MaxGap = -1;
	int CurrentSpace = -1;

	Process();
	u32Timer++;

	ui.label->setText("Worst Fit:" + num1.setNum(u32Timer));
	ui.textEdit->clear();

	if (u32Timer == 1)
	{
		ui.FF_Btn->setEnabled(false);
		ui.BF_Btn->setEnabled(false);
		ui.Restore_Btn->setEnabled(true);
	}

	ui.textEdit->append("Waiting task:");
	ui.textEdit->append("Job number: " + num1.setNum(JobList.at(u32WaitingTask)->u32JobNum) +
		" Process time: " + num3.setNum(JobList.at(u32WaitingTask)->u32ProcessTime) +
		" Size: " + num4.setNum(JobList.at(u32WaitingTask)->u32Size)
	);

	ui.textEdit->append("\n\r*****Unallocated List*****");

	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		ui.textEdit->append("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark)
		);
	}

	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		if (UnallocatedList.at(i)->u32Length >= JobList.at(u32WaitingTask)->u32Size)
		{
			if (s32MaxGap < (int)(UnallocatedList.at(i)->u32Length - JobList.at(u32WaitingTask)->u32Size))
			{
				s32MaxGap = UnallocatedList.at(i)->u32Length - JobList.at(u32WaitingTask)->u32Size;
				CurrentSpace = i;
			}

		}
	}

	if (CurrentSpace == -1)
	{
		ui.textEdit->append("Insert faild! Waiting for memory!");
	}
	else
	{
		InsertJob(CurrentSpace, u32WaitingTask);
		u32WaitingTask++;
		ui.textEdit->append("Insert successful!\n\r*****Allocated list*****");

		for (int i = 0; i < AllocatedList.size(); i++)
		{
			ui.textEdit->append("Partition number: " + num1.setNum(AllocatedList.at(i)->u32PartitionNum) +
				" Start address: " + num2.setNum(AllocatedList.at(i)->u32StartAddress) +
				" Length: " + num3.setNum(AllocatedList.at(i)->u32Length) +
				" Mark: " + num4.setNum(AllocatedList.at(i)->u32OccupyedMark)
			);
		}

		if (u32WaitingTask == (u32)JobList.size())
		{
			ui.textEdit->append("All jobs are inserted!");
			ui.WF_Btn->setEnabled(false);
			ui.Save_Btn->setEnabled(true);
		}
	}

	this->update();
}

void Widget::on_Clear_Btn_clicked()
{
	ui.label->setText("Clear");
	ui.textEdit->clear();
	FreeJobList();
	FreeUnallocatedList();
	FreeAllocatedList();
	u32Timer = 0;
	u32WaitingTask = 0;
	ui.BF_Btn->setEnabled(false);
	ui.FF_Btn->setEnabled(false);
	ui.WF_Btn->setEnabled(false);
	ui.StartBtn->setEnabled(true);
	ui.Clear_Btn->setEnabled(false);
	ui.Openfile_Btn->setEnabled(true);
	ui.Save_Btn->setEnabled(false);
	ui.Restore_Btn->setEnabled(false);
	this->update();
}

void Widget::on_Restore_Btn_clicked()
{
	QString num1, num2, num3, num4;

	ui.label->setText("Restore");
	ui.textEdit->clear();
	FreeUnallocatedList();
	UnallocatedList_Init();
	FreeAllocatedList();
	u32Timer = 0;
	u32WaitingTask = 0;

	ui.textEdit->append("*****Job List*****");
	for (int i = 0; i < JobList.size(); i++)
	{
		ui.textEdit->append("Job number: " + num1.setNum(JobList.at(i)->u32JobNum) +
			" Process time: " + num3.setNum(JobList.at(i)->u32ProcessTime) +
			" Size: " + num4.setNum(JobList.at(i)->u32Size)
		);
	}

	ui.textEdit->append("*****Unallocated List*****");
	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		ui.textEdit->append("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark)
		);
	}

	ui.BF_Btn->setEnabled(true);
	ui.FF_Btn->setEnabled(true);
	ui.WF_Btn->setEnabled(true);
	ui.Restore_Btn->setEnabled(false);
	this->update();
}

void Widget::on_Openfile_Btn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("Allfile(*.*)"));
	QFile file(fileName);
	u32 u32JobNumber = 1;
	bool bok;
	QString num1, num2, num3, num4;

	if (!file.open(QIODevice::ReadOnly))
		return;

	ui.textEdit->clear();

	while (!file.atEnd())
	{
		QByteArray str = file.readLine();
		QString Message = QString(str);

		Message = Message.mid(0, Message.size() - 2);

		JobNodeType* pJobNode = (JobNodeType*)malloc(12);
		pJobNode->u32JobNum = u32JobNumber;
		pJobNode->u32Size = (u32)Message.mid(Message.size() - 2, Message.size()).toLong(&bok, 10);
		pJobNode->u32ProcessTime = (u32)Message.mid(0, 2).toLong(&bok, 10);
		JobList.append(pJobNode);

		u32JobNumber++;
	}
	file.close();

	UnallocatedList_Init();

	ui.textEdit->append("*****Job List*****");
	for (int i = 0; i < JobList.size(); i++)
	{
		ui.textEdit->append("Job number: " + num1.setNum(JobList.at(i)->u32JobNum) +
			" Process time: " + num3.setNum(JobList.at(i)->u32ProcessTime) +
			" Size: " + num4.setNum(JobList.at(i)->u32Size)
		);
	}

	ui.textEdit->append("*****Unallocated List*****");
	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		ui.textEdit->append("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark)
		);
	}

	ui.BF_Btn->setEnabled(true);
	ui.FF_Btn->setEnabled(true);
	ui.WF_Btn->setEnabled(true);
	ui.StartBtn->setEnabled(false);
	ui.Clear_Btn->setEnabled(true);
	ui.Openfile_Btn->setEnabled(false);

}

void Widget::on_Save_Btn_clicked()
{
	QDir SaveDir;
	SaveDir.setCurrent("D:\\WorkSpace\\VS2017\\DynamicMM\\DynamicMM");
	QFile SaveFile("save.txt");
	QString num1, num2, num3, num4;

	if (!SaveFile.open(QIODevice::WriteOnly))
		return;

	SaveFile.write("*****Job List*****\r\n");

	for (int i = 0; i < JobList.size(); i++)
	{
		SaveFile.write(("Job number: " + num1.setNum(JobList.at(i)->u32JobNum) +
			" Process time: " + num3.setNum(JobList.at(i)->u32ProcessTime) +
			" Size: " + num4.setNum(JobList.at(i)->u32Size) + "\r\n").toUtf8()
		);
	}

	SaveFile.write("*****Unallocated List*****\r\n");
	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		SaveFile.write(("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark) + "\r\n").toUtf8()
		);
	}

	SaveFile.write("*****Allocated List*****\r\n");
	for (int i = 0; i < AllocatedList.size(); i++)
	{
		SaveFile.write(("Partition number: " + num1.setNum(AllocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(AllocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(AllocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(AllocatedList.at(i)->u32OccupyedMark) + "\r\n").toUtf8()
		);
	}
	SaveFile.close();
}

void Widget::ProcessFF()
{
	QString num1, num2, num3, num4;
	bool bInsertSuccessfull = false;

	Process();
	u32Timer++;

	ui.label->setText("First Fit:" + num1.setNum(u32Timer));
	ui.textEdit->clear();

	if (u32Timer == 1)
	{
		ui.BF_Btn->setEnabled(false);
		ui.WF_Btn->setEnabled(false);
		ui.Restore_Btn->setEnabled(true);
	}

	ui.textEdit->append("Waiting task:");
	ui.textEdit->append("Job number: " + num1.setNum(JobList.at(u32WaitingTask)->u32JobNum) +
		" Process time: " + num3.setNum(JobList.at(u32WaitingTask)->u32ProcessTime) +
		" Size: " + num4.setNum(JobList.at(u32WaitingTask)->u32Size)
	);

	ui.textEdit->append("\n\r*****Unallocated List*****");
	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		ui.textEdit->append("Partition number: " + num1.setNum(UnallocatedList.at(i)->u32PartitionNum) +
			" Start address: " + num2.setNum(UnallocatedList.at(i)->u32StartAddress) +
			" Length: " + num3.setNum(UnallocatedList.at(i)->u32Length) +
			" Mark: " + num4.setNum(UnallocatedList.at(i)->u32OccupyedMark)
		);
	}

	for (int i = 0; i < UnallocatedList.size(); i++)
	{
		if (UnallocatedList.at(i)->u32Length >= JobList.at(u32WaitingTask)->u32Size)
		{
			InsertJob(i, u32WaitingTask);
			bInsertSuccessfull = true;
			u32WaitingTask++;
			ui.textEdit->append("Insert successful!\n\r*****Allocated list*****");

			for (int i = 0; i < AllocatedList.size(); i++)
			{
				ui.textEdit->append("Partition number: " + num1.setNum(AllocatedList.at(i)->u32PartitionNum) +
					" Start address: " + num2.setNum(AllocatedList.at(i)->u32StartAddress) +
					" Length: " + num3.setNum(AllocatedList.at(i)->u32Length) +
					" Mark: " + num4.setNum(AllocatedList.at(i)->u32OccupyedMark)
				);
			}

			if (u32WaitingTask == (u32)JobList.size())
			{
				ui.textEdit->append("All jobs are inserted!");
				ui.FF_Btn->setEnabled(false);
				ui.Save_Btn->setEnabled(true);
				t->stop();
			}
			break;
		}
	}
	if (!bInsertSuccessfull)
	{
		ui.textEdit->append("Insert faild! Waiting for memory!");
	}
	this->update();
}
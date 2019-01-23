#include "PictureDecoder.h"

PictureDecoder::PictureDecoder(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void PictureDecoder::on_OpenFile_Btn_clicked()
{
	//QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("Allfile(*.*)"));
	QString fileName = "C:\\Users\\Darren Wong\\Documents\\GitHub\\target\\target01";
	QString currentFile;
	QImage image;
	QString num1, num2;
	QString OutputLine;
	unsigned char u8Output = 0;
	int  counter = 0;
	int PictureNum = 0;

	//ui.textEdit->append(fileName);

	for (PictureNum = 0; PictureNum < 1; PictureNum++) 
	{
		if (PictureNum < 10)
		{
			currentFile = fileName + "0" + num1.setNum(PictureNum) + ".bmp";
		}
		else
		{
			currentFile = fileName + num1.setNum(PictureNum) + ".bmp";
		}
		image = QImage(currentFile, nullptr);
		ui.textEdit->append("{");

		for (int i = 0; i < 288; i++)
		{
			for (int j = 0; j < 216; j++)
			{
				if (qGray(image.pixel(i, j)) > 0xaa)
				{
					u8Output &= 0xfe;
				}
				else
				{
					u8Output |= 0x01;
				}

				if (j % 8 == 7)
				{
					OutputLine += "0x" + num1.setNum(u8Output, 16) + ",";
					counter++;
				}

				u8Output = u8Output << 1;

				if (counter == 16)
				{
					ui.textEdit->append(OutputLine);
					OutputLine.clear();
					counter = 0;
				}
			}
		}

		ui.textEdit->append("},");
	}

}

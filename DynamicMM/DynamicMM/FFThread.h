#pragma once

#ifndef FFTHREAD_H
#define FFTHREAD_H

#include <QThread>
#include <qtimer.h>

class FFThread : public QThread
{
public:
	FFThread();
	void run(); //�����̳���QThread�麯�� run()
};

#endif // FFTHREAD_H
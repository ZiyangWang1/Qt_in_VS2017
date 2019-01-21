#pragma once

#ifndef FFTHREAD_H
#define FFTHREAD_H

#include <QThread>
#include <qtimer.h>

class FFThread : public QThread
{
public:
	FFThread();
	void run(); //ÉùÃ÷¼Ì³ĞÓÚQThreadĞéº¯Êı run()
};

#endif // FFTHREAD_H
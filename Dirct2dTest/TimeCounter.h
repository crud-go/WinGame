#pragma once
#include<windows.h>
class TimeCounter
{
public:
	TimeCounter();
	void Update();
	double GetTime();
	double sysFre;		// ��ʱ��Ƶ��
	double LastTime;	// ����ʱ��
};


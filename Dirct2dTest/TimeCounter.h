#pragma once
#include<windows.h>
class TimeCounter
{
public:
	TimeCounter();
	void Update();
	double GetTime();
	double sysFre;		// 计时器频率
	double LastTime;	// 基础时间
};


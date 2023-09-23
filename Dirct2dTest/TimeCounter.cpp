#include "TimeCounter.h"

TimeCounter::TimeCounter()
{
	LARGE_INTEGER temp_time;
	BOOL hr = QueryPerformanceFrequency(&temp_time);
	if (hr)
		sysFre = temp_time.QuadPart;	// ��ȡ��ʱ��Ƶ��

	memset(&temp_time, 0, sizeof(temp_time));

	hr = QueryPerformanceCounter(&temp_time);
	if (hr)
		LastTime = temp_time.QuadPart;	// ���û���ʱ��
}

void TimeCounter::Update()
{
	LARGE_INTEGER temp_time;
	QueryPerformanceCounter(&temp_time);
	LastTime = temp_time.QuadPart;

}

double TimeCounter::GetTime()
{

	LARGE_INTEGER temp_time;
	QueryPerformanceCounter(&temp_time);
	return ((double)temp_time.QuadPart - LastTime) / sysFre;
}


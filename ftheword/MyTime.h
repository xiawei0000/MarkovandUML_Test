#pragma once
#define MYTIMER_H  
#include <windows.h>  

class MyTime
{

private:
	LONGLONG _freq;
	LARGE_INTEGER _begin;
	LARGE_INTEGER _end;
public:
	long costTime;
	MyTime::MyTime()
	{
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		_freq = tmp.QuadPart;
		costTime = 0;
	}


	void MyTime::Start()
	{
		QueryPerformanceCounter(&_begin);
	}
	void MyTime::End()
	{
		QueryPerformanceCounter(&_end);
		costTime = (long)((_end.QuadPart - _begin.QuadPart) * 1000 / _freq);// ms

	}
	void MyTime::Reset()            // ¼ÆÊ±Çå0  
	{
		costTime = 0;
	}
};


#include<iostream>
#include<ctime>

#include<windows.h>
using namespace std;
const int maxn = 1e8;
int* a;
int main()
{
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时

	a = new int[maxn];
	for (int i = 0; i < maxn; i++)
	{
		*(a + i) = 1e9;
	}

	QueryPerformanceCounter(&nEndTime);//停止计时
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s
	cout << time * 1000 << "ms" << endl;
	return 0;
}
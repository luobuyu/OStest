#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;

struct Thread
{
	string name;
	int start, end, step;
	Thread(char* name, int start, int end, int step)
	{
		this->name = name;
		this->start = start;
		this->end = end;
		this->step = step;
	}
	void print()
	{
		for(int i = start; i != end; i+=step)
		{
			cout << name << ":" << i << endl;
			Sleep(500);
		}
	}
};

DWORD WINAPI print(LPVOID p)
{
	Thread* thread = (Thread*)p;
	thread->print();
	return 0;
}


int main()
{
	HANDLE th[2];
	Thread* thread1 = new Thread("thread1", 1, 1000, 1);
	Thread* thread2 = new Thread("thread2", 1000, 1, -1);
	th[0] = CreateThread(NULL, 0, print, (LPVOID)thread1, 0, NULL);
	th[1] = CreateThread(NULL, 0, print, (LPVOID)thread2, 0, NULL);
	WaitForMultipleObjects(2, th, true, INFINITE);
	CloseHandle(th[0]);
	CloseHandle(th[1]);

	return 0;
}

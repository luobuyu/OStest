#include<iostream>
#include<Windows.h>
#include<vector>
using namespace std;
const int MAXN = 5;
const int THREAD_NUM = 4;
vector<int> container;	// ����
CRITICAL_SECTION cs;	// �ٽ���
HANDLE Empty, Full;		// �ź���

DWORD WINAPI produce(LPVOID p)
{
	int id = *(int*)p;
	while (true)
	{
		WaitForSingleObject(Empty, INFINITE);
		EnterCriticalSection(&cs);
		container.push_back(10);
		Sleep(500);
		cout << "��ţ�" << id << ", �����˵�" << container.size() << "������" << ", ʣ��" << container.size() << "��" << endl;
		LeaveCriticalSection(&cs);
		ReleaseSemaphore(Full, 1, NULL);
	}
}

DWORD WINAPI consume(LPVOID p)
{
	int id = *(int*)p;
	while (true)
	{
		WaitForSingleObject(Full, INFINITE);
		EnterCriticalSection(&cs);
		Sleep(500);
		cout << "��ţ�" << id << ", �����˵�" << container.size() << "������" << ", ʣ��" << container.size() - 1 << "��" << endl;
		container.pop_back();
		LeaveCriticalSection(&cs);
		ReleaseSemaphore(Empty, 1, NULL);
	}
}

int main()
{
	InitializeCriticalSection(&cs);
	Empty = CreateSemaphore(NULL, MAXN, MAXN, NULL);
	Full = CreateSemaphore(NULL, 0, MAXN, NULL);
	HANDLE thread[THREAD_NUM];
	int ID[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++)
	{
		ID[i] = i + 1;
		if (i & 1)
			thread[i] = CreateThread(NULL, 0, produce, &ID[i], 0, NULL);
		else
			thread[i] = CreateThread(NULL, 0, consume, &ID[i], 0, NULL);
	}

	WaitForMultipleObjects(THREAD_NUM, thread, true, INFINITE);
	for (int i = 0; i < THREAD_NUM; i++)
	{
		CloseHandle(thread[i]);
	}

	CloseHandle(Empty);
	CloseHandle(Full);
	DeleteCriticalSection(&cs);
	return 0;
}
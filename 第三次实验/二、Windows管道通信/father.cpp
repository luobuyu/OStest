#include<iostream>
#include<Windows.h>

using namespace std;

int main()
{
	HANDLE readHandle, writeHandle;
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (!CreatePipe(&readHandle, &writeHandle, &sa, NULL))
	{
		cout << "创建管道失败" << endl;
		return -1;
	}
	else
	{
		cout << "管道创建成功" << endl;
	}


	STARTUPINFO startInfo;
	PROCESS_INFORMATION piInfo;
	ZeroMemory(&piInfo, sizeof(piInfo));
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	startInfo.wShowWindow = SW_SHOW;
	startInfo.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	startInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	startInfo.hStdInput = readHandle;
	
	TCHAR exe[] = TEXT("son.exe");
	if (!CreateProcess(NULL, exe, NULL, NULL, true, CREATE_NEW_CONSOLE, NULL, NULL, &startInfo, &piInfo))
	{
		cout << "子进程创建失败" << endl;
	}
	else
	{
		cout << "子进程创建成功" << endl;
		CloseHandle(piInfo.hThread);
		CloseHandle(piInfo.hProcess);
	}




	int buffer[105];
	for (int i = 1; i <= 100; i++)
	{
		buffer[i - 1] = i;
	}

	DWORD dwWrite = 0;
	if (!WriteFile(writeHandle, buffer, sizeof(buffer), &dwWrite, NULL))
	{
		cout << "写入失败" << endl;
	}
	else
	{
		cout << "成功写入数据" << endl;
	}

	Sleep(300);

	system("pause");
	return 0;
}
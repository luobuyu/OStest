#include<iostream>
#include<Windows.h>

using namespace std;
DWORD dwRead = 0;
const int size = 500;
int buffer[size];
int main()
{
	HANDLE readHandle = GetStdHandle(STD_INPUT_HANDLE);

	if (!ReadFile(readHandle, buffer, 400, &dwRead, NULL))
	{
		cout << "¶ÁÈ¡Ê§°Ü" << endl;
	}
	else
	{
		for(int i = 1; i <= 100; i++)
		{
			cout << buffer[i-1] << endl;
		}
	}
	Sleep(100000000);
	return 0;
}
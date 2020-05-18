#include<iostream>
#include<unistd.h>
using namespace std;

int main()
{
    pid_t childPid;
    childPid = fork();
    if(childPid == 0)
    {
        cout << "我是子进程" << endl;
        cout << "子进程ID：" << getpid() << "父进程ID：" << getppid() << endl;
    }
    else
    {
        cout << "我是父进程" << endl;
        cout << "父进程ID：" << getpid() << endl;
    }
    
    return 0;
}
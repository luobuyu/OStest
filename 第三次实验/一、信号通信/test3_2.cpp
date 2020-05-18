#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
using namespace std;
const int SIZE = 1024;
bool flag = true;
char * pshm = NULL;
void signHandlePa(int signum)
{
    exit(0);
}
int sum = 0;
void signHandleSon(int signnum)
{

    sum += atoi(pshm);
    
    cout << "你输入的是：" <<pshm << endl;
    cout << "当前sum=" << sum << endl;
    if(sum > 100)
    {
        cout << "My work done!" << endl;
    }

}

int main()
{
    pid_t child;
    key_t key = 0;
    int shmid = 0;  // 共享内存

    char buffer[SIZE] = {'\0'};
    char str[100];

    shmid = shmget((key_t)1234, 1024, 0644 | IPC_CREAT);
    if(shmid == -1)
    {
        cout << "共享内存创建失败" << endl;
        return -1;
    }

    pshm = (char *)shmat(shmid, NULL, 0);
    if(pshm == (void *) - 1)
    {
        cout << "映射失败" << endl;
        shmctl(shmid, IPC_RMID, NULL);
        return -1;
    }

    // 创建进程
    child = fork();
    if(child == -1)
    {
        cout << "创建进程失败！" << endl;
        shmctl(shmid, IPC_RMID, NULL);
        return -1;
    }
    else if (child > 0)
    {
        sleep(2);
        signal(SIGUSR1, signHandlePa);
        while (flag)
        {
            cin >> str;
            sprintf(pshm, "%s", str);
            kill(child, SIGUSR2);
        }
    }
    else
    {
        pid_t pid = getppid();
        signal(SIGUSR2, signHandleSon);
        while(sum <= 100);
        kill(pid, SIGUSR1);
        exit(0);
    }
    
    
    return 0;
}
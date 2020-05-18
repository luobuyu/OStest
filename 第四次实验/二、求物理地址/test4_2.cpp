#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/wait.h>
using namespace std;


/*
获取该程序中的某个变量的虚拟地址，
虚拟页号，页内偏移地址，物理页框号，
页内偏移地址，物理地址，并将它们打
印出来。
*/
int main()
{
    int a = 100;
    int pageSize = getpagesize();
    unsigned long vAddr = (unsigned long)&a;            // 1
    unsigned long vPageID = vAddr / pageSize; //  2
    unsigned long PageOffset = vAddr % pageSize; //  3
    unsigned long vOffSet = vPageID * sizeof(uint64_t);

    uint64_t item = 0;
    int file = open("/proc/self/pagemap", O_RDONLY);
    if(file == -1)
    {
        cout << "打开失败" << endl;
        return -1;
    }

    if(lseek(file, vOffSet, SEEK_SET) == -1)
    {
        cout << "lseek error" << endl;
        return -1;
    }
    if(read(file, &item, sizeof(uint64_t)) != sizeof(uint64_t))
    {
        cout << "read error" << endl;
        return -1;
    }
    if((((uint64_t)1 << 63) & item) == 0)//判断present是否为0
    {
        printf("page present is 0\n");
        return -1;
    }
    uint64_t pPageID = ((uint64_t)1 << 55) & item;  // 4
    unsigned long pAddr = pPageID * pageSize + PageOffset;
    /*
    获取该程序中的某个变量的虚拟地址，
虚拟页号，页内偏移地址，物理页框号，页内偏移地址，物理地址，并将它们打
印出来。
    */
    printf("pid = %d, 虚拟地址：%lx, 虚拟页号:%lu，页内偏移地址:%lx\n", getpid(), vAddr, vPageID, PageOffset);
    printf("物理页框号:%lu，页内偏移地址:%lx，物理地址:%lx\n", pPageID, PageOffset, pAddr);
    sleep(1000000000000);
    return 0;
}
#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

int main () {
	syscall(335, 4);
	return 0;
}



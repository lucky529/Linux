#include <iostream>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        printf("child : pid : %d ,ppid : %d\n",getpid(),getppid());
        sleep(5);
        exit(13);//return 13
    }
    else
    {
        printf("father : pid : %d ,ppid : %d\n",getpid(),getppid());
        int status = 0;
        while(1)
        {        
        int ret = waitpid(-1,&status,WNOHANG);
        if(ret < 0)
        {
            printf("wait error, wait ret: %d\n",ret);
        }
        else if(ret > 0)
        {
            printf("wait success...:%d\n",ret);
            printf("exit status....:%d\n",(status >> 8)&0xFF);
            printf("exit signal....:%d\n",status&0x7F);
            break;
        }
        else
        {
            sleep(1);//do other thing
            printf("father wait again!\n");
        }
        }
        sleep(5);
    }
    return 0;
}

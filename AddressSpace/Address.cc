#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int g_val = 100;
int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        g_val = 200;
        sleep(1);
        printf("Child:%d,%p\n",g_val,&g_val);
    }
    else
    {
        sleep(2);
        printf("Child:%d,%p\n",g_val,&g_val);
    }
    return 0;
}

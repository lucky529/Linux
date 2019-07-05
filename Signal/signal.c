#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void show(sigset_t* ct)
{
    int i = 1;
    for(;i <= 31;i++){
        if(sigismember(ct,i) == 1){
            printf("1");
        }
        else{
            printf("0");
        }
    }
    printf("\n");
}
int main()
{
    sigset_t ct,oct;
    sigemptyset(&ct);
    sigemptyset(&oct);

    sigaddset(&ct,2);
    sigprocmask(SIG_SETMASK,&ct,&oct);
    int count = 10;
    while(1)
    {
        sigset_t pending;
        sigemptyset(&pending);
        sigpending(&pending);
        show(&pending);
        sleep(1);
        if(count-- <= 0)
        {
            printf("recover signal!\n");
            sigprocmask(SIG_SETMASK,&oct,NULL);
        }
    }
    return 0;
}
//void handler(int signum)
//{
//    printf("cath sig : signum : %d\n",signum);
//}
//int main()
//{
//    signal(2,handler);
//    while(1)
//    {
//        printf("im am a process...!\n");
//        sleep(1);
//    }
//    return 0;
//}

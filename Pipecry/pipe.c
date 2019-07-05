#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
    int fd[2] = {0};
    pipe(fd);

    pid_t id = fork();
    if(id == 0) {
        close(fd[0]);
        int count = 0;
        char msg[] = "im child ... im alive";
        while(1) {
            write(fd[1],msg,strlen(msg));
            printf("%d\n",count+=strlen(msg));
            sleep(1);
            break;
        }
    }
    else {
        close(fd[1]);
        char buf[1024];
        while(1){
            ssize_t s = read(fd[0],buf,sizeof(buf)-1);
            if(s > 0){
                buf[s] = 0;
                printf("im father , got child %s\n",buf);
            }
            else if(s == 0){
                printf("read file end !\n"); break;
            }
            else{
                printf("read error!\n"); break;
            }
        }
        int status = 0;
        waitpid(id,&status,0);
        printf("sig : %d\n",status&0x7F);
    }
    return 0;
}

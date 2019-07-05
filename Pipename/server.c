#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
    mkfifo("fifo",0644);
    int fd = open("fifo",O_RDONLY);
    if(fd < 0){
        printf("open error\n");
        return 1;
    }
    char buf[1024];
    while(1){
        ssize_t s = read(fd,buf,sizeof(buf)-1);
        if(s > 0){
            buf[s] = 0;
            printf("%s\n",buf);
        }
        else if(s == 0){
            printf("client quit\n");
            break;
        }
        else{
            printf("read error\n");
            break;
        }
    }
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

int main()
{
    close(1);
    umask(0);
    int fd1 = open("log.txt1",O_WRONLY|O_APPEND);
    const char* msg = "hello world\n";
    write(fd1,msg,strlen(msg));
    fflush(stdout);
    close(fd1);
    return 0;
}

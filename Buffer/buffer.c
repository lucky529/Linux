#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{

    const char* msg1 = "hello printf\n";
    const char* msg2 = "hello write\n";
    printf(msg1);
    write(1,msg2,strlen(msg2));
    fork();
    return 0;
}

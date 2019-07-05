#include<stdio.h>
#include<unistd.h>
int main()
{
    int page = getpagesize();
    printf("%d\n",page);
    return 0;
}

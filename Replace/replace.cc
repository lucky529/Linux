#include<iostream>
#include<unistd.h>
using namespace std;

int main()
{
    execlp("ls","ls","-l","-a","-i",NULL);
    return 0;
}

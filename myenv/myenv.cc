#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, char* argv[],char* env[])
{
    int i = 0;
    for(;env[i];i++)
        printf("%d : %s\n",i,env[i]);
    return 0;
}

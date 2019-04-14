#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
using namespace std;

int main()
{
    pid_t id =  fork();
    if(id == 0)
    {
        while(1)
        {
            cout << "im child...."<<endl;
            sleep(1);
        }
    }
    else
    {
        int count = 0;
        while(1)
        {
            cout << "im father...."<<endl;
            sleep(2);
            if(count++ >=5)
            {
                exit(1);
            }
        }
    }
    return 0;
}

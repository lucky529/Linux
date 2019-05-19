#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

#define NUM 32
int main()
{
    char* argv[NUM];
    char buff[1024] = {0};
    for(;;){
        string command;
        string tips = "[xxx@localhost yyy]#";
        cout << tips;
        fgets(buff,sizeof(buff)-1,stdin);
        buff[strlen(buff)-1] = 0;
        argv[0] = strtok(buff," ");
        int i = 0;
        while(argv[i] != NULL)
        {
            i++;
            argv[i] = strtok(NULL," ");
        }
        pid_t id = fork();
        if(id == 0){
            cout << "child running ..."<<endl;
            execvp(argv[0],argv);
            exit(1);
        }
        else{
            int status = 0;
            waitpid(id,&status,0);
            cout << "exit code: "<<WEXITSTATUS(status)<<endl;
        }
    }
    return 0;
}

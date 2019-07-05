#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#define PATH "/tmp"
#define PRJ_ID 0x6666
#define SIZE 4096

int main()
{
    key_t k = ftok(PATH,PRJ_ID);
    if(k < 0){
        printf("ftok error!\n"); return 1;
    }
    int shm_id = shmget(k,SIZE,0);
    if(shm_id < 0){
        printf("shmget error !\n");
        return 2;
    }
    char* p = (char*)shmat(shm_id,NULL,0);
    int i = 0;
    while(i < SIZE){
        p[i] = 'a'+i;
        i++;
        p[i] = 0;
        sleep(1);
    }
    shmdt(p);
    return 0;
}

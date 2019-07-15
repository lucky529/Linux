#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int goal = 0;
pthread_mutex_t mutx;
void* handle(void* arg)
{
    int count = 10000000;
    pthread_mutex_lock(&mutx);
    while(count--){
        goal++;
    }
    pthread_mutex_unlock(&mutx);
    return (void*)1;
}
int main()
{
    pthread_t t1,t2;
    pthread_mutex_init(&mutx,NULL);
    pthread_create(&t1,NULL,handle,NULL);
    pthread_create(&t2,NULL,handle,NULL);

    sleep(1);
    cout << goal <<endl;

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutx);
    return 0;
}

#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

void* handle(void* arg)
{
    pthread_detach(pthread_self());
    int i = 3;
    while(i--){
        cout << "i am new Thread" <<endl;
    }
    pthread_cancel(pthread_self());
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,handle,(void*)"thread 1");

    void* status;
    sleep(1);
    int ret = pthread_join(tid,&status);
    cout << (int)status<<" :" <<ret <<endl;
    return 0;
}

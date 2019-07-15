#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

using namespace std;
class BlockQueue{
    private:
        queue<int> q;
        pthread_cond_t cond;
        pthread_mutex_t lock;
    private:
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnLockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        bool isEmpty()
        {
            return q.size() == 0 ? true : false;
        }
        void ThreadWait()
        {
            pthread_cond_wait(&cond,&lock);
        }
        void WakeOneThread()
        {
            pthread_cond_signal(&cond);
        }
    public:
        BlockQueue()
        {
            pthread_mutex_init(&lock,NULL);
            pthread_cond_init(&cond,NULL);
        }
        void PushData(const int& data)
        {
            LockQueue();
            q.push(data);
            UnLockQueue();
            cout << "product run done, data push sucess " << data <<endl;
            WakeOneThread();
        }
        void PopData(int& data)
        {
            LockQueue();
            while(isEmpty()){
                ThreadWait();
            }
            data = q.front();
            q.pop();
            UnLockQueue();
            cout << "consume run done, data pop sucess : " << data <<endl;
        }
        ~BlockQueue()
        {
            pthread_cond_destroy(&cond);
            pthread_mutex_destroy(&lock);
        }
};

void* product(void* arg)
{
    BlockQueue* bq = (BlockQueue*)arg;
    srand((unsigned long)time(NULL));
    while(1)
    {
        int data = rand()%100 + 1;
        bq->PushData(data);
        sleep(1);
    }
}
void* consume(void* arg)
{
    BlockQueue* bq = (BlockQueue*)arg;
    while(1)
    {
        int d;
        bq->PopData(d);
    }
}
int main()
{
    BlockQueue bq;
    pthread_t p,c;
    pthread_create(&p,NULL,product,(void*)&bq);
    pthread_create(&c,NULL,consume,(void*)&bq);

    pthread_join(p,NULL);
    pthread_join(c,NULL);
}

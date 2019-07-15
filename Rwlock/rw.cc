#include <iostream>
#include <pthread.h>
#include <unistd.h>
int data = 0;
pthread_rwlock_t rw;
void* reader(void* arg)
{
    for(;;){
        pthread_rwlock_rdlock(&rw);
        std::cout << "reader read done : " << data << std::endl;
        pthread_rwlock_unlock(&rw);
        sleep(1);
    }
}

void* writer(void* arg)
{
    for(;;){
        pthread_rwlock_wrlock(&rw);
        std::cout << "writer write done : " << ++data << std::endl;
        pthread_rwlock_unlock(&rw);
        sleep(1);
    }
}

int main()
{
    pthread_rwlock_init(&rw, NULL);
    pthread_t r, w;
    pthread_create(&r,NULL,reader,NULL);
    pthread_create(&w,NULL,writer,NULL);

    pthread_join(r,NULL);
    pthread_join(w,NULL);
    pthread_rwlock_destroy(&rw);
    return 0;
}

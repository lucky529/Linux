#include<iostream>
#include<pthread.h>
#include<queue>
using namespace std;

typedef void(*handler_t)(int);
class Task{
    private:
        int sock;
        handler_t handler;
    public:
        Task()
        {

        }
        void InitTask(int _sock,handler_t _h)
        {
            sock = _sock;
            handler = _h;
        }
        void Run()
        {
            handler(sock);
        }
        ~Task()
        {

        }
};
class ThreadPool{
private:
	int thread_nums;//线程池中的线程总数
	int idle_nums;//当前闲置线程的数量
	queue<Task> task_queue;//线程所要处理的任务队列
	pthread_mutex_t lock;
	pthread_cond_t cond;
public:
	void LockQueue()
	{
		pthread_mutex_lock(&lock);
	}
	void UnlockQueue()
	{
		pthread_mutex_unlock(&lock);
	}
	bool QueueIsEmpty()
	{
		return task_queue.size() == 0 ? true : false;
	}
	void ThreadIdle()
	{
		idle_nums++;//一旦进入等待状态闲置线程加一
		pthread_cond_wait(&cond, &lock);
		idle_nums--;
	}
	void WakeupThread()
	{
		pthread_cond_signal(&cond);
	}
	void PopTask(Task& t)
	{
		t = task_queue.front();
		task_queue.pop();
	}
public:
	ThreadPool(int _num = 5) :thread_nums(_num), idle_nums(0)
	{
		pthread_mutex_init(&lock, NULL);
		pthread_cond_init(&cond, NULL);
	}
	static void* ThreadRotinue(void* arg)
	{
		pthread_detach(pthread_self());
		ThreadPool *tp = (ThreadPool*)arg;
		for (;;){
			tp->LockQueue();
			while (tp->QueueIsEmpty()){
				tp->ThreadIdle();
			}
			Task t;
			tp->PopTask(t);
			tp->UnlockQueue();
			t.Run();
		}
	}
	void InitThreadPool()//创建所需要的线程
	{
		pthread_t t;
		for (auto i = 0; i < thread_nums; i++)
		{
			pthread_create(&t, NULL, ThreadRotinue, this);
		}
	}
	void PushTask(const Task& t)
	{
		LockQueue();
		task_queue.push(t);
		WakeupThread();
		UnlockQueue();
	}
	~ThreadPool()
	{
		pthread_mutex_destroy(&lock);
		pthread_cond_destroy(&cond);
	}
};

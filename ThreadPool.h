#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include "Define.h"

template <typename T>
class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    void AddTask(T task);

private:
    static void work(void * arg);

private:
    std::queue<T> m_taskQueue;
    std::vector<std::thread> m_threadIDs;

    atomic_int m_busyNum;
    atomic_int m_liveNum;

    std::mutex m_mutex;
};

template <typename T>
ThreadPool::ThreadPool()
{
    for (size_t i = 0; i < POOLSIZE; i++)
    {
        m_threadIDs[i] = std::thread(work, this);
    }
    
}

template <typename T>
ThreadPool::~ThreadPool()
{

}

template <typename T>
void ThreadPool::AddTask(T task)
{
    unique_lock<std::mutex> poolLock(m_mutex);
    m_taskQueue.emplace(task);
}

template <typename T>
void Thread::work(void * arg)
{

}

#endif
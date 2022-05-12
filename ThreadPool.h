#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <thread>
#include <condition_variable>
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
    std::condition_variable m_cond;
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
    unique_lock<std::mutex> poolLock(m_mutex);

    m_cond.notify_all();

    for (auto th : m_threadIDs)
    {
        if (th.joinable())
            th.join();
    }
}

template <typename T>
void ThreadPool::AddTask(T task)
{
    unique_lock<std::mutex> poolLock(m_mutex);

    m_taskQueue.emplace(task);
    m_cond.notify_one();
}

template <typename T>
void Thread::work(void * arg)
{
    unique_lock<std::mutex> poolLock(m_mutex);

    T task;
    if (m_taskQueue.empty())
    {
        m_cond.wait(poolLock);
    }
    else
    {
        task = m_taskQueue.front();
        m_taskQueue.pop();
    }
    
    if (task)
    {
        task.doWork();
    }
    
}

#endif
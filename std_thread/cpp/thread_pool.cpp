#include <queue>
#include <thread>
#include "thread_pool.h"

using namespace std;

namespace ldslds449
{

  Thread_Pool::Thread_Pool(int num_of_thread) : threads(nullptr)
  {
    size = num_of_thread;
    threads = new thread[num_of_thread];
    for (int i = 0; i < num_of_thread; ++i)
    {
      q.push(i);
    }
  }

  Thread_Pool::~Thread_Pool()
  {
    if (threads != nullptr)
    {
      delete[] threads;
    }
  }

  Thread_Pool &Thread_Pool::operator=(const Thread_Pool &pool)
  {
    this->size = pool.size;
    this->threads = new thread[pool.size];
    return *this;
  }

  int Thread_Pool::getThread()
  {
    unique_lock<mutex> lock(q_mtx);
    q_cond.wait(lock, [&]
                { return !q.empty(); });
    int id = q.front();
    q.pop();
    return id;
  }

  void Thread_Pool::addThread(int id)
  {
    {
      lock_guard<mutex> lock(q_mtx);
      q.push(id);
    }
    q_cond.notify_one();
  }

  int Thread_Pool::getSize() const
  {
    return size;
  }

  thread &Thread_Pool::threadInstance(int id)
  {
    return threads[id];
  }

}
#include <thread>
#include <chrono>
#include <future>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "thread_pool.h"

using namespace std;
using namespace ldslds449;

using time_stamp = chrono::_V2::system_clock::time_point;

#define NUM_OF_THREAD 4
#define NUM_OF_TASK 20
#define SLEEP_SECOND 3

void task(int thread_id, int task_id, Thread_Pool &pool, promise<time_stamp> &&p)
{
  stringstream ss;
  ss << "Task " << task_id << " in Thread " << thread_id << "\n";
  cout << ss.str();
  cout.flush();

  this_thread::sleep_for(chrono::seconds(SLEEP_SECOND));

  // return values
  p.set_value(chrono::system_clock::now());

  // release thread
  pool.addThread(thread_id);
}

int main()
{
  Thread_Pool pool(NUM_OF_THREAD);
  promise<time_stamp> pros[NUM_OF_TASK];
  future<time_stamp> data[NUM_OF_TASK];

  for (int i = 0; i < NUM_OF_TASK; ++i)
  {
    int id = pool.getThread();
    if (pool.threadInstance(id).joinable())
    {
      pool.threadInstance(id).join();
    }
    data[i] = move(pros[i].get_future());
    thread t(&task, id, i + 1, ref(pool), move(pros[i]));
    pool.threadInstance(id).swap(t);
  }

  for (int i = 0; i < pool.getSize(); ++i)
  {
    pool.threadInstance(i).join();
  }

  for (int i = 0; i < NUM_OF_TASK; ++i)
  {
    auto tmp = chrono::system_clock::to_time_t(data[i].get());
    cout << "Task " << i + 1 << " Finish At ";
    cout << put_time(localtime(&tmp), "%Y-%m-%d %T") << "\n";
    cout.flush();
  }

  return 0;
}
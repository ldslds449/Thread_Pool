#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

namespace ldslds449
{

  class Thread_Pool
  {
  private:
    queue<int> q;
    thread *threads;
    unsigned size;
    mutex q_mtx;
    condition_variable q_cond;

  public:
    Thread_Pool(int num_of_thread);
    ~Thread_Pool();
    Thread_Pool &operator=(const Thread_Pool &pool);
    int getThread();
    void addThread(int id);
    int getSize() const;
    thread &threadInstance(int id);
  };

}
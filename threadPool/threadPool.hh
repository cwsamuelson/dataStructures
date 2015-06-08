#ifndef __THREAD_POOL_HH__
#define __THREAD_POOL_HH__

#include<queue>
#include<functional>
#include<vector>
#include<mutex>
#include<thread>

class threadPool:public std::queue<std::function<void()>>{
private:
  std::vector<std::thread> pool;
  std::mutex mtxSelf;
  bool isWorking;

  void threadFn();

public:
  threadPool(unsigned int nThreads);
  ~threadPool();
};

#include"threadPool.cc"

#endif


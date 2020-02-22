#ifndef GALACTICSTRUCTURES_THREADPOOL_HH
#define GALACTICSTRUCTURES_THREADPOOL_HH

#include <memory>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <tuple>
#include <future>

// it is possible to have a variant that gets results out as well with future/promise
//! @todo forward exceptions
namespace gsw{

class threadPool{
public:
  using work = std::function<void()>;

private:
  using internal_work = std::function<void(bool&)>;
  std::mutex mMutex;
  std::condition_variable mCV;
  std::queue<internal_work> mWorkQueue;
  std::vector<std::tuple<std::thread, std::shared_ptr<bool>>> mWorkers;

  void enqueueWork(const internal_work& iw){
    std::lock_guard lk(mMutex);

    mWorkQueue.emplace(iw);

    mCV.notify_one();
  }

public:
  explicit
  threadPool(size_t size = 1)
  {
    for(size_t i = 0; i < size; ++i)
    {
      auto rnng = std::make_shared<bool>(false);
      mWorkers.emplace_back(
        [&, running = rnng]()
        {
          *running = true;

          while(*running)
          {
            std::unique_lock lk(mMutex);
            mCV.wait(lk, [&](){ return !mWorkQueue.empty(); });

            try
            {
              auto work = mWorkQueue.front();
              mWorkQueue.pop();

              work(*running);
            } catch(...){
              //what do?
            }
          }
        }, rnng
      );
    }
  }

  ~threadPool()
  {
    for(auto& [worker, control] : mWorkers)
    {
      enqueueWork([](bool& b){ b = false; });
    }

    for(auto& [worker, _] : mWorkers){
      if(worker.joinable()){
        worker.join();
      }
    }
  }

  void addWork(const work& w)
  {
    enqueueWork([=](bool&){ w(); });
  }
};

template<typename T>
class workerThread{
public:
  using context = T;
  using work = std::function<void(context&)>;

private:
  // threading tools
  std::mutex mMutex;
  std::condition_variable mCV;
  std::thread mWorkThread;

  // execution tools
  std::queue<work> mWorkQueue;
  bool mRunning = false;
  context mContext;

  void
  thread_func()
  {
    mRunning = true;

    while(mRunning)
    {
      std::unique_lock lk(mMutex);
      mCV.wait(lk, [&](){ return !mWorkQueue.empty(); });

      try
      {
        auto work = mWorkQueue.front();
        mWorkQueue.pop();

        work(mContext);
      }
      catch(...)// all exceptions must be caught so the thread doesn't die silently
      {
        //how to handle errors?
      }
    }
  }

public:
  workerThread()
    : mWorkThread(std::bind(&workerThread::thread_func, this))
  {}

  template<typename U>
  explicit
  workerThread(U&& u)
    : mContext(std::forward(u))
    , mWorkThread(std::bind(&workerThread::thread_func, this))
  {}

  ~workerThread()
  {
    stop();
  }

  void
  stop()
  {
    addWork(
      [this](context&)
      {
        mRunning = false;
      }
    );

    if(mWorkThread.joinable())
    {
      mWorkThread.join();
    }
  }

  void
  addWork(const work& w)
  {
    std::lock_guard lk(mMutex);

    mWorkQueue.emplace(w);

    mCV.notify_one();
  }
};
/*
template<typename T>
class resultsPool{
public:
  using work = std::function<T()>;

private:
  std::mutex mMutex;
  std::condition_variable mCV;
  std::queue<std::tuple<work, std::promise<T>>> mWorkQueue;

public:
  std::future<T>
  enqueueWork(work w)
  {
    std::lock_guard lk(mMutex);

    mWorkQueue.emplace({w, /* a promise*//*});

    mCV.notify_one();
  }
};

*/
}

#endif //GALACTICSTRUCTURES_THREADPOOL_HH


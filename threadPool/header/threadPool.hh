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

/*!
 * @todo figure out rule-of-5-stuff
 */
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
              //! @todo determine error handling
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

  void thread_func()
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
        //! @todo determine how to handle errors
      }
    }
  }

public:
  workerThread()
    : workerThread(std::move(context()))
  {}

  template<typename U>
  explicit
  workerThread(U&& u)
    : mContext(std::forward<U>(u))
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

template<typename T>
class resultsPool{
public:
  using work = std::function<T()>;

private:
  using internal_work = std::function<T(bool&)>;

  std::mutex mMutex;
  std::condition_variable mCV;

  std::queue<std::tuple<internal_work, std::promise<T>>> mWorkQueue;
  std::vector<std::tuple<std::thread, std::shared_ptr<bool>>> mWorkerThreads;

  void enqueueWork(const internal_work& iw){
    std::lock_guard lk(mMutex);

    mWorkQueue.emplace(iw, std::promise<T>());

    mCV.notify_one();
  }

public:
  explicit
  resultsPool(size_t size = 1)
  {
    for(size_t i = 0; i < size; ++i){
      auto rnng = std::make_shared<bool>(false);

      mWorkerThreads.emplace_back(
        [this, running = rnng](){
            *running = true;

            while(*running)
            {
              std::unique_lock lk(mMutex);
              mCV.wait(lk, [&](){ return !mWorkQueue.empty(); });

              auto [work, p] = std::move(mWorkQueue.front());
              mWorkQueue.pop();

              try
              {
                p.set_value(work(*running));
              }
              catch(...)// all exceptions must be caught so the thread doesn't die silently
              {
                p.set_exception(std::current_exception());
              }
            }
        }, rnng);
    }
  }

  ~resultsPool(){
    for(auto& [worker, control] : mWorkerThreads)
    {
      enqueueWork([](bool& b){ b = false; return T(); });
    }

    for(auto& [worker, _] : mWorkerThreads){
      if(worker.joinable()){
        worker.join();
      }
    }
  }

  std::future<T> addWork(const work& w)
  {
    enqueueWork([=](bool&){ return w(); });

    return std::get<1>(mWorkQueue.back()).get_future();
  }
};

}

#endif //GALACTICSTRUCTURES_THREADPOOL_HH


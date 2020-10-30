#ifndef __TIMER_H__
#define __TIMER_H__

#include<functional>
#include<thread>
#include<future>
#include <condition_variable>

namespace gsw {

class TimerCancelled : public std::runtime_error{
public:
  TimerCancelled()
    : std::runtime_error("Timer was cancelled before it completed, and before delayed action could be taken.")
  {}
};

/*! Timer facility for delayed and scheduled function calls
 *
 * @todo see notes in cppreference async about multiple sequential async calls
 * @todo might be nice to have a cancel per event, so that I can schedule 2 events, and cancel them independently
 * this might actually call for factory pattern, where timers are created by the factory, and the only method
 * on timer is just cancel, or maybe a 'time until' counter
 */
class timer {
private:
  bool mCancel = false;
  std::mutex mMutex;
  std::condition_variable mConVar;


public:
  template<typename T> using callback = std::function<T()>;

  /*! Call a function repeatedly at an interval until cancelled
   *
   * @tparam Rep type forwarded to duration
   *
   * @tparam Period type forwarded to duration
   *
   * @param fn Callback to be called repeatedly at an interval
   *
   * @param duration The interval at which fn will be called
   */
  template<typename Rep, typename Period>
  void interval(callback<void> fn, const std::chrono::duration<Rep, Period>& duration) {
    mCancel = false;

    std::thread t([this, fn = std::move(fn), duration]()
                    {
                      while(true) {
                        std::this_thread::sleep_for(duration);
                        if(mCancel) {
                          break;
                        }
                        fn();
                      }
                    });
    t.detach();
  }

  /*! Call a function at some relative time in the future
   *
   * @tparam Rep type forwarded to duration
   *
   * @tparam Period type forwarded to duration
   *
   * @tparam callback_function Function callback type
   *
   * @param fn Function that will be called later
   *
   * @param duration time to wait until calling fn
   *
   * @return A future with which the result of fn can be retrieved
   */
  template<typename Rep, typename Period, typename callback_function>
  auto delayed(callback_function fn,
               const std::chrono::duration<Rep, Period>& duration){
    mCancel = false;

    return std::async(std::launch::async, [this, fn = std::move(fn), duration]()
      {
        std::unique_lock lk(mMutex);
        if(!mConVar.wait_for(lk, duration, [this](){ return mCancel; })){
          return fn();
        } else {
          throw TimerCancelled();
        }
      });
  }

  /*! Call a function at some specified time in the future
   *
   * @tparam clock Type forwarded to time_point
   *
   * @tparam duration Type forwarded to time_point
   *
   * @tparam callback_function Function callback type
   *
   * @param fn Function that will be called at time
   *
   * @param time point in time to call fn
   *
   * @return A future with which the result of fn can be retrieved
   */
  template<typename clock, typename duration, typename callback_function>
  auto schedule(callback_function fn,
                const std::chrono::time_point<clock, duration>& time){
    mCancel = false;

    return std::async(std::launch::async, [this, fn = std::move(fn), time]()
      {
        std::unique_lock lk(mMutex);
        if(!mConVar.wait_until(lk, time, [this](){ return mCancel; })){
          return fn();
        } else {
          throw TimerCancelled();
        }
      });
  }

  void cancel(){
    mCancel = true;
    mConVar.notify_all();
  }
};

}

#endif

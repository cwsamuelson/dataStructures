#ifndef __TIMER_H__
#define __TIMER_H__

#include<functional>
#include<thread>
#include<future>

class timer{
private:
  bool mCancel = false;

public:
  template<typename T>
  using callback = std::function<T()>;

  template<typename Rep, typename Period, typename T>
  void
  interval( callback<T> fn, const std::chrono::duration<Rep, Period>& duration ){
    mCancel = false;

    std::thread t( [=](){
      while( true ){
        std::this_thread::sleep_for( duration );
        if( mCancel ){
          break;
        }
        fn();
      }
    });
    t.detach();
  }

  template<typename Rep, typename Period, typename T>
  std::future<T>
  delayed( callback<T> fn, const std::chrono::duration<Rep, Period>& duration ){
    mCancel = false;

    return std::async( std::launch::async, [=](){
      std::this_thread::sleep_for( duration );
      if( !mCancel ){
        return fn();
      }
    } );
  }

  template<typename clock, typename duration, typename T>
  std::future<T>
  schedule( callback<T> fn, const std::chrono::time_point<clock, duration>& time ){
    mCancel = false;

    return std::async( std::launch::async, [=](){
      std::this_thread::sleep_until( time );
      if( !mCancel ){
        return fn();
      }
    });
  }
};

#endif

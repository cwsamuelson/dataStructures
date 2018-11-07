#ifndef __TIMER_H__
#define __TIMER_H__

#include<functional>
#include<thread>
#include<future>

/*!
 * see notes in cppreference async about multiple sequential async calls
 */
class timer{
private:
  bool mCancel = false;

public:
  template<typename T>
  using callback = std::function<T()>;

  template<typename Rep, typename Period>
  void
  interval( callback<void> fn, const std::chrono::duration<Rep, Period>& duration ){
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

  template<typename Rep, typename Period, typename callback_function>
  auto
  delayed( callback_function fn, const std::chrono::duration<Rep, Period>& duration )->decltype( std::async( std::launch::async, fn ) ){
    mCancel = false;

    return std::async( std::launch::async, [=](){
      std::this_thread::sleep_for( duration );
      if( !mCancel ){
        return fn();
      }
    } );
  }

  template<typename clock, typename duration, typename callback_function>
  auto
  schedule( callback_function fn, const std::chrono::time_point<clock, duration>& time )->decltype( std::async( std::launch::async, fn ) ){
    mCancel = false;

    return std::async( std::launch::async, [=](){
      std::this_thread::sleep_until( time );
      if( !mCancel ){
        return fn();
      }
    } );
  }
};

#endif

#ifndef __TIMER_H__
#define __TIMER_H__

#include<functional>
#include<thread>

class timer{
private:
  bool mCancel = false;

public:
  using callback = std::function<void()>;

  template<typename Rep, typename Period>
  void
  interval( callback fn, const std::chrono::duration<Rep, Period>& duration ){
    mCancel = false;

    std::thread t( [=](){
      while( mCancel ){
        std::this_thread::sleep_for( duration );
        if( mCancel ){
          break;
        }
        fn();
      }
    });
    t.detach();
  }

  template<typename Rep, typename Period>
  void
  delayed( callback fn, const std::chrono::duration<Rep, Period>& duration ){
    std::thread t( [=](){
      std::this_thread::sleep_for( duration );
      if( !mCancel ){
        fn();
      }
    } );
    t.detach();
  }

  template<typename clock, typename duration>
  void
  schedule( callback fn, const std::chrono::time_point<clock, duration>& time ){
    std::thread t( [=](){
      std::this_thread::sleep_until( time );
      if( !mCancel ){
        fn();
      }
    });
    t.detach();
  }
};

#endif

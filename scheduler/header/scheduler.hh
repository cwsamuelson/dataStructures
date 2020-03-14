#ifndef __SCHEDULER_HH__
#define __SCHEDULER_HH__

#include<functional>

#include<unit.hh>
#include<ratio.hh>

namespace gsw {

class scheduler {
public:
  using tick_rate = decltype(tick<double>() / time<double>());

  using callback = std::function<void()>;

private:
  time<double> mCounter;
  callback mCall;
  tick_rate mRate;

public:
  scheduler(callback cb, tick_rate rate)
          : mCounter(0.0)
          , mCall(cb)
          , mRate(rate) {
  }

  void update(time<double> t) {
    mCounter += t;

    //this allows t to trigger multiple events.
    while((mCounter * mRate) > 1) {
      //the amount of time for one tick, given mRate
      mCounter -= ((1.0 / mRate) * tick<double>(1));

      mCall();
    }
  }
};

}

#endif

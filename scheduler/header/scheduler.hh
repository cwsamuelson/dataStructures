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
  scheduler(callback cb, tick_rate rate);

  void update(time<double> t);
};

}

#endif

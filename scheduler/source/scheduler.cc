#include <scheduler.hh>

namespace gsw {

scheduler::scheduler(callback cb, scheduler::tick_rate rate)
        : mCounter(0.0)
        , mCall(std::move(cb))
        , mRate(rate) {
}

void scheduler::update(gsw::time<double> t){
  mCounter += t;

  //this allows t to trigger multiple events.
  while((mCounter * mRate) > 1) {
    //the amount of time for one tick, given mRate
    mCounter -= ((1.0 / mRate) * tick<double>(1));

    mCall();
  }
}


}

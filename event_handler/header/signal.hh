#ifndef GALACTICSTRUCTURES_SIGNAL_HH
#define GALACTICSTRUCTURES_SIGNAL_HH

#include <event_handler.hh>

#include <functional>
#include <future>

namespace gsw{

template<typename T>
class signal;

// the signal class does well to simulate a public method/function
// to do this as a private method, currently you should use triggers/channels
// private trigger, and public (or public access to) the channel

//! @TODO It might be cool to use combiners in signals?
// this is tricky/weird since there's 2 events to be combined
// and where do the results go?  currently the return value is the result of
// the actual action, so where do the combined results belong?
template<typename R, typename ...Args>
class signal<R(Args...)>{
public:
  using before_trigger_t = gsw::event_trigger<void(Args...)>;
  using after_trigger_t = gsw::event_trigger<void(Args...)>;
  using trigger_t = after_trigger_t;

private:
  using before_channel_t = typename before_trigger_t::channel_t;
  using after_channel_t = typename after_trigger_t::channel_t;
  using channel_t = after_channel_t;

public:
  using before_handler_t = typename before_channel_t::handler;
  using after_handler_t = typename after_channel_t::handler;
  using handler_t = after_handler_t;

  using action_t = std::function<R(Args...)>;

private:
  before_trigger_t mPreTrigger;
  after_trigger_t mPostTrigger;
  action_t mAction;

public:
  /*signal(R(*p)(Args...))
    : signal(p)
  {}*/

  signal(action_t action)
    : mAction(std::move(action))
  {}
  // this type is intended to be part of a public interface to interact with, but
  // we don't want the signal removed/moved off an object it was created for,
  // BUT we don't want to prevent the containing type to not be movable/copyable
  // solution may be 'weird' copy/move.
  // maybe normal move, but copy will clear out handlers in the new copy, so that
  // the new one doesn't notify objects that don't care?
  // or should we expect those objects to care?
  // food for thought; for now we prevent all
  signal(const signal&) = delete;
  signal(signal&&) = delete;
  signal& operator=(const signal&) = delete;
  signal& operator=(signal&&) = delete;

  //! @TODO should args... be forwarded?
  // reflex says yes, but which gets forwarded?
  // optimally the action would be forwarded, but that could invalidate vars for
  // the post operation.
  //! @TODO should R be required to be copyable?
  // it's pretty much treated as guaranteed copyable here, but maybe there's
  // another solution to forward its result after the post trigger is fired
  //
  // not sure, but using futures may be better than explict copy?
  auto operator()(Args... args){
    mPreTrigger.fire(args...);

    //!@NOTE using futures here works well to handle void results
    // I originally did this to work with copyable types before realizing
    // worrying about that before it occurred may be silly, however the case of
    // void results is clear/necessary, and occurs in unit tests
    auto f = std::async(std::launch::deferred, mAction, args...);
    f.wait();

    mPostTrigger.fire(args...);

    return f.get();
  }

  auto& pre(){
    return *mPreTrigger.getChannel().lock();
  }

  auto& post(){
    return *mPostTrigger.getChannel().lock();
  }

  void subscribe(handler_t handler){
    post().subscribe(handler);
  }
};

}

#endif //GALACTICSTRUCTURES_SIGNAL_HH

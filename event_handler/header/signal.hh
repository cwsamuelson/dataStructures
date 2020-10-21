#ifndef GALACTICSTRUCTURES_SIGNAL_HH
#define GALACTICSTRUCTURES_SIGNAL_HH

#include <event_handler.hh>

#include <functional>
#include <future>

namespace gsw{

template<typename T>
class signal;

template<typename R, typename ...Args>
class signal<R(Args...)>{
public:
  using before_trigger_t = gsw::event_trigger<Args...>;
  using after_trigger_t = gsw::event_trigger<Args...>;
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

    auto f = std::async(mAction, args...);
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

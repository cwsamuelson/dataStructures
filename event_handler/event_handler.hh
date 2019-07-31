#ifndef __EVENT_HANDLER__HH__
#define __EVENT_HANDLER__HH__

/*!
 * @example test-events.cc
 */

#include<map>
#include<functional>
#include<utility>

#include<tuple.hh>

namespace gsw{

/*! Event channel system
 *
 * @tparam Args...
 */
template<typename ...Args>
class event_channel{
public:
  class event_handler{
  public:
    using counter_t = unsigned long long;
    using handler = std::function<void( event_channel&, counter_t, Args... )>;
    friend class event_channel;

  private:
    event_channel& mChannel;
    handler mHandler;
    counter_t mCounter;

    event_handler( event_channel channel, counter_t counter, handler handle )
      : mChannel( channel )
      , mHandler( handle )
      , mCounter( counter ){
    }

  public:
    event_handler(const event_handler& from)
      : mChannel(from.mChannel)
      , mHandler(from.mHandler)
      , mCounter(from.mCounter)
    {}

    event_handler(event_handler&& from)
      : mChannel(from.mChannel)
      , mHandler(std::move(from.mHandler))
      , mCounter(std::move(from.mCounter))
    {}

    //mChannel cannot be reassigned!
    // some other solution is needed (ref wrapper?)
    event_handler&
    operator=(const event_handler& from){
      //mChannel = from.mChannel;
      mHandler = from.mHandler;
      mCounter = from.mCounter;
    }

    event_handler&
    operator=(event_handler&& from){
      //mChannel = from.mChannel;
      mHandler = std::move(from.mHandler);
      mCounter = std::move(from.mCounter);
    }

    void
    operator()( Args... args ){
      mHandler( mChannel, mCounter, args... );
    }

    bool
    operator==( event_handler other ) const{
      return ( mCounter == other.mCounter )
          && ( mChannel == other.mChannel );
    }

    bool
    operator!=( event_handler other ) const{
      return !( *this == other );
    }
  };

  /*!
   */
  using counter_t = unsigned long long;

  /*!
   * @todo wrap std::function into something that contains counter
   *    this will allow operator -= to identify which handler to use
   */
  using handler = typename event_handler::handler;

  /*!
   * @tparam N
   */
  template<size_t N>
  using arg_types = tuple_element<N, tuple<Args...> >;

private:
  std::map<counter_t, event_handler> handlers;
  counter_t idCounter = 0;

public:
  event_channel() noexcept = default;

  event_channel(const event_channel&) = default;

  event_channel(event_channel&&) = default;

  ~event_channel() noexcept = default;

  event_channel&
  operator=(const event_channel&) = default;

  event_channel&
  operator=(event_channel&&) noexcept = default;

  /*! Register new handler
   *
   * @param handler
   *
   * @return
   */
  event_channel&
  operator+=( const handler& handler ){
    enlist( handler );
 
    return *this;
  }

  /*! Register new handler
   *
   * @param handler
   *
   * @return
   */
  event_handler&
  enlist( const handler& handler ){
    handlers.insert({idCounter, event_handler( *this, idCounter, handler )});

    return handlers.at(idCounter++);
  }

  /*! Unregister a previously registered handler
   *
   * @param handle
   */
  void
  delist( const event_handler& handler ){
    for(auto& [id, hndl] : handlers){
      if(hndl == handler){
        handlers.erase(id);
      }
    }
  }

  void
  delist(counter_t id){
    handlers.erase(id);
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel&
  operator-=( const event_handler& handler ){
    delist( handler );

    return *this;
  }

  /*! Fire the event!
   *
   * @param args Arguments to pass on to handlers
   *
   * parameters will not be forwarded because they cannot be moved to multiple
   * places at once.
   *
   * @todo find a nice way to fire handlers in parallel
   */
  void
  fire( Args... args ){
    for( auto& [id, handler] : handlers ){
      handler( args... );
    }
  }

  /*!
   */
  void
  operator()( Args... args ){
    fire( args... );
  }

  /*! Remove all registered handlers
   */
  void
  clear(){
    handlers.clear();
    idCounter = 0;
  }

  bool
  operator==(const event_channel& channel) const
  {
    return (handlers == channel.handlers) &&
           (idCounter == channel.idCounter);
  }

  bool
  operator!=(const event_channel& channel) const
  {
    return !((*this) == channel);
  }
};

}

#endif


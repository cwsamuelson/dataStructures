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
    using handler = std::function<void( event_channel, counter_t, Args... )>;

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
    void
    operator()( Args... args ){
      mHandler( mChannel, mCounter, args );
    }

    bool
    operator==( event_handler other ){
      return ( mCounter == other.mCounter )
          && ( mChannel == other.mChannel );
    }

    bool
    operator!=( event_handler other ){
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
  using handler = event_handler::handler;

  /*!
   * @tparam N
   */
  template<size_t N>
  using arg_types = tuple_element<N, tuple<Args...> >;

private:
  std::map<counter_t, event_handler> handlers;
  counter_t idCounter = 0;

public:
  /*! Register new handler
   *
   * @param handler
   *
   * @return
   */
  event_channel& operator+=( const handler& handler ){
    enlist( handler );
 
    return *this;
  }

  /*! Register new handler
   *
   * @param handler
   *
   * @return
   */
  event_handler  enlist( const handler& handler ){
    handlers[idCounter] = event_handler( *this, idCounter, handler );

    return handlers[idCounter++];
  }

  /*! Unregister a previously registered handler
   *
   * @param ref
   */
  void delist( const event_handler& handle ){
    handlers.erase( ref );
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel& operator-=( const event_handler& handler ){
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
  void fire( Args... args ){
    for( auto& handle : handlers ){
      handle.second( *this, handle.first, args... );
    }
  }

  /*!
   */
  void operator()( Args... args ){
    fire( args... );
  }

  /*! Remove all registered handlers
   */
  void clear(){
    handlers.clear();
    idCounter = 0;
  }
};

}

#endif


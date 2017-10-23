#ifndef __EVENT_HANDLER__HH__
#define __EVENT_HANDLER__HH__

/*!
 * @example test-events.cc
 */

#include<map>
#include<functional>

namespace gsw{

template<typename channel, typename ...Args>
class event_handler{
public:
  using channel_type = channel;
  using callback = std::function<void(const channel_type&, Args...)>;

private:
  callback mCallback;

public:
  /*!
   */
  event_handler() = default;

  /*!
   */
  event_handler( const callback& cb ):
    mCallback( cb ){
  }

  /*!
   */
  event_handler& operator=( const callback& cb ){
    mCallback = cb;
  }

  /*!
   */
  void operator()( const channel_type& value, Args... args ){
    mCallback( value, args... );
  }
};

template<typename ...Args>
class event_channel{
public:
  using handler = event_handler<event_channel, Args...>;

private:
  std::map<unsigned long long, handler> handlers;
  unsigned long long idCounter = 0;

public:
  /*!
   */
  event_channel& operator+=( const handler& handler ){
    handlers[idCounter++] = handler;
 
    return *this;
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel& operator-=( const handler& handler );

  /*!
   */
  void fire( Args... args ){
    for( auto& handle : handlers ){
      handle.second( *this, args... );
    }
  }
};

}

#endif


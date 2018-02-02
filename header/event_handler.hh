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
  /*!
   */
  using counter_t = unsigned long long;
  /*!
   */
  using handler = std::function<void(const event_channel&, counter_t, Args...)>;
  /*!
   * @tparam N
   */
  template<size_t N>
  using arg_types = tuple_element<N, tuple<Args...> >;

private:
  std::map<counter_t, handler> handlers;
  counter_t idCounter = 0;

public:
  /*! Register new handler
   *
   * @param handler
   *
   * @return
   */
  event_channel& operator+=( const handler& handler ){
    handlers[idCounter++] = handler;
 
    return *this;
  }

  /*! Register new handler
   *
   * @param handler
   *
   * @return
   */
  counter_t enlist( const handler& handler ){
    handlers[idCounter] = handler;

    return idCounter++;
  }

  /*! Unregister a previously registered handler
   *
   * @param ref
   */
  void delist( counter_t ref ){
    handlers.erase( ref );
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel& operator-=( const handler& handler );

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

  /*! Remove all registered handlers
   */
  void clear(){
    handlers.clear();
    idCounter = 0;
  }
};

}

#endif


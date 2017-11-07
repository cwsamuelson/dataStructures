#ifndef __EVENT_HANDLER__HH__
#define __EVENT_HANDLER__HH__

/*!
 * @example test-events.cc
 */

#include<map>
#include<functional>
#include<utility>

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
  using handler = std::function<void(const event_channel&, Args...)>;

private:
  std::map<unsigned long long, handler> handlers;
  unsigned long long idCounter = 0;

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
  unsigned long long enlist( const handler& handler ){
    handlers[idCounter] = handler;

    return idCounter++;
  }

  /*! Unregister a previously registered handler
   *
   * @param ref
   */
  void delist( unsigned long long ref ){
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
   * @todo find a nice way to fire handlers in parallel
   * @todo determine if parameters should be forwarded or not. if they are, that implies trying to move an object to multiple handlers, which is an oxymoron
   */
  void fire( Args... args ){
    for( auto& handle : handlers ){
      handle.second( *this, std::forward<Args>( args )... );
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


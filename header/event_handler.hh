#ifndef __EVENT_HANDLER__HH__
#define __EVENT_HANDLER__HH__

/*!
 * @example test-events.cc
 */

#include<map>
#include<functional>
#include<utility>

namespace gsw{

/*!
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
  /*!
   */
  event_channel& operator+=( const handler& handler ){
    handlers[idCounter++] = handler;
 
    return *this;
  }

  /*!
   */
  unsigned long long enlist( const handler& handler ){
    handlers[idCounter] = handler;

    return idCounter++;
  }

  /*!
   */
  void delist( unsigned long long ref ){
    handlers.erase( ref );
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel& operator-=( const handler& handler );

  /*!
   */
  void fire( Args... args ){
    for( auto& handle : handlers ){
      handle.second( *this, std::forward<Args>( args )... );
    }
  }

  /*!
   */
  void clear(){
    handlers.clear();
    idCounter = 0;
  }
};

}

#endif


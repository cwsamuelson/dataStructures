#ifndef __EVENT_HANDLER__HH__
#define __EVENT_HANDLER__HH__

/*!
 * @example test-events.cc
 */

#include <map>
#include <functional>
#include <utility>
#include <memory>
#include <tuple>

namespace gsw {

/*! Event channel system
 *
 * @tparam Args...
 *
 * @TODO non-blocking event handling
 *
 * @TODO could add a couple special type parameters to distinguish different event_channels within the type system
 *
 * One might be the owner type.  Doing that would allow the channel to friend the owner, and then make the fire method private,
 * that way the owner is the only one that's allowed to fire an event! (this feature is somewhat desired)
 * another parameter might be a dummy, kinda like what's used in the named_type system
 * this dummy might look like struct OnMousePressed, to help distinguish between different posseble events
 */
template<typename ...Args>
class event_channel {
public:
  class event_trigger {
  public:
    using channel_t = event_channel<Args...>;

  private:
    std::shared_ptr<channel_t> mChannel;

  public:
    void fire(Args... args) {
      mChannel->fire(args...);
    }

    event_trigger()
            : mChannel(new channel_t) {
    }

    std::weak_ptr<channel_t> getChannel() const {
      return mChannel;
    }
  };

  friend class event_trigger;

  /*! Container for handling events
   */
  class event_handler {
  public:
    using counter_t = unsigned long long;
    using handler = std::function<void(event_channel&, counter_t, Args...)>;
    using simple_handler = std::function<void(Args...)>;
    friend event_channel;

  private:
    event_channel& mChannel;
    handler mHandler;
    simple_handler mSHandler;
    counter_t mCounter;

    /*! Private constructor
     *
     * Constructor is private so that only the channel creates handlers
     */
    event_handler(event_channel& channel, counter_t counter, handler handle)
            : mChannel(channel)
            , mHandler(handle)
            , mCounter(counter) {
    }

    /*! Private constructor
     *
     * Constructor is private so that only the channel creates handlers
     */
    event_handler(event_channel& channel, counter_t counter, simple_handler handle)
            : mChannel(channel)
            , mSHandler(handle)
            , mCounter(counter) {
    }

    /*! Call event
     *
     * Made private so that only the channel triggers events
     */
    void operator()(Args... args) {
      if(mHandler) {
        mHandler(mChannel, mCounter, args...);
      }
      if(mSHandler) {
        mSHandler(args...);
      }
    }

  public:
    /*! Copy ctor
     *
     * @param handler Event handler to copy from
     */
    event_handler(const event_handler& handler) = default;

    /*! Copy assignment
     *
     * @param handler Event handler to copy from
     */
    event_handler& operator=(const event_handler& handler) = default;

    bool operator==(event_handler other) const {
      return (mCounter == other.mCounter) && (mChannel == other.mChannel);
    }

    bool operator!=(event_handler other) const {
      return !(*this == other);
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
  using simple_handler = typename event_handler::simple_handler;

  /*!
   * @tparam N
   */
  template<size_t N> using arg_types = typename std::tuple_element<N, std::tuple<Args...>>::type;

private:
  std::map<counter_t, event_handler> handlers;
  counter_t idCounter = 0;

protected:
  /*! Fire the event!
   *
   * @param args Arguments to pass on to handlers
   *
   * parameters will not be forwarded because they cannot be moved to multiple
   * places at once.
   *
   * @todo find a nice way to fire handlers in parallel
   * @todo should event parameters be forwarded
   * the initial reaction is "obviously yes", but then moved/gutted objects
   * could not be used for the second handler.  I'm not yet 100% sure if the
   * answer should continue to be 'no'(seems as though it should).
   */
  void fire(Args... args) {
    for(auto&[id, handler] : handlers) {
      handler(args...);
    }
  }

  /*! Fire the event!
   *
   * @param args Arguments to pass on to handlers
   */
  void operator()(Args... args) {
    fire(std::forward<Args>(args)...);
  }

  event_channel() = default;

  event_channel(const event_channel&) = default;

  event_channel(event_channel&&) noexcept = default;

public:
  ~event_channel() = default;

  event_channel& operator=(const event_channel&) = default;

  event_channel& operator=(event_channel&&) noexcept = default;

  /*! Register new handler
   *
   * @param handler Handler to enlist
   *
   * @return The new modified channel
   */
  event_handler subscribe(const handler& handle) {
    handlers.emplace(std::make_pair(idCounter, event_handler{ *this, idCounter, handle }));

    return handlers.at(idCounter++);
  }

  /*!
   */
  event_handler subscribe(const simple_handler& handle) {
    handlers.emplace(std::make_pair(idCounter, event_handler{ *this, idCounter, handle }));

    return handlers.at(idCounter++);
  }

  /*! Unregister a previously registered handler
   *
   * @param ref Handler to no longer be fired when the event goes off
   */
  void unsubscribe(const event_handler& handle) {
    handlers.erase(handlers.find(handle.mCounter));
  }

  /*! Register new handler
   *
   * @param handler Handler to register
   *
   * @return The new modified channel
   */
  event_channel& operator+=(const handler& handle) {
    subscribe(handle);

    return *this;
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel& operator-=(const event_handler& handler) {
    unsubscribe(handler);

    return *this;
  }

  /*! Remove all registered handlers
   */
  void clear() {
    handlers.clear();
    idCounter = 0;
  }

  friend auto operator<=>(const event_channel&, const event_channel&) = default;
};

template<typename ...Args>
using event_trigger = typename event_channel<Args...>::event_trigger;

}

#endif

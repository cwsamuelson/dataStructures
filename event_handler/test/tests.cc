#include<string>

#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<event_handler.hh>

using namespace std;

struct foo {
  int x;
};

/*TEST_CASE( "Basic event control flow", "[events]" )
{
  int g_i = 0;
  int g_j = 0;
  int g_k = 0;
  int g_l = 0;
  int g_m = 0;
  foo g_f;
  g_f.x = 0;

  class trigg0 : public gsw::event_trigger<int>
  {
  public:
    using base_t = gsw::event_trigger<int>;
    using base_t::fire;
  };
  class trigg1 : public gsw::event_trigger<foo>
  {
    public:
    using base_t = gsw::event_trigger<foo>;
    using base_t::fire;
  };
  class trigg2 : public gsw::event_trigger<int, int>
  {
  public:
    using base_t = gsw::event_trigger<int, int>;
    using base_t::fire;
  };
  trigg0 t0;
  trigg1 t1;
  trigg2 t2;
  auto chan0 = t0.getChannel();
  auto chan1 = t1.getChannel();
  auto chan2 = t2.getChannel();

  gsw::event_channel<int>::handler handler0;
  gsw::event_channel<foo>::handler handler1(
    [&]( gsw::event_channel<foo>&, unsigned long long, foo f ){
      g_f = f;
    }
  );
  gsw::event_channel<int>::handler handler2(
    [&]( gsw::event_channel<int>&, unsigned long long, int i ){
      g_j = i;
    }
  );
  gsw::event_channel<int>::handler handler3(
    [&]( gsw::event_channel<int>&, unsigned long long, int i ){
      g_k = i;
    }
  );
  gsw::event_channel<int, int>::handler handler4(
    [&]( gsw::event_channel<int, int>&, unsigned long long, int i, int j ){
      g_l = i;
      g_m = j;
    }
  );

  handler0 =
    [&]( gsw::event_channel<int>&, unsigned long long, int i ){
      g_i = i;
    };

  *chan0.lock() += handler0;
  *chan0.lock() += handler2;
  *chan1.lock() += handler1;
  *chan2.lock() += handler4;
  auto idx = chan0.lock()->subscribe( handler3 );
  chan0.lock()->unsubscribe( idx );

  CHECK( g_i   == 0 );
  CHECK( g_j   == 0 );
  CHECK( g_k   == 0 );
  CHECK( g_l   == 0 );
  CHECK( g_m   == 0 );
  CHECK( g_f.x == 0 );

  t0.fire(     42 );
  t1.fire( foo{69} );
  t2.fire( 6, 9 );

  CHECK( g_i   == 42 );
  CHECK( g_j   == 42 );
  CHECK( g_k   == 0 );
  CHECK( g_l   == 6 );
  CHECK( g_m   == 9 );
  CHECK( g_f.x == 69 );
}*/

class serial {
public:
  using handler = gsw::event_trigger<string>::channel_t::handler;
  using channel_t = gsw::event_trigger<string>::channel_t;

private:
  gsw::event_trigger<string> mSendEvent;

public:
  auto sendEvent() const {
    return mSendEvent.getChannel();
  }

  void send(const string& d) {
    //do some things with the data

    //then fire the corresponding event!
    mSendEvent.fire(d);
  }
};

TEST_CASE("In context usage", "[events]") {
  string response;
  serial ser;
  serial::handler serialRxHandler([&](const serial::channel_t&, unsigned long long, const string& str)
                                    {
                                      response = str + "response!";
                                    });
  auto eventChannel = ser.sendEvent().lock();
  eventChannel->subscribe(serialRxHandler);

  ser.send("data!");

  CHECK(response == "data!response!");
}


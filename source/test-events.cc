#include<string>

#include<catch.hpp>

#include<event_handler.hh>

using namespace std;

struct foo{
  int x;
};

TEST_CASE( "Basic event control flow", "[events]" ){
  int g_i = 0;
  foo g_f;
  g_f.x = 0;

  gsw::event_channel<int> chan0;
  gsw::event_channel<foo> chan1;

  gsw::event_channel<int>::handler handler0;
  gsw::event_channel<foo>::handler handler1(
                                     [&]( gsw::event_channel<foo>, foo f ){
                                       g_f = f;
                                     } );

  handler0 =
    [&]( gsw::event_channel<int>, int i ){
      g_i = i;
    };

  chan0 += handler0;
  chan1 += handler1;

  REQUIRE( g_i   == 0 );
  REQUIRE( g_f.x == 0 );

  chan0.fire(     42 );
  chan1.fire( foo{69} );

  REQUIRE( g_i   == 42 );
  REQUIRE( g_f.x == 69 );
}

class serial{
public:
  using rxEvent = gsw::event_channel<string>;
  using rxHandler = rxEvent::handler;

  rxEvent rxDataEvent;

  void send( const string& str ){
    rxDataEvent.fire( "response!" );
  }
};

TEST_CASE( "In context usage", "[events]" ){
  string response;
  serial ser;
  serial::rxHandler serialRxHandler(
                      [&]( const serial::rxEvent&, const string& str ){
                        response = str;
                      } );
  ser.rxDataEvent += serialRxHandler;

  ser.send( "data!" );

  REQUIRE( response == "response!" );
}


#ifndef __JSON_HH__
#define __JSON_HH__

#include<string>
#include<vector>
#include<map>
#include<utility>

// json supports int, string, array/vector, and object/map
/*!
 */
class json{
  using object_t = std::map<std::string, json>;
  using array_t = std::vector<json>;
  using string_t = std::string;
  using integer_t = signed long long;
  using u_integer_t = unsigned long long;
  using float_t = double;
  using bool_t = bool;

  enum class json_type{
    null,
    object,
    array,
    string,
    integer,
    uinteger,
    float_pt,
    boolean,
  }

  union json_value{
    object_t* object;
    array_t* array;
    string_t* string;
    integer_t integer;
    u_integer_t uinteger;
    float_t float_pt;
    bool_t boolean;

    json_value() = default;

    json_value( integer_t i )
      : integer( i ){
    }

    json_value( u_integer_t ui )
      : uinteger( ui ){
    }

    json_value( bool_t b )
      : bool_t( b ){
    }

    json_value( const string_t& str )
      : string( str ){
    }

    json_value( string_t&& str )
      : string( std::move( str ) ){
    }

    json_value( const array_t& arr )
      : string( arr ){
    }

    json_value( array_t&& arr )
      : string( std::move( arr ) ){
    }

    json_value( const object_t& obj )
      : string( obj ){
    }

    json_value( object_t&& obj )
      : string( std::move( obj ) ){
    }

    json_value( json_type type ){
      switch( type ){
      case json_type::null:
        object = nullptr;
      break;

      case json_type::object:
        object = new object_t;
      break;

      case json_type::array:
        array = new array_t;
      break;

      case json_type::string:
        string = new string_t;
      break;

      case json_type::integer:
        integer = integer_t( 0 );
      break;

      case json_type::uinteger:
        uinteger = u_integer_t( 0 );
      break;

      case json_type::float_pt:
        float_pt = float_t( 0.0 );
      break;

      case json_type::boolean:
        boolean = bool_t( false );
      break;
      }
    }

    void
    destroy( json_type type ){
      switch( type ){
      case json_type::object:
        delete object;
      break;

      case json_type::array:
        delete array;
      break;

      case json_type::string:
        delete object;
      break;

      default:
      break;
      }
    }
  }

  json_type mType;
  json_value mValue;
};

#endif


#ifndef __DATE_TIME_HH__
#define __DATE_TIME_HH__

/*!
 * @example test-time.cc
 */

#include<string>

#include<unit.hh>

namespace gsw{

typedef unsigned long long under_type;

/*! Type that operates like the unit class
 *
 * @tparam F
 *
 * Type that operates like the unit class, and can inter-op with it, but
 * is simultaneously a different type.
 */
template<size_t F>
class time_type : public time<under_type, metric, ratio<F, 1> >{
public:
  typedef time<under_type, metric, ratio<F, 1> > base;

  constexpr time_type()
    : base(){
  }
  constexpr time_type( under_type ut )
    : base( ut ){
  }
  template<typename D, typename F_t>
  constexpr time_type( const typename base::template other_type<metric, D, F_t>& other )
    : base( other ){
  }
};

using second = time_type<1>;
using minute = time_type<60>;
using hour   = time_type<60 * 60>;
using day    = time_type<60 * 60 * 24>;
using week   = time_type<60 * 60 * 24 * 7>;
using month  = time_type<60 * 60 * 24 * 7 * 4>;
using year   = time_type<60 * 60 * 24 * 365>;

constexpr
second
operator""_s( under_type val ){
  return val;
}

constexpr
minute
operator""_m( under_type val ){
  return val;
}

constexpr
hour
operator""_h( under_type val ){
  return val;
}

constexpr
day
operator""_d( under_type val ){
  return val;
}

constexpr
week
operator""_w( under_type val ){
  return val;
}

constexpr
month
operator""_M( under_type val ){
  return val;
}

constexpr
year
operator""_y( under_type val ){
  return val;
}

/*! Outputs a data, and it's name to os
 *
 * @tparam OSTREAM  Output stream type
 *
 * @param os  Output stream object that data will be inserted into
 *
 * @param t
 *
 * @param type  Name of units being output to os
 *
 * @return
 */
template<typename OSTREAM>
auto&
output( OSTREAM& os, under_type t, const std::string& type ){
  return ( os << t << " " << type );
}

/*! Stream insertion operator
 *
 * @tparam OSTREAM  Output stream type
 *
 * @tparam F  Factor of type's ratio
 *
 * @param os  Output stream object that data will be inserted into
 *
 * @param tt
 *
 * @return
 *
 * @todo make these all ifs constexpr-if; if constexpr( F == ... )...
 *
 *
 */
template<typename OSTREAM, size_t F>
auto&
operator<<( OSTREAM& os, const time_type<F>& tt ){
  std::string type;

  if ( F == second::factor_type::value ){
    type = "seconds";
  } else if ( F == minute::factor_type::value ){
    type = "minutes";
  } else if ( F == hour::factor_type::value ){
    type = "hours";
  } else if ( F == day::factor_type::value ){
    type = "days";
  } else if ( F == week::factor_type::value ){
    type = "weeks";
  } else if ( F == month::factor_type::value ){
    type = "months";
  } else if ( F == year::factor_type::value ){
    type = "years";
  } else {
    type = "time units";
  }

  return output( os, tt.getValue(), type );
}

/*! Stream extraction operator
 *
 * @tparam ISTREAM  Input stream type
 *
 * @tparam F  Factor of type's ratio
 *
 * @param is  Input stream object that data will be extracted from
 *
 * @param tu  Reference to time to set equal to extracted value
 *
 * @return
 *
 * @todo make these all ifs constexpr-if; if constexpr( F == ... )...
 *
 *
 */
template<size_t F, typename ISTREAM>
auto&
operator>>( ISTREAM& is, time_type<F>& tu ){
  long long val;
  std::string str;

  is >> val;
  is >> str;

  if( str == "seconds" ){
    tu = second( val );
  } else if( str == "minutes" ){
    tu = minute( val );
  } else if( str == "hours" ){
    tu = hour( val );
  } else if( str == "days" ){
    tu = day( val );
  } else if( str == "weeks" ){
    tu = week( val );
  } else if( str == "months" ){
    tu = month( val );
  } else if( str == "years" ){
    tu = year( val );
  }

  return is;
}

/*! Stores the date, and year
 *
 * Interacts with time types to increment the current date appropriately
 */
class date{
private:
  day mDay;
  year mYear;
  static constexpr unsigned int mMonths[12] = { 31, 29, 31, 30, 31, 30,
                                                31, 31, 30, 31, 30, 31 };
  static constexpr char monthNames[][12] = { "January", "February", "March",
                                             "April", "May", "June", "July",
                                             "August", "September", "October",
                                             "November", "December" };

public:
  /*! Ctor
   *
   * @param d  Day of the month to initialize
   *
   * @param mont  Number representing the month to initialize
   *
   * @param y  The year to initialize
   */
  date( day d, unsigned int mont, year y )
    : mDay( d )
    , mYear( y ){

    for( unsigned int i = 0; i < mont - 1; ++i ){
      mDay += mMonths[i];
    }
  }

  /*! Addition operator
   *
   * @tparam F  Factor for value prefix
   *
   * @param tu  Amount of time to add to current date
   *
   * @return Value of result of addition
   */
  template<size_t F>
  date
  operator+( const time_type<F>& tu ){
    date d( *this );

    d += tu;

    return d;
  }

  /*! Subtraction operator
   *
   * @tparam F  Factor for value prefix
   *
   * @param tu  Amount of time to subtract from current date
   *
   * @return Value of result of subtraction
   */
  template<size_t F>
  date
  operator-( const time_type<F>& tu ){
    date d( *this );

    d -= tu;

    return d;
  }

  /*! Addition assignment operator
   *
   * @tparam F  Factor for value prefix
   *
   * @param tu  Amount of time to add to current date
   *
   * @return Reference to result of addition
   */
  template<size_t F>
  date&
  operator+=( const time_type<F>& tu ){
    mDay += tu;
    if( mDay >= 365ll ){
      ++mYear;
      mDay -= 365;
    }

    return *this;
  }

  /*! Subtraction assignment operator
   *
   * @tparam F  Factor for value prefix
   *
   * @param tu  Amount of time to subtract from current date
   *
   * @return Reference to result of subtraction
   */
  template<size_t F>
  date&
  operator-=( const time_type<F>& tu ){
    mDay -= tu;
    if( mDay <= 0ll ){
      --mYear;
      mDay += 365;
    }

    return *this;
  }

  /*! Stream insertion operator
   *
   * @tparam OSTREAM  Output stream type
   *
   * @param os  Output stream to insert data into
   *
   * @param dayt  Date to be printed to stream
   *
   * @return Reference to resulting stream object
   */
  template<typename OSTREAM>
  friend
  auto&
  operator<<( OSTREAM& os, date dayt ){
    unsigned int mont = 0;

    while( dayt.mDay.getValue() > date::mMonths[mont] ){
      dayt.mDay -= date::mMonths[mont++];
    }

    return ( os << dayt.mDay.getValue() << " "
                << date::monthNames[mont] << " "
                << dayt.mYear.getValue() );
  }
};

constexpr unsigned int date::mMonths[12];
constexpr char date::monthNames[][12];

/*!
 */
class date_time{
private:
  date mDate;
  hour mHour;
  minute mMinute;
  second mSecond;

public:
  /*! Time-centric ctor
   *
   * @param h
   *
   * @param m
   *
   * @param s
   *
   * @param d
   */
  date_time( const hour& h, const minute& m, const second& s, const date& d = date( day( 0 ), 0, year( 0 ) ) )
    : mDate( d )
    , mHour( h )
    , mMinute( m )
    , mSecond( s ){
  }

  /*! Date-centric ctor
   *
   * @param d
   *
   * @param h
   *
   * @param m
   *
   * @param s
   */
  date_time( const date& d, const hour& h = hour( 0 ), const minute& m = minute( 0 ), const second& s = second( 0 ) )
    : mDate( d )
    , mHour( h )
    , mMinute( m )
    , mSecond( s ){
  }

  /*! Addition operator
   *
   * @tparam F  Factor for value prefix
   *
   * @param tu
   *
   * @return
   */
  template<size_t F>
  date_time
  operator+( const time_type<F>& tu ){
    date_time ret( *this );

    ret += tu;

    return ret;
  }

  /*! Addition-assignment operator
   *
   * @tparam F  Factor for value prefix
   *
   * @param tu
   *
   * @return
   */
  template<size_t F>
  date_time&
  operator+=( const time_type<F>& tu ){
    while( tu.getRaw() > day::factor_type::value ){
      day one( 1 );
      mDate += one;
      tu -= one;
    }

    //whatever's left will be hour/min/sec
    //dump it into the time
    while( tu.getRaw() > hour::factor_type::value ){
      ++mHour;
      tu -= 3600 / F;
    }

    while( tu.getRaw() > minute::factor_type::value ){
      ++mMinute;
      tu -= 60 / F;
    }

    mSecond += tu;

    return *this;
  }

  /*! Stream insertion operator
   *
   * @tparam OSTREAM  Output stream type
   *
   * @param os  Output stream object to insert data into
   *
   * @param dt  date and time to insert into stream
   *
   * @return Reference to resulting output stream object
   */
  template<typename OSTREAM>
  friend
  auto&
  operator<<( OSTREAM& os, date_time dt ){
    os << dt.mDate << " ";

    return ( os << dt.mHour.getValue() << ":" << dt.mMinute.getValue() << ":" << dt.mSecond.getValue() );
  }
};

}

#endif

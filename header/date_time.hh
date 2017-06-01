#ifndef __DATE_TIME_HH__
#define __DATE_TIME_HH__

#include<string>

#include<unit.hh>

typedef unsigned long long under_type;

template<size_t F>
class time_type : public thyme<under_type, ratio<F, 1> >{
public:
  typedef thyme<under_type, ratio<F, 1> > base;

  time_type():
    base(){
  }
  explicit time_type( under_type ut ):
    base( ut ){
  }
  template<typename D, typename F_t>
  time_type( const typename base::template other_type<D, F_t>& other ):
    base( other ){
  }
};

using second = time_type<1>;
using minute = time_type<60>;
using hour   = time_type<3600>;
using day    = time_type<86400>;
using week   = time_type<604800>;
using month  = time_type<2592000>;
using year   = time_type<31536000>;

template<typename OSTREAM>
auto& output( OSTREAM& os, under_type t, const std::string& type ){
  return ( os << t << " " << type );
}

/*!
 * @todo make these all constexpr-if; if constexpr( F == ... )...
 */
template<typename OSTREAM, size_t F>
auto& operator<<( OSTREAM& os, const time_type<F>& tt ){
  std::string type;

  if ( F == second::factor_type::numerator ){
    type = "seconds";
  } else if ( F == minute::factor_type::numerator ){
    type = "minutes";
  } else if ( F == hour::factor_type::numerator ){
    type = "hours";
  } else if ( F == day::factor_type::numerator ){
    type = "days";
  } else if ( F == week::factor_type::numerator ){
    type = "weeks";
  } else if ( F == month::factor_type::numerator ){
    type = "months";
  } else if ( F == year::factor_type::numerator ){
    type = "years";
  } else {
    type = "time units";
  }

  return output( os, tt.getValue(), type );
}

/*!
 * @todo make these all constexpr-if; if constexpr( F == ... )...
 */
template<size_t UI, typename ISTREAM>
ISTREAM& operator>>( ISTREAM& is, time_type<UI>& tu ){
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
  date( day d, unsigned int mont, year y ):
    mDay( d ),
    mYear( y ){

    for( unsigned int i = 0; i < mont - 1; ++i ){
      mDay += mMonths[i];
    }
  }

  template<size_t UI>
  date operator+( const time_type<UI>& tu ){
    date d( *this );

    d += tu;

    return d;
  }
  template<size_t UI>
  date operator-( const time_type<UI>& tu ){
    date d( *this );

    d -= tu;

    return d;
  }
  template<size_t UI>
  date& operator+=( const time_type<UI>& tu ){
    mDay += tu;
    if( mDay >= 365ll ){
      ++mYear;
      mDay -= 365;
    }

    return *this;
  }
  template<size_t UI>
  date& operator-=( const time_type<UI>& tu ){
    mDay -= tu;
    if( mDay <= 0ll ){
      --mYear;
      mDay += 365;
    }

    return *this;
  }

  template<typename OSTREAM>
  friend
  auto& operator<<( OSTREAM& os, date dayt ){
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

class date_time{
private:
  date mDate;
  hour mHour;
  minute mMinute;
  second mSecond;

public:
  date_time( const hour& h, const minute& m, const second& s, const date& d = date( day( 0 ), 0, year( 0 ) ) ):
    mDate( d ),
    mHour( h ),
    mMinute( m ),
    mSecond( s ){
  }
  date_time( const date& d, const hour& h = hour( 0 ), const minute& m = minute( 0 ), const second& s = second( 0 ) ):
    mDate( d ),
    mHour( h ),
    mMinute( m ),
    mSecond( s ){
  }

  template<size_t UI>
  date_time operator+( const time_type<UI>& tu ){
    date_time ret( *this );

    ret += tu;

    return ret;
  }

  template<size_t UI>
  date_time& operator+=( const time_type<UI>& tu ){
    while( tu.getRaw() > 86400 ){
      day one( 1 );
      mDate += one;
      tu -= one;
    }

    //whatever's left will be hour/min/sec
    //dump it into the time
    while( tu.getRaw() > 3600 ){
      ++mHour;
      tu -= 3600 / UI;
    }
    while( tu.getRaw() > 60 ){
      ++mMinute;
      tu -= 60 / UI;
    }
    
    mSecond += tu;

    return *this;
  }

  template<typename OSTREAM>
  friend
  auto& operator<<( OSTREAM& os, date_time dt ){
    os << dt.mDate << " ";

    return ( os << dt.mHour.getValue() << ":" << dt.mMinute.getValue() << ":" << dt.mSecond.getValue() );
  }
};

#endif


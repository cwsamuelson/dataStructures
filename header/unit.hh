#ifndef __UNIT_HH__
#define __UNIT_HH__

#include<ratio.hh>

template<int METERS, int SECONDS, int KILOGRAM, int AMPERE, int KELVIN, int CANDELA, typename DBL = double, typename FACTOR = ratio<1,1> >
class unit{
public:
  typedef DBL value_type;
  typedef FACTOR factor_type;
  template<typename D_t = value_type, typename F_t = factor_type>
  using other_type = unit<METERS, SECONDS, KILOGRAM, AMPERE, KELVIN, CANDELA, D_t, F_t>;

private:
  value_type mValue;

public:
  unit():
    mValue( 0.0 ){
  }
  unit( value_type val ):
    mValue( val ){
  }
  template<typename D, typename F>
  unit( const other_type<D, F>& other ):
    mValue( ( other.getRaw() ) / factor_type::value ){
  }

  template<typename D, typename F>
  unit& operator=( const other_type<D, F>& other ){
    mValue = other.getRaw() / factor_type::value;
    return *this;
  }
  unit& operator=( value_type value ){
    mValue = value;
    return *this;
  }

  template<typename D, typename F>
  bool operator==( const other_type<D, F>& other ) const{
    //TODO: allow slight error( epsilon )
    return getRaw() == other.getRaw();
  }
  template<typename D, typename F>
  bool operator!=( const other_type<D, F>& other ) const{
    return !( *this == other );
  }
  template<typename D, typename F>
  bool operator<( const other_type<D, F>& other ) const{
    return getRaw() < other.getRaw();
  }
  template<typename D, typename F>
  bool operator>( const other_type<D, F>& other ) const{
    return getRaw() > other.getRaw();
  }
  template<typename D, typename F>
  bool operator<=( const other_type<D, F>& other ) const{
    return !( ( *this ) > other );
  }
  template<typename D, typename F>
  bool operator>=( const other_type<D, F>& other ) const{
    return !( ( *this ) < other );
  }
//TODO: remove operators, which have been previously defined to work with unit,
//        and take value_type as parameter, as value_type can be converted to unit type
  bool operator==( value_type other ) const{
    return mValue == other;
  }
  bool operator<( value_type other ) const{
    return mValue < other;
  }
  bool operator>( value_type other ) const{
    return mValue > other;
  }
  bool operator<=( value_type other ) const{
    return !( ( *this ) > other );
  }
  bool operator>=( value_type other ) const{
    return !( ( *this ) < other );
  }

  unit& operator++(){
    ++mValue;
    return *this;
  }
//post-fix
  unit operator++( int ){
    unit u = *this;
 
    ++( *this );

    return u;
  }
  unit& operator--(){
    --mValue;
    return *this;
  }
//post-fix
  unit operator--( int ){
    unit u = *this;

    --( *this );

    return u;
  }

  template<typename D, typename F>
  unit operator+( const other_type<D, F>& other ) const{
    return getRaw() + other.getRaw();
  }
  template<typename D, typename F>
  unit operator-( const other_type<D, F>& other ) const{
    return getRaw() - other.getRaw();
  }

  template<typename D, typename F>
  unit& operator+=( const other_type<D, F>& other ){
    mValue = getRaw() + other.getRaw();
    return *this;
  }
  template<typename D, typename F>
  unit& operator-=( const other_type<D, F>& other ){
    mValue = getRaw() - other.getRaw();
    return *this;
  }

  unit& operator+=( value_type other ){
    mValue += other;
    return *this;
  }
  unit& operator-=( value_type other ){
    mValue -= other;
    return *this;
  }

  unit& operator*=( const value_type& val ){
    mValue *= val;
    return ( *this );
  }
  unit& operator/=( const value_type& val ){
    mValue /= val;
    return ( *this );
  }
  /* *= and /= only work with doubles because the * and / operations return a new type,
   * and therefore cannot be assigned to either operand
   */

  value_type getValue() const{ return mValue; }
  value_type getRaw() const{ return ( mValue * factor_type::value ); }

  template<typename OSTREAM>
  friend
  auto& operator<<( OSTREAM& os, const unit& val ){
    return ( os << val.mValue );
  }
  
  template<typename ISTREAM>
  friend
  auto& operator>>( ISTREAM& is, unit& val ){
    return ( is >> val.mValue );
  }
};

template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, 
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2,
         typename D_t1, typename D_t2, typename F_t1, typename F_t2>
unit<METERS1 + METERS2, SECONDS1 + SECONDS2, KILOGRAM1 + KILOGRAM2,
     AMPERE1 + AMPERE2, KELVIN1 + KELVIN2, CANDELA1 + CANDELA2, D_t1, F_t1>
operator*( const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1, D_t1, F_t1>& lhs,
           const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2, D_t2, F_t2>& rhs ){
  return lhs.getRaw() * rhs.getRaw();
}

template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1,
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2,
         typename D_t1, typename D_t2, typename F_t1, typename F_t2>
unit<METERS1 - METERS2, SECONDS1 - SECONDS2, KILOGRAM1 - KILOGRAM2,
     AMPERE1 - AMPERE2, KELVIN1 - KELVIN2, CANDELA1 - CANDELA2, D_t1, F_t1>
operator/( const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1, D_t1, F_t1>& lhs,
           const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2, D_t2, F_t2>& rhs ){
  return ( lhs.getRaw() / rhs.getRaw() ) / F_t1::value;
}

/* 'thyme' should be renamed back to 'time' when a namespace is established, as
 * name collision would be disambiguated using <namespace>::time vs ( i.e. ) std::time
 */
//                         m   s   kg  A   K  C
template<typename T = double, typename F = ratio<1,1> >
using length        = unit< 1,  0,  0,  0,  0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using mass          = unit< 0,  0,  1,  0,  0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using current       = unit< 0,  0,  0,  1,  0, 0, T, F>;//amps
template<typename T = double, typename F = ratio<1,1> >
using temperature   = unit< 0,  0,  0,  0,  1, 0, T, F>;//kelvin
template<typename T = double, typename F = ratio<1,1> >
using light         = unit< 0,  0,  0,  0,  0, 1, T, F>;//candela
template<typename T = double, typename F = ratio<1,1> >
using thyme         = unit< 0,  1,  0,  0,  0, 0, T, F>;//time, renamed to avoid collision

template<typename T = double, typename F = ratio<1,1> >
using speed         = unit< 1, -1,  0,  0,  0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using acceleration  = unit< 1, -2,  0,  0,  0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using force         = unit< 1, -2,  1,  0,  0, 0, T, F>;//newton
template<typename T = double, typename F = ratio<1,1> >
using momentum      = unit< 1, -1,  1,  0,  0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using energy        = unit< 2, -2,  1,  0,  0, 0, T, F>;//joules
template<typename T = double, typename F = ratio<1,1> >
using power         = unit< 2, -3,  1,  0,  0, 0, T, F>;//watts

template<typename T = double, typename F = ratio<1,1> >
using voltage       = unit< 2, -3,  1, -1,  0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using resistance    = unit< 2, -3,  1, -2,  0, 0, T, F>;//ohms
template<typename T = double, typename F = ratio<1,1> >
using capacitance   = unit<-2,  4, -1,  2,  0, 0, T, F>;//farad
template<typename T = double, typename F = ratio<1,1> >
using inductance    = unit< 2, -2,  1, -2,  0, 0, T, F>;//henrys
template<typename T = double, typename F = ratio<1,1> >
using charge        = unit< 0,  1,  0,  1,  0, 0, T, F>;//coulomb
template<typename T = double, typename F = ratio<1,1> >
using coulomb = charge<T, F>;

template<typename T = double, typename F = ratio<1,1> >
using magField      = unit< 0, -2,  1,  1,  0, 0, T, F>;//tesla
template<typename T = double, typename F = ratio<1,1> >
using elecField     = unit< 1, -3,  1, -1,  0, 0, T, F>;

template<typename T = double, typename F = ratio<1,1> >
using specificHeat  = unit< 2, -2,  1,  0, -1, 0, T, F>;
//OR typedef decltype( energy / temperature ) specificHeat;

#endif


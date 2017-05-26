#ifndef __UNIT_HH__
#define __UNIT_HH__

#include<ratio.hh>

/*! Unit class that differentiates between different measurements.  i.e. Meters and area
 *
 * @tparam METERS  Distance
 *
 * @tparam SECONDS  Time
 *
 * @tparam KILOGRAM  Mass (not lbs, pounds is a force)
 *
 * @tparam AMPERE  Electric current
 *
 * @tparam KELVIN  Temperature
 *
 * @tparam CANDELA  Brightness
 *
 * @tparam TICK  Custom user type.  A common usage may be tick, but can be
 *               used for anything
 *
 * @tparam DBL  Internal storage type.
 *
 * @tparam FACTOR  Prefix factor.  Can be 1:1, 2:1, 1000:1, 1:1000 etc.  Allows
 *                 Semantic storage of kilometers (km) and the like.
 *
 * The value of METERS...TICK describe the exponent value for that parameter.
 * For example, to describe length, METERS will be set to 1, and the rest 0,
 * but to describe area METERS will be set to 2 (m^2), and the rest 0, and to
 * describe velocity/speed METERS will be set to 1, and SECONDS to -1 (m/s).
 * Units can be multiplied by another, and this will result in a new type.  For
 * instance if speed is multiplied by time, the result will be of type distance.
 */
template<int METERS, int SECONDS, int KILOGRAM, int AMPERE, int KELVIN, int CANDELA, int TICK = 0, typename DBL = double, typename FACTOR = ratio<1,1> >
class unit{
public:
  typedef DBL value_type;
  typedef FACTOR factor_type;
  template<typename D_t = value_type, typename F_t = factor_type>
  using other_type = unit<METERS, SECONDS, KILOGRAM, AMPERE, KELVIN, CANDELA, TICK, D_t, F_t>;

private:
  value_type mValue;

public:
  /*! Ctor sets initial internal value
   *
   * @param val  Value to initialize data, defaults to default ctor
   */
  unit( value_type val = value_type() ):
    mValue( val ){
  }

  /*! Copy ctor
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Data to be copied in
   *
   * Value will be converted appropriately.  i.e.: if other is in kV, and has
   * value 1 and this is in V, this will have value 1000.  This conversion is
   * based on the value in F.
   */
  template<typename D, typename F>
  unit( const other_type<D, F>& other ):
    mValue( ( other.getRaw() ) / factor_type::value ){
  }

  /*! Copy-assignment operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Data to be copied in
   *
   * @return Reference to result/lhs
   *
   * Value will be converted appropriately.  i.e.: if other is in kV, and has
   * value 1 and this is in V, this will have value 1000.  This conversion is
   * based on the value in F.
   */
  template<typename D, typename F>
  unit& operator=( const other_type<D, F>& other ){
    mValue = other.getRaw() / factor_type::value;

    return *this;
  }

  /*! Copy-assignment operator
   *
   * @param value  Other value to be copied
   *
   * @return Reference to result/lhs
   *
   * Copies value raw as this' new value.
   */
  unit& operator=( value_type value ){
    mValue = value;

    return *this;
  }

  /*! Equality comparison operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Result of comparison.
   *
   * Compares this instance with another instance for equality.
   *
   * @todo Allow small error in comparison to account for floating point math.
   */
  template<typename D, typename F>
  bool operator==( const other_type<D, F>& other ) const{
    return getRaw() == other.getRaw();
  }

  /*! Inequality comparison operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Result of comparison.
   *
   * Compares this instance with another instance for inequality.
   */
  template<typename D, typename F>
  bool operator!=( const other_type<D, F>& other ) const{
    return !( *this == other );
  }

  /*!
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Result of comparison.
   *
   */
  template<typename D, typename F>
  bool operator<( const other_type<D, F>& other ) const{
    return getRaw() < other.getRaw();
  }

  /*!
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Result of comparison.
   *
   */
  template<typename D, typename F>
  bool operator>( const other_type<D, F>& other ) const{
    return getRaw() > other.getRaw();
  }

  /*!
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Result of comparison.
   *
   */
  template<typename D, typename F>
  bool operator<=( const other_type<D, F>& other ) const{
    return !( ( *this ) > other );
  }

  /*!
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Result of comparison.
   *
   */
  template<typename D, typename F>
  bool operator>=( const other_type<D, F>& other ) const{
    return !( ( *this ) < other );
  }

  /*!
   */
  bool operator==( value_type other ) const{
    return mValue == other;
  }

  /*!
   */
  bool operator<( value_type other ) const{
    return mValue < other;
  }

  /*!
   */
  bool operator>( value_type other ) const{
    return mValue > other;
  }

  /*!
   */
  bool operator<=( value_type other ) const{
    return !( ( *this ) > other );
  }

  /*!
   */
  bool operator>=( value_type other ) const{
    return !( ( *this ) < other );
  }

  /*! Prefix increment operator
   *
   * @return Reference to instance operated on, with new value.
   *
   * Increments value.
   */
  unit& operator++(){
    ++mValue;
    return *this;
  }

  /*! Post-fix increment operator
   *
   * @param Unused parameter indicates post-fix
   *
   * @return Value before increment
   */
  unit operator++( int ){
    unit u = *this;
 
    ++( *this );

    return u;
  }

  /*! Prefix decrement operator
   *
   * @return Reference to instance operated on, with new value.
   *
   * Deccrements value.
   */
  unit& operator--(){
    --mValue;
    return *this;
  }

  /*! Post-fix decrement operator
   *
   * @param Unused parameter indicates post-fix
   *
   * @return Value before deccrement
   *
   * Deccrements value.
   */
  unit operator--( int ){
    unit u = *this;

    --( *this );

    return u;
  }

  /*!
   *
   * @tparam D  
   *
   * @tparam F  
   */
  template<typename D, typename F>
  unit operator+( const other_type<D, F>& other ) const{
    return getRaw() + other.getRaw();
  }

  /*!
   *
   * @tparam D  
   *
   * @tparam F  
   */
  template<typename D, typename F>
  unit operator-( const other_type<D, F>& other ) const{
    return getRaw() - other.getRaw();
  }

  /*!
   *
   * @tparam D  
   *
   * @tparam F  
   */
  template<typename D, typename F>
  unit& operator+=( const other_type<D, F>& other ){
    mValue = getRaw() + other.getRaw();
    return *this;
  }

  /*!
   *
   * @tparam D  
   *
   * @tparam F  
   */
  template<typename D, typename F>
  unit& operator-=( const other_type<D, F>& other ){
    mValue = getRaw() - other.getRaw();
    return *this;
  }

  /*!
   */
  unit& operator+=( value_type other ){
    mValue += other;
    return *this;
  }

  /*!
   */
  unit& operator-=( value_type other ){
    mValue -= other;
    return *this;
  }

  /* *= and /= only work with doubles because the * and / operations return a new type,
   * and therefore cannot be assigned to either operand
   */

  /*!
   */
  unit& operator*=( const value_type& val ){
    mValue *= val;
    return ( *this );
  }

  /*!
   */
  unit& operator/=( const value_type& val ){
    mValue /= val;
    return ( *this );
  }

  /*!
   */
  value_type getValue() const{ return mValue; }

  /*!
   */
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

/*! Multiplication operator
 *
 * @tparam Template parameters reflect those available for the class itself.
 *         There are 2 sets of parameters, one for the lhs and the other for
 *         the rhs.
 *
 * @return Returns a 3rd type, where each template parameter is the sum of the
 *         equivalent parameters of the lhs and rhs.
 *
 */
template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, int TICK1,
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2, int TICK2,
         typename D_t1, typename D_t2, typename F_t1, typename F_t2>
unit<METERS1 + METERS2, SECONDS1 + SECONDS2, KILOGRAM1 + KILOGRAM2,
     AMPERE1 + AMPERE2, KELVIN1 + KELVIN2, CANDELA1 + CANDELA2, TICK1 + TICK2, D_t1, F_t1>
operator*( const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1, TICK1, D_t1, F_t1>& lhs,
           const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2, TICK2, D_t2, F_t2>& rhs ){
  return lhs.getRaw() * rhs.getRaw();
}

/*! Division operator
 *
 * @tparam Template parameters reflect those available for the class itself.
 *         There are 2 sets of parameters, one for the lhs and the other for
 *         the rhs.
 *
 * @return Returns a 3rd type, where each template parameter is the difference
 *         of the equivalent parameters of the lhs and rhs.
 *
 */
template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, int TICK1,
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2, int TICK2,
         typename D_t1, typename D_t2, typename F_t1, typename F_t2>
unit<METERS1 - METERS2, SECONDS1 - SECONDS2, KILOGRAM1 - KILOGRAM2,
     AMPERE1 - AMPERE2, KELVIN1 - KELVIN2, CANDELA1 - CANDELA2, TICK1 - TICK2, D_t1, F_t1>
operator/( const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1, TICK1, D_t1, F_t1>& lhs,
           const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2, TICK2, D_t2, F_t2>& rhs ){
  return ( lhs.getRaw() / rhs.getRaw() ) / F_t1::value;
}

/* TODO:'thyme' should be renamed back to 'time' when a namespace is established, as
 * name collision would be disambiguated using <namespace>::time vs ( i.e. ) std::time
 */
//                          m   s   kg  A   K  C  T
template<typename T = double, typename F = ratio<1,1> >
using length        = unit< 1,  0,  0,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using area          = unit< 2,  0,  0,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using volume        = unit< 3,  0,  0,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using mass          = unit< 0,  0,  1,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using current       = unit< 0,  0,  0,  1,  0, 0, 0, T, F>;//amps
template<typename T = double, typename F = ratio<1,1> >
using temperature   = unit< 0,  0,  0,  0,  1, 0, 0, T, F>;//kelvin
template<typename T = double, typename F = ratio<1,1> >
using brightness    = unit< 0,  0,  0,  0,  0, 1, 0, T, F>;//candela
template<typename T = double, typename F = ratio<1,1> >
using thyme         = unit< 0,  1,  0,  0,  0, 0, 0, T, F>;//time, renamed to avoid collision

template<typename T = double, typename F = ratio<1,1> >
using speed         = unit< 1, -1,  0,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using acceleration  = unit< 1, -2,  0,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using force         = unit< 1, -2,  1,  0,  0, 0, 0, T, F>;//newton
template<typename T = double, typename F = ratio<1,1> >
using momentum      = unit< 1, -1,  1,  0,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using energy        = unit< 2, -2,  1,  0,  0, 0, 0, T, F>;//joules
template<typename T = double, typename F = ratio<1,1> >
using power         = unit< 2, -3,  1,  0,  0, 0, 0, T, F>;//watts

template<typename T = double, typename F = ratio<1,1> >
using voltage       = unit< 2, -3,  1, -1,  0, 0, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using resistance    = unit< 2, -3,  1, -2,  0, 0, 0, T, F>;//ohms
template<typename T = double, typename F = ratio<1,1> >
using capacitance   = unit<-2,  4, -1,  2,  0, 0, 0, T, F>;//farad
template<typename T = double, typename F = ratio<1,1> >
using inductance    = unit< 2, -2,  1, -2,  0, 0, 0, T, F>;//henrys
template<typename T = double, typename F = ratio<1,1> >
using charge        = unit< 0,  1,  0,  1,  0, 0, 0, T, F>;//coulomb
template<typename T = double, typename F = ratio<1,1> >
using coulomb = charge<T, F>;

template<typename T = double, typename F = ratio<1,1> >
using mag_field      = unit< 0, -2,  1,  1,  0, 0, 0, T, F>;//tesla
template<typename T = double, typename F = ratio<1,1> >
using elec_field     = unit< 1, -3,  1, -1,  0, 0, 0, T, F>;

template<typename T = double, typename F = ratio<1,1> >
using specificHeat  = decltype( energy<T, F>() / temperature<T, F>() );

#endif


#ifndef __UNIT_HH__
#define __UNIT_HH__

/*! This file defines scientific and other units and their interactions
 *
 * @example test-unit.cc
 */

#include<ratio.hh>
#include<additive.hh>

namespace gsw{

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
 * @tparam DEGREE  Degrees of angle
 *
 * @tparam PERCENTAGE  Percent
 *
 * @tparam TICK  Custom user type.  A common usage may be tick, but can be used
 *               for anything
 *
 * @tparam DBL  Internal storage type.
 *
 * @tparam FACTOR  Prefix factor.  Can be 1:1, 2:1, 1000:1, 1:1000 etc.  Allows
 *                 semantic storage of kilometers (km) and the like.
 *
 * The value of METERS...TICK describe the exponent value for that parameter.
 * For example, to describe length, METERS will be set to 1, and the rest 0,
 * but to describe area METERS will be set to 2 (m^2), and the rest 0, and to
 * describe velocity/speed METERS will be set to 1, and SECONDS to -1 (m/s).
 * Units can be multiplied by another, and this will result in a new,
 * appropriate type.  For instance if speed is multiplied by time, the result
 * will be of type distance.
 */
template<int METERS, int SECONDS, int KILOGRAM, int AMPERE, int KELVIN, int CANDELA, int DEGREE, int PERCENTAGE = 0, int TICK = 0, typename DBL = double, typename FACTOR = ratio<1, 1> >
class unit : public additive<unit<METERS, SECONDS, KILOGRAM, AMPERE, KELVIN, CANDELA, DEGREE, PERCENTAGE, TICK, DBL, FACTOR> >,
                    additive<unit<METERS, SECONDS, KILOGRAM, AMPERE, KELVIN, CANDELA, DEGREE, PERCENTAGE, TICK, DBL, FACTOR>, DBL>{
public:
  typedef DBL value_type;
  typedef FACTOR factor_type;
  template<typename D_t = value_type, typename F_t = factor_type>
  using other_type = unit<METERS, SECONDS, KILOGRAM, AMPERE, KELVIN, CANDELA, DEGREE, PERCENTAGE, TICK, D_t, F_t>;

private:
  value_type mValue;

public:
  /*! Ctor sets initial internal value
   *
   * @param val  Value to initialize data, defaults to default ctor
   */
  constexpr unit( value_type val = value_type() ):
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
  constexpr unit( const other_type<D, F>& other ):
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
  constexpr bool operator==( const other_type<D, F>& other ) const{
    return getRaw() == other.getRaw();
  }

  /*! Inequality comparison operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison.
   *
   * Compares this instance with another instance for inequality.
   */
  template<typename D, typename F>
  constexpr bool operator!=( const other_type<D, F>& other ) const{
    return !( *this == other );
  }

  /*!
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison.
   */
  template<typename D, typename F>
  constexpr bool operator<( const other_type<D, F>& other ) const{
    return getRaw() < other.getRaw();
  }

  /*!
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison.
   */
  template<typename D, typename F>
  constexpr bool operator>( const other_type<D, F>& other ) const{
    return getRaw() > other.getRaw();
  }

  /*! LE comparison operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison.
   */
  template<typename D, typename F>
  constexpr bool operator<=( const other_type<D, F>& other ) const{
    return !( ( *this ) > other );
  }

  /*! GE comparison operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  template<typename D, typename F>
  constexpr bool operator>=( const other_type<D, F>& other ) const{
    return !( ( *this ) < other );
  }

  /*! Equality comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool operator==( value_type other ) const{
    return mValue == other;
  }

  /*! LT comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool operator<( value_type other ) const{
    return mValue < other;
  }

  /*! GT comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool operator>( value_type other ) const{
    return mValue > other;
  }

  /*! LE comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool operator<=( value_type other ) const{
    return !( ( *this ) > other );
  }

  /*! GE comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool operator>=( value_type other ) const{
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

  /*! Add-assignment operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Reference to lhs, but with value of the addition
   */
  template<typename D, typename F>
  unit& operator+=( const other_type<D, F>& other ){
    mValue = getRaw() + other.getRaw();
    return *this;
  }

  /*! Subtraction-assignment operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return Reference to lhs, but with value of the subtraction
   */
  template<typename D, typename F>
  unit& operator-=( const other_type<D, F>& other ){
    mValue = getRaw() - other.getRaw();
    return *this;
  }

  /*! Add-assignment operator
   *
   * @param other  Value to add to stored value
   *
   * @return Reference to resulting unit
   *
   * Stored value is increased by other, and saved
   */
  unit& operator+=( value_type other ){
    mValue += other;
    return *this;
  }

  /*! Subtract-assignment operator
   *
   * @param other  Value to be subtracted from stored value
   *
   * @return Reference to resulting unit
   *
   * Stored value is reduced by other, and saved
   */
  unit& operator-=( value_type other ){
    mValue -= other;
    return *this;
  }

  /* *= and /= only work with doubles because the * and / operations return a new type,
   * and therefore cannot be assigned to either operand
   */

  /*! Multiply-assignment operator
   *
   * @param val  Value to multiply by
   *
   * @return Reference to resulting unit
   *
   * Stored value is multiplied by val, and saved
   */
  unit& operator*=( const value_type& val ){
    mValue *= val;
    return ( *this );
  }

  /*! Divide-assignment operator
   *
   * @param val  Value to divide by
   *
   * @return Resulting unit
   *
   * Stored value is divided by val, and saved
   */
  unit& operator/=( const value_type& val ){
    mValue /= val;
    return ( *this );
  }

  /*! Get factored, stored value
   */
  constexpr value_type getValue() const{
    return mValue;
  }

  /*! Retrieve actual raw value (factor is taken into account)
   */
  constexpr value_type getRaw() const{
    return ( mValue * factor_type::value );
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
template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, int DEGREE1, int PERCENTAGE1, int TICK1,
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2, int DEGREE2, int PERCENTAGE2, int TICK2,
         typename D_t1, typename D_t2, typename F_t1, typename F_t2>
unit<METERS1 + METERS2, SECONDS1 + SECONDS2, KILOGRAM1 + KILOGRAM2, AMPERE1 + AMPERE2,
     KELVIN1 + KELVIN2, CANDELA1 + CANDELA2, DEGREE1 + DEGREE2, PERCENTAGE1 + PERCENTAGE2, TICK1 + TICK2,
     D_t1, F_t1>
operator*( const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1, DEGREE1, PERCENTAGE1, TICK1, D_t1, F_t1>& lhs,
           const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2, DEGREE2, PERCENTAGE2, TICK2, D_t2, F_t2>& rhs ){
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
template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, int DEGREE1, int PERCENTAGE1, int TICK1,
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2, int DEGREE2, int PERCENTAGE2, int TICK2,
         typename D_t1, typename D_t2, typename F_t1, typename F_t2>
unit<METERS1 - METERS2, SECONDS1 - SECONDS2, KILOGRAM1 - KILOGRAM2, AMPERE1 - AMPERE2,
     KELVIN1 - KELVIN2, CANDELA1 - CANDELA2, DEGREE1 - DEGREE2, PERCENTAGE1 - PERCENTAGE2, TICK1 - TICK2,
     D_t1, F_t1>
operator/( const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1, DEGREE1, PERCENTAGE1, TICK1, D_t1, F_t1>& lhs,
           const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2, DEGREE2, PERCENTAGE2, TICK2, D_t2, F_t2>& rhs ){
  return ( lhs.getRaw() / rhs.getRaw() ) / F_t1::value;
}

//                          m   s  kg   A   K  C  D  P  T
template<typename T = double, typename F = ratio<1,1> >
using none          = unit< 0,  0,  0,  0,  0, 0, 0, 0, 0, T, F>;//meters

template<typename T = double, typename F = ratio<1,1> >
using length        = unit< 1,  0,  0,  0,  0, 0, 0, 0, 0, T, F>;//meters
template<typename T = double, typename F = ratio<1,1> >
using mass          = unit< 0,  0,  1,  0,  0, 0, 0, 0, 0, T, F>;//kg
template<typename T = double, typename F = ratio<1,1> >
using current       = unit< 0,  0,  0,  1,  0, 0, 0, 0, 0, T, F>;//amps
template<typename T = double, typename F = ratio<1,1> >
using temperature   = unit< 0,  0,  0,  0,  1, 0, 0, 0, 0, T, F>;//kelvin
template<typename T = double, typename F = ratio<1,1> >
using l_intensity   = unit< 0,  0,  0,  0,  0, 1, 0, 0, 0, T, F>;//luminous intensity
template<typename T = double, typename F = ratio<1,1> >
using time          = unit< 0,  1,  0,  0,  0, 0, 0, 0, 0, T, F>;//seconds
template<typename T = double, typename F = ratio<1,1> >
using tick          = unit< 0,  0,  0,  0,  0, 0, 0, 0, 1, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using percent       = unit< 0,  0,  0,  0,  0, 0, 0, 1, 0, T, F>;
template<typename T = double, typename F = ratio<1,1> >
using frequency     = unit< 0, -1,  0,  0,  0, 0, 0, 0, 0, T, F>;//hz
template<typename T = double, typename F = ratio<1,1> >
using angle         = unit< 0,  0,  0,  0,  0, 0, 1, 0, 0, T, F>;//degrees
template<typename T = double, typename F = ratio<1,1> >
using solid_angle   = unit< 0,  0,  0,  0,  0, 0, 2, 0, 0, T, F>;

template<typename T = double, typename F = ratio<1,1> >
using area          = decltype( length<T, F>() * length<T, F>() );
template<typename T = double, typename F = ratio<1,1> >
using volume        = decltype( length<T, F>() * length<T, F>() * length<T, F>() );
template<typename T = double, typename F = ratio<1,1> >
using l_flux        = decltype( l_intensity<T, F>() * solid_angle<T, F>() );//lumen
template<typename T = double, typename F = ratio<1,1> >
using l_illuminance = decltype( l_flux<T, F>() / area<T, F>() );//lux
template<typename T = double, typename F = ratio<1,1> >
using l_exposure    = decltype( l_illuminance<T, F>() * time<T, F>() );
template<typename T = double, typename F = ratio<1,1> >
using l_energy      = decltype( l_flux<T, F>() * time<T, F>() );

template<typename T = double, typename F = ratio<1,1> >
using speed         = decltype( length<T, F>() / time<T, F>() );
template<typename T = double, typename F = ratio<1,1> >
using acceleration  = decltype( speed<T, F>() / time<T, F>() );
template<typename T = double, typename F = ratio<1,1> >
using force         = decltype( mass<T, F>() * acceleration<T, F>() );//newtons
template<typename T = double, typename F = ratio<1,1> >
using momentum      = decltype( mass<T, F>() * speed<T, F>() );
template<typename T = double, typename F = ratio<1,1> >
using energy        = decltype( force<T, F>() * length<T, F>() );//joules
template<typename T = double, typename F = ratio<1,1> >
using power         = decltype( energy<T, F>() / time<T, F>() );//watts

template<typename T = double, typename F = ratio<1,1> >
using voltage       = unit< 2, -3,  1, -1,  0, 0, 0, 0, 0, T, F>;//volts
template<typename T = double, typename F = ratio<1,1> >
using resistance    = unit< 2, -3,  1, -2,  0, 0, 0, 0, 0, T, F>;//ohms
template<typename T = double, typename F = ratio<1,1> >
using capacitance   = unit<-2,  4, -1,  2,  0, 0, 0, 0, 0, T, F>;//farad
template<typename T = double, typename F = ratio<1,1> >
using inductance    = unit< 2, -2,  1, -2,  0, 0, 0, 0, 0, T, F>;//henrys
template<typename T = double, typename F = ratio<1,1> >
using charge        = unit< 0,  1,  0,  1,  0, 0, 0, 0, 0, T, F>;//coulomb
template<typename T = double, typename F = ratio<1,1> >
using resistivity   = decltype( resistance<T, F>() * length<T, F>() );//ohm*meter
template<typename T = double, typename F = ratio<1,1> >
using conductivity  = decltype( none<T, F>( 1 ) / resistivity<T, F>() );//siemens/meter
template<typename T = double, typename F = ratio<1,1> >
using conductance   = decltype( conductivity<T, F>() * length<T, F>() );

template<typename T = double, typename F = ratio<1,1> >
using mag_field     = unit< 0, -2,  1,  1,  0, 0, 0, 0, 0, T, F>;//tesla
template<typename T = double, typename F = ratio<1,1> >
using elec_field    = unit< 1, -3,  1, -1,  0, 0, 0, 0, 0, T, F>;

template<typename T = double, typename F = ratio<1,1> >
using specificHeat  = decltype( energy<T, F>() / temperature<T, F>() );

}

#endif


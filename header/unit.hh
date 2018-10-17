#ifndef __UNIT_HH__
#define __UNIT_HH__

/*! This file defines scientific and other units and their interactions
 *
 * @example test-unit.cc
 */

#include<type_traits>

#include<ratio.hh>
#include<operators.hh>

namespace gsw{

/*!
 * @tparam LENGTH  Distance
 *
 * @tparam TIME  Time
 *
 * @tparam MASS  Mass (not lbs, pounds is a force)
 *
 * @tparam CURRENT  Electric current
 *
 * @tparam TEMPERATURE  Temperature
 *
 * @tparam CANDELA  Brightness
 *
 * @tparam ANGLE  Degrees of angle
 *
 * @tparam MONEY
 *
 * @tparam PERCENTAGE  Percent
 *
 * @tparam TICK  Custom user type.  A common usage may be tick, but can be used
 *               for anything
 *
 * @tparam MOLE Number of things.  1 mole is 6.02214*10^23
 *
 * @tparam BYTE Smallest addressable unit of data
 *
 * The value of LENGTH...BYTE describe the exponent value for that parameter.
 * For example, to describe length, LENGTH will be set to 1, and the rest 0,
 * but to describe area LENGTH will be set to 2 (m^2), and the rest 0, and to
 * describe velocity/speed LENGTH will be set to 1, and TIME to -1 (m/s).
 * Units can be multiplied by another, and this will result in a new,
 * appropriate type.  For instance if speed is multiplied by time, the result
 * will be of type distance.
 *
 * In a practical sense, these types have no particular meaning.  In other words
 * each template parameter can be reassigned a measurement, and used however
 * the user pleases.  Do bear in mind that doing so precludes usage of the
 * special typedefs below, and using said values with other libraries, as those
 * will be using the defaults specified here.
 *
 */
template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY, int ANGLE, int PERCENTAGE, int TICK,
         int MOLE, int BYTE>
class meas{
public:
  static constexpr int length = LENGTH;
  static constexpr int time = TIME;
  static constexpr int mass = MASS;
  static constexpr int current = CURRENT;
  static constexpr int temperature = TEMPERATURE;
  static constexpr int candela = CANDELA;
  static constexpr int money = MONEY;
  static constexpr int angle = ANGLE;
  static constexpr int percentage = PERCENTAGE;
  static constexpr int tick = TICK;
  static constexpr int mole = MOLE;
  static constexpr int byte = BYTE;
};

/*!
 */
template<int LENGTH1, int TIME1, int MASS1, int CURRENT1, int TEMPERATURE1,
         int CANDELA1, int MONEY1, int ANGLE1, int PERCENTAGE1, int TICK1,
         int MOLE1, int BYTE1,
         int LENGTH2, int TIME2, int MASS2, int CURRENT2, int TEMPERATURE2,
         int CANDELA2, int MONEY2, int ANGLE2, int PERCENTAGE2, int TICK2,
         int MOLE2, int BYTE2>
meas<LENGTH1 + LENGTH2, TIME1 + TIME2, MASS1 + MASS2, CURRENT1 + CURRENT2,
     TEMPERATURE1 + TEMPERATURE2, CANDELA1 + CANDELA2, MONEY1 + MONEY2,
     ANGLE1 + ANGLE2, PERCENTAGE1 + PERCENTAGE2, TICK1 + TICK2, MOLE1 + MOLE2,
     BYTE1 + BYTE2>
operator*( const meas<LENGTH1, TIME1, MASS1, CURRENT1, TEMPERATURE1,
                      CANDELA1, MONEY1, ANGLE1, PERCENTAGE1, TICK1, MOLE1, BYTE1>& lhs,
           const meas<LENGTH2, TIME2, MASS2, CURRENT2, TEMPERATURE2,
                      CANDELA2, MONEY2, ANGLE2, PERCENTAGE2, TICK2, MOLE2, BYTE2>& rhs );

/*!
 */
template<int LENGTH1, int TIME1, int MASS1, int CURRENT1, int TEMPERATURE1,
         int CANDELA1, int MONEY1, int ANGLE1, int PERCENTAGE1, int TICK1,
         int MOLE1, int BYTE1,
         int LENGTH2, int TIME2, int MASS2, int CURRENT2, int TEMPERATURE2,
         int CANDELA2, int MONEY2, int ANGLE2, int PERCENTAGE2, int TICK2,
         int MOLE2, int BYTE2>
meas<LENGTH1 - LENGTH2, TIME1 - TIME2, MASS1 - MASS2, CURRENT1 - CURRENT2,
     TEMPERATURE1 - TEMPERATURE2, CANDELA1 - CANDELA2, MONEY1 - MONEY2,
     ANGLE1 - ANGLE2, PERCENTAGE1 - PERCENTAGE2, TICK1 - TICK2, MOLE1 - MOLE2,
     BYTE1 - BYTE2>
operator/( const meas<LENGTH1, TIME1, MASS1, CURRENT1, TEMPERATURE1,
                      CANDELA1, MONEY1, ANGLE1, PERCENTAGE1, TICK1, MOLE1, BYTE1>& lhs,
           const meas<LENGTH2, TIME2, MASS2, CURRENT2, TEMPERATURE2,
                      CANDELA2, MONEY2, ANGLE2, PERCENTAGE2, TICK2, MOLE2, BYTE2>& rhs );

//                              d   t   m   c   T  l  M  a  p  k, ml, B
using none_msr        = meas< 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,  0, 0>;
using length_msr      = meas< 1,  0,  0,  0, 0, 0, 0, 0, 0, 0,  0, 0>;
using mass_msr        = meas< 0,  0,  1,  0, 0, 0, 0, 0, 0, 0,  0, 0>;
using current_msr     = meas< 0,  0,  0,  1, 0, 0, 0, 0, 0, 0,  0, 0>;
using temperature_msr = meas< 0,  0,  0,  0, 1, 0, 0, 0, 0, 0,  0, 0>;
using l_intensity_msr = meas< 0,  0,  0,  0, 0, 1, 0, 0, 0, 0,  0, 0>;
using money_msr       = meas< 0,  0,  0,  0, 0, 0, 1, 0, 0, 0,  0, 0>;
using time_msr        = meas< 0,  1,  0,  0, 0, 0, 0, 0, 0, 0,  0, 0>;
using tick_msr        = meas< 0,  0,  0,  0, 0, 0, 0, 0, 0, 1,  0, 0>;
using percent_msr     = meas< 0,  0,  0,  0, 0, 0, 0, 0, 1, 0,  0, 0>;
using frequency_msr   = meas< 0, -1,  0,  0, 0, 0, 0, 0, 0, 0,  0, 0>;
using angle_msr       = meas< 0,  0,  0,  0, 0, 0, 0, 1, 0, 0,  0, 0>;
using solid_angle_msr = meas< 0,  0,  0,  0, 0, 0, 0, 2, 0, 0,  0, 0>;
using mole_msr        = meas< 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,  1, 0>;
using byte_msr        = meas< 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,  0, 1>;
using voltage_msr     = meas< 2, -3,  1, -1, 0, 0, 0, 0, 0, 0,  0, 0>;
using resistance_msr  = meas< 2, -3,  1, -2, 0, 0, 0, 0, 0, 0,  0, 0>;
using capacitance_msr = meas<-2,  4, -1,  2, 0, 0, 0, 0, 0, 0,  0, 0>;
using inductance_msr  = meas< 2, -2,  1, -2, 0, 0, 0, 0, 0, 0,  0, 0>;
using charge_msr      = meas< 0,  1,  0,  1, 0, 0, 0, 0, 0, 0,  0, 0>;
using mag_field_msr   = meas< 0, -2,  1,  1, 0, 0, 0, 0, 0, 0,  0, 0>;
using elec_field_msr  = meas< 1, -3,  1, -1, 0, 0, 0, 0, 0, 0,  0, 0>;

/*!
 * a unit_system is like metric or imperial.  a particular variable can be of
 * any system, and the systems can convert between each other.  This is to allow
 * syntax such as:
 * length<metric> meters;
 * length<english> feet;
 *
 * meters = 1;
 * feet = meters;
 *
 * REQUIRE( feet == 3.28 );
 */
class metric{};
class english{};

template<typename MEAS, typename SYSTEM, typename DBL, typename FACTOR>
class unit;

template<typename M, typename Si, typename So,
                     typename Ti, typename To,
                     typename Fi, typename Fo>
class converter_base{
public:
  using measure = M;
  using sys_in = Si;
  using sys_out = So;
  using T_in = Ti;
  using T_out = To;
  using factor_in = Fi;
  using factor_out = Fo;
  using conversion_factor = decltype( factor_in() * factor_out().invert() );
  using input = unit<measure, sys_in, T_in, factor_in>;
  using result = unit<measure, sys_out, T_out, factor_out>;

  auto
  conversion_ratio(){
    return conversion_factor();
  }
};

template<typename M, typename Si, typename So,
                     typename Ti, typename To,
                     typename Fi, typename Fo, typename Enable = void>
class converter
      : public converter_base<M, Si, So, Ti, To, Fi, Fo>{
public:
  using base = converter_base<M, Si, So, Ti, To, Fi, Fo>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return unit<typename base::measure, typename base::sys_in,
                typename base::T_out, typename base::factor_out>
                  ( val.getValue() * base::conversion_ratio() );
  }
};

template<typename M, typename S, typename T, typename F>
class converter<M, S, S, T, T, F, F>
      : public converter_base<M, S, S, T, T, F, F>{
public:
  using base = converter_base<M, S, S, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return val;
  }
};

//! @todo add comparitive to unit?
/*! Unit class that differentiates between different measurements.
 *
 * @tparam MEAS Unit of measurement in terms of length, time, mass etc.
 *
 * @tparam SYSTEM System of measurement, (i.e. metric, english, etc)
 *
 * @tparam DBL  Internal storage type.
 *
 * @tparam FACTOR  Prefix factor.  Can be 1:1, 2:1, 1000:1, 1:1000 etc.  Allows
 *                 semantic storage of kilometers (km) and the like.
 *
 * @todo put implementation into a pimpl class?
 *        doing this may decrease the amount of code space increase per template
 *        insantiation. The problem stems from the fact that each instance of a
 *        template is a unique class with a unique definition, and unique code
 *        space. what that means for this class is that each unit and each type
 *        will increase binary size; from volt to kilovolt, from m/s to km. this
 *        impact might be reducable through the pimpl idiom? some idea of implementation:
 *        use a base class or pointer to an implementation class.  the class will take
 *        a storage type and ratio factor only(maybe only storage?), so that code space
 *        only really increases when a different storage type is used.
 */
template<typename MEAS, typename SYSTEM = metric, typename DBL = double, typename FACTOR = ratio<1, 1> >
class unit : public additive<unit<MEAS, SYSTEM, DBL, FACTOR> >,
                    additive<unit<MEAS, SYSTEM, DBL, FACTOR>, DBL>,
                    multiplicative<unit<MEAS, SYSTEM, DBL, FACTOR>, DBL>{
public:
  /*! Storage type
   */
  using value_type = DBL;

  /*! Type storing the order of magnitude of the type(mega, giga etc)
   */
  using factor_type = FACTOR;

  /*! Convenience type used for conversion between storage and factor types
   */
  template<typename S_t = SYSTEM, typename D_t = value_type, typename F_t = factor_type>
  using other_type = unit<MEAS, S_t, D_t, F_t>;

private:
  value_type mValue;

  /*!
   */
  template<typename S_t = SYSTEM, typename D_t = value_type, typename F_t = factor_type>
  using convert_type = converter<MEAS, S_t, SYSTEM, D_t, DBL, F_t, FACTOR>;

public:
  /*! Ctor sets initial internal value
   *
   * @param val  Value to initialize data, defaults to default ctor
   */
  constexpr
  unit( const value_type& val = value_type() )
    : mValue( val ){
  }

  /*!
   */
  constexpr explicit
  operator value_type() const{
    return mValue;
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
  template<typename D, typename F, typename S>
  constexpr
  unit( const other_type<S, D, F>& other )
    : mValue( convert_type<S, D, F>()( other ).getRaw() ){
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
  template<typename D, typename F, typename S>
  constexpr unit&
  operator=( const other_type<S, D, F>& other ){
    mValue = convert_type<S, D, F>()( other ).getRaw() * typename factor_type::invert_type();

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
  constexpr unit&
  operator=( value_type value ){
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
  template<typename D, typename F, typename S>
  constexpr bool
  operator==( const other_type<S, D, F>& other ) const{
    return getRaw() == converter<MEAS, S, SYSTEM, D, D, F, FACTOR>()( other ).getRaw();
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
  template<typename D, typename F, typename S>
  constexpr bool
  operator!=( const other_type<S, D, F>& other ) const{
    return !( *this == other );
  }

  /*! Less than comparison operator
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
  template<typename D, typename F, typename S>
  constexpr bool
  operator<( const other_type<S, D, F>& other ) const{
    return getRaw() < convert_type<S, D, F>()( other ).getRaw();
  }

  /*! Greater than comparison operator
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
  template<typename D, typename F, typename S>
  constexpr bool
  operator>( const other_type<S, D, F>& other ) const{
    return getRaw() > convert_type<S, D, F>()( other ).getRaw();
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
  template<typename D, typename F, typename S>
  constexpr bool
  operator<=( const other_type<S, D, F>& other ) const{
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
  template<typename D, typename F, typename S>
  constexpr bool
  operator>=( const other_type<S, D, F>& other ) const{
    return !( ( *this ) < other );
  }

  /*! Equality comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool
  operator==( value_type other ) const{
    return mValue == other;
  }

  /*! LT comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool
  operator<( value_type other ) const{
    return mValue < other;
  }

  /*! GT comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool
  operator>( value_type other ) const{
    return mValue > other;
  }

  /*! LE comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool
  operator<=( value_type other ) const{
    return !( ( *this ) > other );
  }

  /*! GE comparison operator
   *
   * @param other  Value to compare internal state against
   *
   * @return Result of comparison
   */
  constexpr bool
  operator>=( value_type other ) const{
    return !( ( *this ) < other );
  }

  /*! Prefix increment operator
   *
   * @return Reference to instance operated on, with new value.
   *
   * Increments value.
   */
  constexpr unit&
  operator++(){
    ++mValue;

    return *this;
  }

  /*! Post-fix increment operator
   *
   * @param Unused parameter indicates post-fix
   *
   * @return Value before increment
   */
  constexpr unit
  operator++( int ){
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
  constexpr unit&
  operator--(){
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
  constexpr unit
  operator--( int ){
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
  template<typename D, typename F, typename S>
  constexpr unit&
  operator+=( const other_type<S, D, F>& other ){
    mValue = ( getRaw() + convert_type<S, D, F>()( other ).getRaw() ) / factor_type::value;

    return *this;
  }

  /*! Addition operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return value of the sum of this and other
   *
   * this operator can not be obtained by inheritance from additive.  This is
   * because the D and F parameters are on a per call basis, but would need to
   * be part of the class to be used in inheritance.
   */
  template<typename D, typename F, typename S>
  constexpr auto
  operator+( const other_type<S, D, F>& other ) const{
    return unit( *this ) += convert_type<S, D, F>()( other );
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
  template<typename D, typename F, typename S>
  constexpr unit&
  operator-=( const other_type<S, D, F>& other ){
    mValue = ( getRaw() - convert_type<S, D, F>()( other ).getRaw() ) / factor_type::value;

    return *this;
  }

  /*! Subtraction operator
   *
   * @tparam D  Storage type for other.  Can be anything that can convert into
   *            value_type.
   *
   * @tparam F  Prefix factor.  Can be anything, but expected to be 'k' or 'M' etc.
   *
   * @return value of the difference of this and other
   *
   * this operator can not be obtained by inheritance from additive.  This is
   * because the D and F parameters are on a per call basis, but would need to
   * be part of the class to be used in inheritance.
   */
  template<typename D, typename F, typename S>
  constexpr auto
  operator-( const other_type<S, D, F>& other ) const{
    return unit( *this ) -= convert_type<S, D, F>()( other );
  }

  /*! Add-assignment operator
   *
   * @param other  Value to add to stored value
   *
   * @return Reference to resulting unit
   *
   * Stored value is increased by other, and saved
   */
  constexpr unit&
  operator+=( value_type other ){
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
  constexpr unit&
  operator-=( value_type other ){
    mValue -= other;

    return *this;
  }

  /* *= and /= only work with value_type because the * and / operations return a
   * new type, and therefore cannot be assigned to either operand
   */

  /*! Multiply-assignment operator
   *
   * @param val  Value to multiply by
   *
   * @return Reference to resulting unit
   *
   * Stored value is multiplied by val, and saved
   */
  constexpr unit&
  operator*=( const value_type& val ){
    mValue *= val;

    return *this;
  }

  /*! Divide-assignment operator
   *
   * @param val  Value to divide by
   *
   * @return Resulting unit
   *
   * Stored value is divided by val, and saved
   */
  constexpr unit&
  operator/=( const value_type& val ){
    mValue /= val;

    return *this;
  }

  /*! Get factored, stored value
   */
  constexpr value_type
  getValue() const{
    return mValue;
  }

  /*! Retrieve actual raw value (factor is taken into account)
   */
  constexpr value_type
  getRaw() const{
    return ( mValue * factor_type::value );
  }
};

/*!
 * @param u
 * @param d
 */
template<typename MEAS, typename SYSTEM = metric, typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<MEAS, SYSTEM, DBL, FACTOR>
operator*( const unit<MEAS, SYSTEM, DBL, FACTOR>& u, const DBL& d ){
  unit<MEAS, SYSTEM, DBL, FACTOR> cp( u );

  cp *= d;

  return cp;
}

/*!
 * @param d
 * @param u
 */
template<typename MEAS, typename SYSTEM = metric, typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<MEAS, SYSTEM, DBL, FACTOR>
operator*( const DBL& d, const unit<MEAS, SYSTEM, DBL, FACTOR>& u ){
  unit<MEAS, SYSTEM, DBL, FACTOR> cp( u );

  cp *= d;

  return cp;
}

/*!
 * @param u
 * @param d
 */
template<typename MEAS, typename SYSTEM = metric, typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<MEAS, SYSTEM, DBL, FACTOR>
operator/( const unit<MEAS, SYSTEM, DBL, FACTOR>& u, const DBL& d ){
  unit<MEAS, SYSTEM, DBL, FACTOR> cp( u );

  cp /= d;

  return cp;
}

/*!
 * @param d
 * @param u
 */
template<typename MEAS, typename SYSTEM = metric, typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<MEAS, SYSTEM, DBL, FACTOR>
operator/( const DBL& d, const unit<MEAS, SYSTEM, DBL, FACTOR>& u ){
  unit<MEAS, SYSTEM, DBL, FACTOR> cp( u );

  cp /= d;

  return cp;
}

/*! Multiplication operator
 *
 * @tparam Template parameters reflect those available for the class itself.
 *         There are 2 sets of parameters, one for the lhs and the other for
 *         the rhs.
 *
 * @return Returns a 3rd type, where each template parameter is the sum of the
 *         equivalent parameters of the lhs and rhs.
 */
template<typename MEAS1, typename MEAS2,
         typename S_t1, typename S_t2,
         typename D_t1, typename D_t2,
         typename F_t1, typename F_t2>
constexpr
unit<decltype( MEAS1() * MEAS2() ), S_t1, D_t1, decltype( F_t1() * F_t2() )>
operator*( const unit<MEAS1, S_t1, D_t1, F_t1>& lhs,
           const unit<MEAS2, S_t2, D_t2, F_t2>& rhs ){
  return lhs.getValue() * converter<MEAS2, S_t2, S_t1, D_t2, D_t1, F_t2, F_t2>()( rhs ).getValue();
}

/*! Division operator
 *
 * @tparam Template parameters reflect those available for the class itself.
 *         There are 2 sets of parameters, one for the lhs and the other for
 *         the rhs.
 *
 * @return Returns a 3rd type, where each template parameter is the difference
 *         of the equivalent parameters of the lhs and rhs.
 */
template<typename MEAS1, typename MEAS2,
         typename S_t1, typename S_t2,
         typename D_t1, typename D_t2,
         typename F_t1, typename F_t2>
constexpr
unit<decltype( MEAS1() / MEAS2() ), S_t1, D_t1, decltype( F_t1() / F_t2() )>
operator/( const unit<MEAS1, S_t1, D_t1, F_t1>& lhs,
           const unit<MEAS2, S_t2, D_t2, F_t2>& rhs ){
  return lhs.getValue() / converter<MEAS2, S_t2, S_t1, D_t2, D_t1, F_t2, F_t2>()( rhs ).getValue();
}

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using none          = unit<none_msr, S, T, F>;

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using length        = unit<length_msr, S, T, F>;//meters
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using mass          = unit<mass_msr, S, T, F>;//kg
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using current       = unit<current_msr, S, T, F>;//amps
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using temperature   = unit<temperature_msr, S, T, F>;//kelvin
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using l_intensity   = unit<l_intensity_msr, S, T, F>;//luminous intensity, candela
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using money         = unit<money_msr, S, T, F>;//dolla dolla bills
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using time          = unit<time_msr, S, T, F>;//seconds
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using tick          = unit<tick_msr, S, T, F>;
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using percent       = unit<percent_msr, S, T, F>;//%
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using frequency     = unit<frequency_msr, S, T, F>;//hz
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using angle         = unit<angle_msr, S, T, F>;//degrees
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using solid_angle   = unit<solid_angle_msr, S, T, F>;
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using mole          = unit<mole_msr, S, T, F>;
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using byte          = unit<byte_msr, S, T, F>;

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using area          = decltype( length<T, S, F>() * length<T, S, F>() );
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using volume        = decltype( length<T, S, F>() * length<T, S, F>() * length<T, S, F>() );

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using l_flux        = decltype( l_intensity<T, S, F>() * solid_angle<T, S, F>() );//lumen
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using l_illuminance = decltype( l_flux<T, S, F>() / area<T, S, F>() );//lux
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using l_exposure    = decltype( l_illuminance<T, S, F>() * time<T, S, F>() );
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using l_energy      = decltype( l_flux<T, S, F>() * time<T, S, F>() );

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using speed         = decltype( length<T, S, F>() / time<T, S, F>() );
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using acceleration  = decltype( speed<T, S, F>() / time<T, S, F>() );
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using force         = decltype( mass<T, S, F>() * acceleration<T, S, F>() );//newtons
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using momentum      = decltype( mass<T, S, F>() * speed<T, S, F>() );
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using energy        = decltype( force<T, S, F>() * length<T, S, F>() );//joules
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using power         = decltype( energy<T, S, F>() / time<T, S, F>() );//watts

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using voltage       = unit<voltage_msr, S, T, F>;//volts
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using resistance    = unit<resistance_msr, S, T, F>;//ohms
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using capacitance   = unit<capacitance_msr, S, T, F>;//farad
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using inductance    = unit<inductance_msr, S, T, F>;//henrys
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using charge        = unit<charge_msr, S, T, F>;//coulomb
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using resistivity   = decltype( resistance<T, S, F>() * length<T, S, F>() );//ohm*meter
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using conductivity  = decltype( none<T, S, F>() / resistivity<T, S, F>() );//siemens/meter
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using conductance   = decltype( conductivity<T, S, F>() * length<T, S, F>() );

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using mag_field     = unit<mag_field_msr, S, T, F>;//tesla
template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using elec_field    = unit<elec_field_msr, S, T, F>;

template<typename T = double, typename S = metric, typename F = ratio<1, 1> >
using specificHeat  = decltype( energy<T, S, F>() / temperature<T, S, F>() );

/* measurement system specific */
/* metric */
template<typename T = double, typename F = ratio<1, 1> >
using meters = length<T, metric, F>;

template<typename T = double, typename F = ratio<1, 1> >
using gram = mass<T, metric, F>;

template<typename T = double, typename F = ratio<1, 1> >
using celsius = temperature<T, metric, F>;

/* english */
template<typename T = double, typename F = ratio<1, 1> >
using feet = length<T, english, F>;

template<typename T = double, typename F = ratio<1, 1> >
using slug = mass<T, english, F>;

template<typename T = double, typename F = ratio<1, 1> >
using fahrenheit = temperature<T, english, F>;

/* english->metric */
template<typename T, typename F>
class converter<length_msr, english, metric, T, T, F, F>
      : public converter_base<length_msr, english, metric, T, T, F, F>{
public:
  using base = converter_base<length_msr, english, metric, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() * 0.30481 );
  }
};

template<typename T, typename F>
class converter<temperature_msr, english, metric, T, T, F, F>
      : public converter_base<temperature_msr, english, metric, T, T, F, F>{
public:
  using base = converter_base<temperature_msr, english, metric, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( ( val.getRaw() - 32 ) * ( 5 / 9 ) );
  }
};

template<typename T, typename F>
class converter<mass_msr, english, metric, T, T, F, F>
      : public converter_base<mass_msr, english, metric, T, T, F, F>{
public:
  using base = converter_base<mass_msr, english, metric, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() * 14593.9 );
  }
};

/* metric->english */
template<typename T, typename F>
class converter<length_msr, metric, english, T, T, F, F>
      : public converter_base<length_msr, metric, english, T, T, F, F>{
public:
  using base = converter_base<length_msr, metric, english, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() * 3.28084 );
  }
};

template<typename T, typename F>
class converter<temperature_msr, metric, english, T, T, F, F>
      : public converter_base<temperature_msr, metric, english, T, T, F, F>{
public:
  using base = converter_base<temperature_msr, metric, english, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( ( val.getRaw() * ( 9 / 5 ) ) + 32 );
  }
};

template<typename T, typename F>
class converter<mass_msr, metric, english, T, T, F, F>
      : public converter_base<mass_msr, metric, english, T, T, F, F>{
public:
  using base = converter_base<mass_msr, metric, english, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() / 14593.9 );
  }
};

//@todo should the unity conversions be /ANY/ system?
// probably not
/* unity conversions */
template<typename Si, typename So, typename T, typename F>
class converter<tick_msr, Si, So, T, T, F, F,
                typename std::enable_if<!std::is_same<Si, So>::value>::type>
      : public converter_base<tick_msr, Si, So, T, T, F, F>{
public:
  using base = converter_base<tick_msr, Si, So, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() );
  }
};

template<typename Si, typename So, typename T, typename F>
class converter<time_msr, Si, So, T, T, F, F,
                typename std::enable_if<!std::is_same<Si, So>::value>::type>
      : public converter_base<time_msr, Si, So, T, T, F, F>{
public:
  using base = converter_base<time_msr, Si, So, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() );
  }
};

template<typename Si, typename So, typename T, typename F>
class converter<percent_msr, Si, So, T, T, F, F,
                typename std::enable_if<!std::is_same<Si, So>::value>::type>
      : public converter_base<percent_msr, Si, So, T, T, F, F>{
public:
  using base = converter_base<percent_msr, Si, So, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() );
  }
};

template<typename Si, typename So, typename T, typename F>
class converter<frequency_msr, Si, So, T, T, F, F,
                typename std::enable_if<!std::is_same<Si, So>::value>::type>
      : public converter_base<frequency_msr, Si, So, T, T, F, F>{
public:
  using base = converter_base<frequency_msr, Si, So, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() );
  }
};

template<typename Si, typename So, typename T, typename F>
class converter<current_msr, Si, So, T, T, F, F,
                typename std::enable_if<!std::is_same<Si, So>::value>::type>
      : public converter_base<current_msr, Si, So, T, T, F, F>{
public:
  using base = converter_base<current_msr, Si, So, T, T, F, F>;

  constexpr
  converter() = default;

  constexpr
  typename base::result
  operator()( const typename base::input& val ){
    return typename base::result( val.getRaw() );
  }
};

/* floating point literals */
constexpr auto operator""_0( long double val ){
  return none<long double>( val );
}

constexpr auto operator""_len( long double val ){
  return length<long double>( val );
}

constexpr auto operator""_mass( long double val ){
  return mass<long double>( val );
}

constexpr auto operator""_A( long double val ){
  return current<long double>( val );
}

constexpr auto operator""_temp( long double val ){
  return temperature<long double>( val );
}

constexpr auto operator""_t( long double val ){
  return time<long double>( val );
}

constexpr auto operator""_V( long double val ){
  return voltage<long double>( val );
}

constexpr auto operator""_R( long double val ){
  return resistance<long double>( val );
}

constexpr auto operator""_mny( long double val ){
  return money<long double>( val );
}

constexpr auto operator""_tk( long double val ){
  return tick<long double>( val );
}

/* integral literals */
constexpr auto operator""_0( unsigned long long val ){
  return none<unsigned long long>( val );
}

constexpr auto operator""_len( unsigned long long val ){
  return length<unsigned long long>( val );
}

constexpr auto operator""_mass( unsigned long long val ){
  return mass<unsigned long long>( val );
}

constexpr auto operator""_A( unsigned long long val ){
  return current<unsigned long long>( val );
}

constexpr auto operator""_temp( unsigned long long val ){
  return temperature<unsigned long long>( val );
}

constexpr auto operator""_t( unsigned long long val ){
  return time<unsigned long long>( val );
}

constexpr auto operator""_V( unsigned long long val ){
  return voltage<unsigned long long>( val );
}

constexpr auto operator""_R( unsigned long long val ){
  return resistance<unsigned long long>( val );
}

constexpr auto operator""_mny( unsigned long long val ){
  return money<unsigned long long>( val );
}

constexpr auto operator""_tk( unsigned long long val ){
  return tick<unsigned long long>( val );
}

}

#endif

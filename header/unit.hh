#ifndef __UNIT_HH__
#define __UNIT_HH__

/*! This file defines scientific and other units and their interactions
 *
 * @example test-unit.cc
 */

#include<ratio.hh>
#include<operators.hh>

namespace gsw{

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

/*template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY, int ANGLE, int PERCENTAGE, int TICK>
class unit_params{
public:
  static constexpr length = LENGTH;
  static constexpr time = TIME;
  static constexpr mass = MASS;
  static constexpr current = CURRENT;
  static constexpr temperature = TEMPERATURE;
  static constexpr candela = CANDELA;
  static constexpr money = MONEY;
  static constexpr angle = ANGLE;
  static constexpr percentage = PERCENTAGE;
  static constexpr tick = TICK;
};

template<typename T>
class unit_system{
private:
  double length;
  double time;
  double mass;
  double current;
  double temperature;
  double candela;
  double money;
  double angle;
  double percentage;
  double tick;

public:
  using system = T;

  double
  length_factor() const{
    return length;
  }

  double
  time_factor() const{
    return time;
  }

  double
  mass_factor() const{
    return mass;
  }

  double
  current_factor() const{
    return current;
  }

  double
  temperature_factor() const{
    return temperature;
  }

  double
  candela_factor() const{
    return candela;
  }

  double
  money_factor() const{
    return money;
  }

  double
  angle_factor() const{
    return angle;
  }

  double
  percentage_factor() const{
    return percentage;
  }

  double
  tick_factor() const{
    return tick;
  }
};

class base : public unit_system<metric>{
public:
  base()
    : length( 1 )//foot
    , time( 1 )//second
    , mass( 1 )//kg
    , current( 1 )//amp
    , temperature( 1 )//fahrenheit
    , candela( 1 )
    , money( 1 )//yen?
    , angle( 1 )//degree?
    , percentage( 1 )
    , tick( 1 ){
  }
};

class metric : public unit_system<metric>{
  metric()
    : length( 3.2 )
    , time( 1 )
    , mass( 1 )
    , current( 1 )
    , temperature( 1 )//non linear conversion?
    , candela( 1 )
    , money( 100 )
    , angle( 120 )//radian
    , percentage( 1 )
    , tick( 1 ){
  }
};

class english : public unit_system<english>{
  english()
    : length( 1 )
    , time( 1 )
    , mass( 14 )//slug
    , current( 1 )
    , temperature( 1 )//non linear conversion?
    , candela( 1 )
    , money( 100 )
    , angle( 1)//radian
    , percentage( 1 )
    , tick( 1 ){
  }
};

using default_system = metric;
*/
//! @todo add comparitive to unit?
/*! Unit class that differentiates between different measurements.
 *
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
 * @tparam DBL  Internal storage type.
 *
 * @tparam FACTOR  Prefix factor.  Can be 1:1, 2:1, 1000:1, 1:1000 etc.  Allows
 *                 semantic storage of kilometers (km) and the like.
 *
 * The value of LENGTH...TICK describe the exponent value for that parameter.
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
 * @todo add byte and mole?
 * @todo put implementation into a pimpl class?
 *        doing this may decrease the amount of code space increase through template
 *        insantiation. The problem stems from the fact that each instance of a
 *        template is a unique class with a unique definition, and unique code
 *        space. what that means for this class is that each unit and each type
 *        will increase binary size; from volt to kilovolt, from m/s to km. this
 *        impact might be reducable through the pimpl idiom? some idea of implementation:
 *        use a base class or pointer to an implementation class.  the class will take
 *        a storage type and ratio factor only(maybe only storage?), so that code space
 *        only really increases when a different storage type is used.
 *        
 */
template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY = 0, int ANGLE = 0, int PERCENTAGE = 0, int TICK = 0,
         typename SYSTEM, typename DBL = double, typename FACTOR = ratio<1, 1> >
class unit : public additive<unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE,
                                  CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, SYSTEM, DBL, FACTOR> >,
                    additive<unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE,
                                  CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, SYSTEM, DBL, FACTOR>,
                                  DBL>,
                    multiplicative<unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA,
                                        MONEY, ANGLE, PERCENTAGE, TICK, SYSTEM, DBL, FACTOR>,
                                        DBL>{
public:
  /*! Storage type
   */
  using value_type = DBL;

  /*! Type storing the order of magnitude of the type(mega, giga etc)
   */
  using factor_type = FACTOR;

  /*! Convenience type used for conversion between storage and factor types
   */
  template<typename D_t = value_type, typename F_t = factor_type>
  using other_type = unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA,
                          MONEY, ANGLE, PERCENTAGE, TICK, D_t, F_t>;

  //! @todo provide static constexpr aliases to types
  // done something like:
  // static constexpr int CURRENCY = MONEY;
  // primary problem is to find names for these aliases that aren't the param names 

private:
  value_type mValue;

public:
  /*! Ctor sets initial internal value
   *
   * @param val  Value to initialize data, defaults to default ctor
   */
  constexpr
  unit( const value_type& val = value_type() ):
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
  constexpr
  unit( const other_type<D, F>& other ):
    mValue( ( other.getRaw() * factor_type::denominator ) / factor_type::numerator ){
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
  constexpr unit&
  operator=( const other_type<D, F>& other ){
    mValue = other.getRaw() * typename factor_type::invert_type();

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
  template<typename D, typename F>
  constexpr bool
  operator==( const other_type<D, F>& other ) const{
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
  constexpr bool
  operator!=( const other_type<D, F>& other ) const{
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
  template<typename D, typename F>
  constexpr bool
  operator<( const other_type<D, F>& other ) const{
    return getRaw() < other.getRaw();
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
  template<typename D, typename F>
  constexpr bool
  operator>( const other_type<D, F>& other ) const{
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
  constexpr bool
  operator<=( const other_type<D, F>& other ) const{
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
  constexpr bool
  operator>=( const other_type<D, F>& other ) const{
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
  template<typename D, typename F>
  constexpr unit&
  operator+=( const other_type<D, F>& other ){
    mValue = ( getRaw() + other.getRaw() ) / factor_type::value;

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
  template<typename D, typename F>
  constexpr auto
  operator+( const other_type<D,F>& other ) const{
    return unit( *this ) += other;
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
  constexpr unit&
  operator-=( const other_type<D, F>& other ){
    mValue = ( getRaw() - other.getRaw() ) / factor_type::value;

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
  template<typename D, typename F>
  constexpr auto
  operator-( const other_type<D,F>& other ) const{
    return unit( *this ) -= other;
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

template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY = 0, int ANGLE = 0, int PERCENTAGE = 0, int TICK = 0,
         typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>
operator*( const unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>& u, const DBL& d ){
  unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR> cp( u );

  cp *= d;

  return cp;
}

template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY = 0, int ANGLE = 0, int PERCENTAGE = 0, int TICK = 0,
         typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>
operator*( const DBL& d, const unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>& u ){
  unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR> cp( u );

  cp *= d;

  return cp;
}

template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY = 0, int ANGLE = 0, int PERCENTAGE = 0, int TICK = 0,
         typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>
operator/( const unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>& u, const DBL& d ){
  unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR> cp( u );

  cp /= d;

  return cp;
}

template<int LENGTH, int TIME, int MASS, int CURRENT, int TEMPERATURE,
         int CANDELA, int MONEY = 0, int ANGLE = 0, int PERCENTAGE = 0, int TICK = 0,
         typename DBL = double, typename FACTOR = ratio<1, 1> >
unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>
operator/( const DBL& d, const unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR>& u ){
  unit<LENGTH, TIME, MASS, CURRENT, TEMPERATURE, CANDELA, MONEY, ANGLE, PERCENTAGE, TICK, DBL, FACTOR> cp( u );

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
 *
 */
template<int LENGTH1, int TIME1, int MASS1, int CURRENT1, int TEMPERATURE1,
         int CANDELA1, int MONEY1, int ANGLE1, int PERCENTAGE1, int TICK1,
         int LENGTH2, int TIME2, int MASS2, int CURRENT2, int TEMPERATURE2,
         int CANDELA2, int MONEY2, int ANGLE2, int PERCENTAGE2, int TICK2,
         typename D_t1, typename D_t2,
         typename F_t1, typename F_t2>
constexpr
unit<LENGTH1 + LENGTH2, TIME1 + TIME2, MASS1 + MASS2, CURRENT1 + CURRENT2,
     TEMPERATURE1 + TEMPERATURE2, CANDELA1 + CANDELA2, MONEY1 + MONEY2, ANGLE1 + ANGLE2, PERCENTAGE1 + PERCENTAGE2, TICK1 + TICK2,
     D_t1, decltype( F_t1() * F_t2() )>
operator*( const unit<LENGTH1, TIME1, MASS1, CURRENT1, TEMPERATURE1,
                      CANDELA1, MONEY1, ANGLE1, PERCENTAGE1, TICK1, D_t1, F_t1>& lhs,
           const unit<LENGTH2, TIME2, MASS2, CURRENT2, TEMPERATURE2,
                      CANDELA2, MONEY2, ANGLE2, PERCENTAGE2, TICK2, D_t2, F_t2>& rhs ){
  return lhs.getValue() * rhs.getValue();
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
template<int LENGTH1, int TIME1, int MASS1, int CURRENT1, int TEMPERATURE1,
         int CANDELA1, int MONEY1, int ANGLE1, int PERCENTAGE1, int TICK1,
         int LENGTH2, int TIME2, int MASS2, int CURRENT2, int TEMPERATURE2,
         int CANDELA2, int MONEY2, int ANGLE2, int PERCENTAGE2, int TICK2,
         typename D_t1, typename D_t2,
         typename F_t1, typename F_t2>
constexpr
unit<LENGTH1 - LENGTH2, TIME1 - TIME2, MASS1 - MASS2, CURRENT1 - CURRENT2,
     TEMPERATURE1 - TEMPERATURE2, CANDELA1 - CANDELA2, MONEY1 - MONEY2, ANGLE1 - ANGLE2, PERCENTAGE1 - PERCENTAGE2, TICK1 - TICK2,
     D_t1, decltype( F_t1() / F_t2() )>
operator/( const unit<LENGTH1, TIME1, MASS1, CURRENT1, TEMPERATURE1,
                      CANDELA1, MONEY1, ANGLE1, PERCENTAGE1, TICK1, D_t1, F_t1>& lhs,
           const unit<LENGTH2, TIME2, MASS2, CURRENT2, TEMPERATURE2,
                      CANDELA2, MONEY2, ANGLE2, PERCENTAGE2, TICK2, D_t2, F_t2>& rhs ){
  return lhs.getValue() / rhs.getValue();
}

//                          m   s  kg   A   K  C  $  D  P  T
template<typename T = double, typename F = ratio<1, 1> >
using none          = unit< 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, T, F>;

template<typename T = double, typename F = ratio<1, 1> >
using length        = unit< 1,  0,  0,  0,  0, 0, 0, 0, 0, 0, T, F>;//meters
template<typename T = double, typename F = ratio<1, 1> >
using mass          = unit< 0,  0,  1,  0,  0, 0, 0, 0, 0, 0, T, F>;//kg
template<typename T = double, typename F = ratio<1, 1> >
using current       = unit< 0,  0,  0,  1,  0, 0, 0, 0, 0, 0, T, F>;//amps
template<typename T = double, typename F = ratio<1, 1> >
using temperature   = unit< 0,  0,  0,  0,  1, 0, 0, 0, 0, 0, T, F>;//kelvin
template<typename T = double, typename F = ratio<1, 1> >
using l_intensity   = unit< 0,  0,  0,  0,  0, 1, 0, 0, 0, 0, T, F>;//luminous intensity, candela
template<typename T = double, typename F = ratio<1, 1> >
using money         = unit< 0,  0,  0,  0,  0, 0, 1, 0, 0, 0, T, F>;//dolla dolla bills
template<typename T = double, typename F = ratio<1, 1> >
using time          = unit< 0,  1,  0,  0,  0, 0, 0, 0, 0, 0, T, F>;//seconds
template<typename T = double, typename F = ratio<1, 1> >
using tick          = unit< 0,  0,  0,  0,  0, 0, 0, 0, 0, 1, T, F>;
template<typename T = double, typename F = ratio<1, 1> >
using percent       = unit< 0,  0,  0,  0,  0, 0, 0, 0, 1, 0, T, F>;//%
template<typename T = double, typename F = ratio<1, 1> >
using frequency     = unit< 0, -1,  0,  0,  0, 0, 0, 0, 0, 0, T, F>;//hz
template<typename T = double, typename F = ratio<1, 1> >
using angle         = unit< 0,  0,  0,  0,  0, 0, 0, 1, 0, 0, T, F>;//degrees
template<typename T = double, typename F = ratio<1, 1> >
using solid_angle   = unit< 0,  0,  0,  0,  0, 0, 0, 2, 0, 0, T, F>;

template<typename T = double, typename F = ratio<1, 1> >
using area          = decltype( length<T, F>() * length<T, F>() );
template<typename T = double, typename F = ratio<1, 1> >
using volume        = decltype( length<T, F>() * length<T, F>() * length<T, F>() );
template<typename T = double, typename F = ratio<1, 1> >
using l_flux        = decltype( l_intensity<T, F>() * solid_angle<T, F>() );//lumen
template<typename T = double, typename F = ratio<1, 1> >
using l_illuminance = decltype( l_flux<T, F>() / area<T, F>() );//lux
template<typename T = double, typename F = ratio<1, 1> >
using l_exposure    = decltype( l_illuminance<T, F>() * time<T, F>() );
template<typename T = double, typename F = ratio<1, 1> >
using l_energy      = decltype( l_flux<T, F>() * time<T, F>() );

template<typename T = double, typename F = ratio<1, 1> >
using speed         = decltype( length<T, F>() / time<T, F>() );
template<typename T = double, typename F = ratio<1, 1> >
using acceleration  = decltype( speed<T, F>() / time<T, F>() );
template<typename T = double, typename F = ratio<1, 1> >
using force         = decltype( mass<T, F>() * acceleration<T, F>() );//newtons
template<typename T = double, typename F = ratio<1, 1> >
using momentum      = decltype( mass<T, F>() * speed<T, F>() );
template<typename T = double, typename F = ratio<1, 1> >
using energy        = decltype( force<T, F>() * length<T, F>() );//joules
template<typename T = double, typename F = ratio<1, 1> >
using power         = decltype( energy<T, F>() / time<T, F>() );//watts

template<typename T = double, typename F = ratio<1, 1> >
using voltage       = unit< 2, -3,  1, -1,  0, 0, 0, 0, 0, 0, T, F>;//volts
template<typename T = double, typename F = ratio<1, 1> >
using resistance    = unit< 2, -3,  1, -2,  0, 0, 0, 0, 0, 0, T, F>;//ohms
template<typename T = double, typename F = ratio<1, 1> >
using capacitance   = unit<-2,  4, -1,  2,  0, 0, 0, 0, 0, 0, T, F>;//farad
template<typename T = double, typename F = ratio<1, 1> >
using inductance    = unit< 2, -2,  1, -2,  0, 0, 0, 0, 0, 0, T, F>;//henrys
template<typename T = double, typename F = ratio<1, 1> >
using charge        = unit< 0,  1,  0,  1,  0, 0, 0, 0, 0, 0, T, F>;//coulomb
template<typename T = double, typename F = ratio<1, 1> >
using resistivity   = decltype( resistance<T, F>() * length<T, F>() );//ohm*meter
template<typename T = double, typename F = ratio<1, 1> >
using conductivity  = decltype( none<T, F>( 1 ) / resistivity<T, F>() );//siemens/meter
template<typename T = double, typename F = ratio<1, 1> >
using conductance   = decltype( conductivity<T, F>() * length<T, F>() );

template<typename T = double, typename F = ratio<1, 1> >
using mag_field     = unit< 0, -2,  1,  1,  0, 0, 0, 0, 0, 0, T, F>;//tesla
template<typename T = double, typename F = ratio<1, 1> >
using elec_field    = unit< 1, -3,  1, -1,  0, 0, 0, 0, 0, 0, T, F>;

template<typename T = double, typename F = ratio<1, 1> >
using specificHeat  = decltype( energy<T, F>() / temperature<T, F>() );

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

}

#endif


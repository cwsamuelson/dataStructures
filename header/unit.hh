#ifndef __UNIT_HH__
#define __UNIT_HH__

template<int METERS, int SECONDS, int KILOGRAM, int AMPERE, int KELVIN, int CANDELA, typename DBL = double>
class unit{
private:
  DBL mValue;

public:
  unit():
    mValue(0.0){
  }
  unit(DBL val):
    mValue(val){
  }
  unit(const unit& other):
    unit(other.mValue){
  }
  unit(unit&& other):
    unit(other.mValue){
  }

  unit& operator=(const unit& other){
    mValue = other.mValue;
    return *this;
  }
  unit& operator=(DBL value){
    mValue = value;
    return *this;
  }

  bool operator==(const unit& other) const{
    //TODO: allow slight error(epsilon)
    return mValue == other.mValue;
  }
  bool operator<( const unit& other ) const{
    return mValue < other.mValue;
  }
  bool operator>( const unit& other ) const{
    return mValue > other.mValue;
  }
  bool operator<=( const unit& other ) const{
    return !( ( *this ) > other );
  }
  bool operator>=( const unit& other ) const{
    return !( ( *this ) < other );
  }
  bool operator==(DBL other) const{
    return mValue == other;
  }
  bool operator<( DBL other ) const{
    return mValue < other;
  }
  bool operator>( DBL other ) const{
    return mValue > other;
  }
  bool operator<=( DBL other ) const{
    return !( ( *this ) > other );
  }
  bool operator>=( DBL other ) const{
    return !( ( *this ) < other );
  }

  unit operator+(const unit& other) const{
    return mValue + other.mValue;
  }
  unit operator-(const unit& other) const{
    return mValue - other.mValue;
  }

  unit& operator+=(const unit& other){
    this->mValue = mValue + other.mValue;
    return *this;
  }
  unit& operator-=(const unit& other){
    this->mValue = mValue - other.mValue;
    return *this;
  }

  unit& operator*=( const DBL& val ){
    mValue *= val;
    return ( *this );
  }
  unit& operator/=( const DBL& val ){
    mValue /= val;
    return ( *this );
  }
  /* *= and /= only work with doubles because the * and / operations return a new type,
   * and therefore cannot be assigned to either operand
   */

  DBL& getValue(){ return mValue; }
  DBL getValue() const{ return mValue; }

  template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, 
       int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2>
  friend
  unit<METERS1 + METERS2, SECONDS1 + SECONDS2, KILOGRAM1 + KILOGRAM2,
       AMPERE1 + AMPERE2, KELVIN1 + KELVIN2, CANDELA1 + CANDELA2>
  operator*(const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1>& lhs,
            const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2>& rhs);

  template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, 
           int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2>
  friend
  unit<METERS1 - METERS2, SECONDS1 - SECONDS2, KILOGRAM1 - KILOGRAM2,
       AMPERE1 - AMPERE2, KELVIN1 - KELVIN2, CANDELA1 - CANDELA2>
  operator/(const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1>& lhs,
            const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2>& rhs);

  template<int METERS0, int SECONDS0, int KILOGRAM0, int AMPERE0, int KELVIN0, int CANDELA0, class OSTREAM>
  friend
  OSTREAM&
  operator<<(OSTREAM& os, const unit<METERS0, SECONDS0, KILOGRAM0, AMPERE0, KELVIN0, CANDELA0>& val);
  
  template<int METERS0, int SECONDS0, int KILOGRAM0, int AMPERE0, int KELVIN0, int CANDELA0, class ISTREAM>
  friend
  ISTREAM&
  operator>>(ISTREAM& is, unit<METERS0, SECONDS0, KILOGRAM0, AMPERE0, KELVIN0, CANDELA0>& val);
};

template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, 
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2>
unit<METERS1 + METERS2, SECONDS1 + SECONDS2, KILOGRAM1 + KILOGRAM2,
     AMPERE1 + AMPERE2, KELVIN1 + KELVIN2, CANDELA1 + CANDELA2>
operator*(const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1>& lhs,
          const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2>& rhs){
  return lhs.mValue * rhs.mValue;
}

template<int METERS1, int SECONDS1, int KILOGRAM1, int AMPERE1, int KELVIN1, int CANDELA1, 
         int METERS2, int SECONDS2, int KILOGRAM2, int AMPERE2, int KELVIN2, int CANDELA2>
unit<METERS1 - METERS2, SECONDS1 - SECONDS2, KILOGRAM1 - KILOGRAM2,
     AMPERE1 - AMPERE2, KELVIN1 - KELVIN2, CANDELA1 - CANDELA2>
operator/(const unit<METERS1, SECONDS1, KILOGRAM1, AMPERE1, KELVIN1, CANDELA1>& lhs,
          const unit<METERS2, SECONDS2, KILOGRAM2, AMPERE2, KELVIN2, CANDELA2>& rhs){
  return lhs.mValue / rhs.mValue;
}

template<int METERS0, int SECONDS0, int KILOGRAM0, int AMPERE0, int KELVIN0, int CANDELA0, class OSTREAM>
OSTREAM&
operator<<(OSTREAM& os, const unit<METERS0, SECONDS0, KILOGRAM0, AMPERE0, KELVIN0, CANDELA0>& val){
  os << val.mValue;
  return os;
}

template<int METERS0, int SECONDS0, int KILOGRAM0, int AMPERE0, int KELVIN0, int CANDELA0, class ISTREAM>
ISTREAM&
operator>>(ISTREAM& is, unit<METERS0, SECONDS0, KILOGRAM0, AMPERE0, KELVIN0, CANDELA0>& val){
  is >> val.mValue;
  return is;
}

/* 'thyme' should be renamed back to 'time' when a namespace is established, as
 * name collision would be disambiguated using <namespace>::time vs (i.e.) std::time
 */
//                         m   s   kg  A   K  C
template<typename T = double>
using length       = unit< 1,  0,  0,  0,  0, 0, T>;
template<typename T = double>
using thyme        = unit< 0,  1,  0,  0,  0, 0, T>;//time, renamed to avoid collision
template<typename T = double>
using mass         = unit< 0,  0,  1,  0,  0, 0> mass;
template<typename T = double>
using current      = unit< 0,  0,  0,  1,  0, 0> current;//amps
template<typename T = double>
using temperature  = unit< 0,  0,  0,  0,  1, 0> temperature;//kelvin
template<typename T = double>
using light        = unit< 0,  0,  0,  0,  0, 1> light;//candela

template<typename T = double>
using speed        = unit< 1, -1,  0,  0,  0, 0> speed;
template<typename T = double>
using acceleration = unit< 1, -2,  0,  0,  0, 0> acceleration;
template<typename T = double>
using force        = unit< 1, -2,  1,  0,  0, 0> force;//newton
template<typename T = double>
using momentum     = unit< 1, -1,  1,  0,  0, 0> momentum;
template<typename T = double>
using energy       = unit< 2, -2,  1,  0,  0, 0> energy;//joules
template<typename T = double>
using power        = unit< 2, -3,  1,  0,  0, 0> power;//watts

template<typename T = double>
using voltage      = unit< 2, -3,  1, -1,  0, 0> voltage;
template<typename T = double>
using resistance   = unit< 2, -3,  1, -2,  0, 0> resistance;//ohms
template<typename T = double>
using capacitance  = unit<-2,  4, -1,  2,  0, 0> capacitance;//farad
template<typename T = double>
using inductance   = unit< 2, -2,  1, -2,  0, 0> inductance;//henrys
template<typename T = double>
using charge       = unit< 0,  1,  0,  1,  0, 0> charge;//coulomb

template<typename T = double>
using magField     = unit< 0, -2,  1,  1,  0, 0> magField;//tesla
template<typename T = double>
using elecField    = unit< 1, -3,  1, -1,  0, 0> elecField;

template<typename T = double>
using specificHeat = unit< 2, -2,  1,  0, -1, 0> specificHeat;
//OR typedef decltype( energy / temperature ) specificHeat;

#endif


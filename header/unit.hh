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
  /* *= and /= are not included because the * and / operations return a new type,
   * and therefore cannot be assigned to either operand
   */

  double& getValue(){ return mValue; }
  double getValue() const{ return mValue; }

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
 * name collision would be disambiguated using <namespace>::time vs (say) std::time
 */
typedef unit< 1,  0,  0,  0,  0, 0> length;
typedef unit< 0,  1,  0,  0,  0, 0> thyme;//time, renamed to avoid collision
typedef unit< 0,  0,  1,  0,  0, 0> mass;
typedef unit< 0,  0,  0,  1,  0, 0> current;//amps
typedef unit< 0,  0,  0,  0,  1, 0> temperature;//kelvin
typedef unit< 0,  0,  0,  0,  0, 1> light;//candela

typedef unit< 1, -1,  0,  0,  0, 0> speed;
typedef unit< 1, -2,  0,  0,  0, 0> acceleration;
typedef unit< 1, -2,  1,  0,  0, 0> force;//newton
typedef unit< 1, -1,  1,  0,  0, 0> momentum;
typedef unit< 2, -2,  1,  0,  0, 0> energy;//joules
typedef unit< 2, -3,  1,  0,  0, 0> power;//watts

typedef unit< 2, -3,  1, -1,  0, 0> voltage;
typedef unit< 2, -3,  1, -2,  0, 0> resistance;//ohms
typedef unit<-2,  4, -1,  2,  0, 0> capacitance;//farad
typedef unit< 2, -2,  1, -2,  0, 0> inductance;//henrys
typedef unit< 0,  1,  0,  1,  0, 0> charge;//coulomb

typedef unit< 0, -2,  1,  1,  0, 0> magField;//tesla
typedef unit< 1, -3,  1, -1,  0, 0> elecField;

typedef unit< 2, -2,  1,  0, -1, 0> specificHeat;
//OR typedef decltype( energy / temperature ) specificHeat;

#endif


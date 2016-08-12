#ifndef __DATE_TIME_HH__
#define __DATE_TIME_HH__

#include<iostream>
#include<string>

template<unsigned int FACTOR>
class time_unit{
private:
  const unsigned int factor = FACTOR;
  //mValue stores the number of seconds
  long long mValue;
  template<unsigned int UI>
  friend class time_unit;

public:
  time_unit(double val = 1.0):
    mValue(factor * val){
  }
  template<unsigned int UI>
  time_unit(time_unit<UI> tu):
    mValue(tu.mValue){
  }

  time_unit& operator=(double val){
    mValue = factor * val;

    return *this;
  }
  template<unsigned int UI>
  time_unit& operator=(const time_unit<UI>& val){
    mValue = val.mValue;

    return *this;
  }

  time_unit operator+(double val){
    time_unit ret(*this);
    ret += val;

    return ret;
  }
  template<unsigned int UI>
  time_unit operator+(const time_unit<UI>& tu){
    time_unit ret(*this);
    ret += tu;

    return ret;
  }
  time_unit operator-(double val){
    time_unit tu(*this);
    tu -= val;

    return tu;
  }
  template<unsigned int UI>
  time_unit operator-(const time_unit<UI>& tu){
    time_unit ret(*this);
    ret -= tu;

    return ret;
  }

  time_unit& operator+=(double val){
    mValue += factor * val;

    return *this;
  }
  template<unsigned int UI>
  time_unit& operator+=(const time_unit<UI>& tu){
    mValue += tu.mValue;

    return *this;
  }
  time_unit& operator-=(double val){
    mValue -= factor * val;

    return *this;
  }
  template<unsigned int UI>
  time_unit& operator-=(const time_unit<UI>& tu){
    mValue -= tu.mValue;

    return *this;
  }
  time_unit operator*(double val) const{
    time_unit ret(*this);

    ret.mValue *= val;

    return ret;
  }
  time_unit operator/(double val) const{
    time_unit ret(*this);

    ret.mValue /= val;

    return ret;
  }

  bool operator==(double val) const{
    return mValue == (factor * val);
  }
  template<unsigned int UI>
  bool operator==(const time_unit<UI>& tu) const{
    return mValue == tu.mValue;
  }
  bool operator<(double val) const{
    return mValue < (factor * val);
  }
  template<unsigned int UI>
  bool operator<(const time_unit<UI>& tu) const{
    return mValue < tu.mValue;
  }
  bool operator<=(double val) const{
    return (*this) < val || (*this) == val;
  }
  template<unsigned int UI>
  bool operator<=(const time_unit<UI>& tu) const{
    return (*this) < tu || (*this) == tu;
  }
  bool operator>(double val) const{
    return mValue > (factor * val);
  }
  template<unsigned int UI>
  bool operator>(const time_unit<UI>& tu) const{
    return mValue > tu.mValue;
  }
  bool operator>=(double val) const{
    return (*this) > val || (*this) == val;
  }
  template<unsigned int UI>
  bool operator>=(const time_unit<UI>& tu) const{
    return (*this) > tu || (*this) == tu;
  }

  time_unit& operator++(){
    (*this) += 1;

    return *this;
  }
  time_unit operator++(int){
    time_unit tu(*this);

    (*this) += 1;

    return tu;
  }
  time_unit& operator--(){
    (*this) -= 1;

    return *this;
  }
  time_unit operator--(int){
    time_unit tu(*this);

    (*this) -= 1;

    return tu;
  }

  long long getValue(){
    return mValue / factor;
  }

  template<unsigned int UI>
  friend std::ostream& operator<<(std::ostream& os, const time_unit<UI>& tu);
};

template<unsigned int UI>
time_unit<UI> operator*(double val, const time_unit<UI>& tu){
  return tu * val;
}

template<unsigned int UI>
std::ostream& operator<<(std::ostream& os, const time_unit<UI>& tu){
  std::string str;

  if(UI == 1){
    str = "seconds";
  } else if(UI == 60){
    str = "minutes";
  } else if(UI == 3600){
    str = "hours";
  } else if(UI == 86400){
    str = "days";
  } else if(UI == 604800){
    str = "weeks";
  } else if(UI == 2592000){
    str = "months";
  } else if(UI == 31536000){
    str = "years";
  } else {
    str = "units";
  }

  os << (tu.mValue / UI) << " " << str;

  return os;
}

typedef time_unit<1> second;
typedef time_unit<60> minute;
typedef time_unit<3600> hour;
typedef time_unit<86400> day;
typedef time_unit<604800> week;
typedef time_unit<2592000> month;//30 days
typedef time_unit<31536000> year;

class date{
private:
  day mDay;
  year mYear;
  const unsigned int mMonths[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  const std::string monthNames[12] = { "January", "February", "March", "April",
                                       "May", "June", "July", "August",
                                       "September", "October", "November",
                                       "December" };

public:
  date(day d, unsigned int mont, year y):
    mDay(d),
    mYear(y){

    for(unsigned int i = 0; i < mont - 1; ++i){
      mDay += mMonths[i];
    }
  }

  template<unsigned int UI>
  date operator+(const time_unit<UI>& tu){
    date d(*this);

    d += tu;

    return d;
  }
  template<unsigned int UI>
  date operator-(const time_unit<UI>& tu){
    date d(*this);

    d -= tu;

    return d;
  }
  template<unsigned int UI>
  date& operator+=(const time_unit<UI>& tu){
    mDay += tu;
    if(mDay >= 365){
      ++mYear;
      mDay -= 365;
    }

    return *this;
  }
  template<unsigned int UI>
  date& operator-=(const time_unit<UI>& tu){
    mDay -= tu;
    if(mDay <= 0){
      --mYear;
      mDay += 365;
    }

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, date d);
};

std::ostream& operator<<(std::ostream& os, date dayt){
  unsigned int mont = 0;

  while(dayt.mDay.getValue() > dayt.mMonths[mont]){
    dayt.mDay -= dayt.mMonths[mont++];
  }

  os << dayt.mDay.getValue() << " " << dayt.monthNames[mont] << " " << dayt.mYear.getValue();

  return os;
}

class date_time{
private:
  date mDate;
  second mTime;

public:
  date_time(hour h, minute m, second s, date d = date(0, 0, 0)):
    mDate(d),
    mTime(h + m + s){
  }
  date_time(date d, hour h = 0, minute m = 0, second s = 0):
    mDate(d),
    mTime(h + m + s){
  }

  template<unsigned int UI>
  date_time operator+(const time_unit<UI>& tu){
    date_time ret(*this);

    return ret;
  }

  template<unsigned int UI>
  date_time& operator+=(time_unit<UI> tu){
    while(tu.getValue() * UI > 86400){
      day one(1);
      mDate += one;
      tu -= one;
    }

    //whatever's left will be hour/min/sec
    //dump it into the time
    mTime += tu;

    return *this;
  }
  friend std::ostream& operator<<(std::ostream& os, date_time dt);
};

std::ostream& operator<<(std::ostream& os, date_time dt){
  unsigned int h = 0;
  unsigned int m = 0;
  unsigned int s = 0;

  os << dt.mDate << " ";

  while(dt.mTime > 3600){
    ++h;
    dt.mTime -= 3600;
  }
  while(dt.mTime > 60){
    ++m;
    dt.mTime -= 60;
  }
  s = dt.mTime.getValue();

  os << h << ":" << m << ":" << s;

  return os;
}

#endif


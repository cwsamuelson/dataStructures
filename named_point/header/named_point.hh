#ifndef __NAMED_POINT_HH__
#define __NAMED_POINT_HH__

#include <initializer_list>

#include <named_type.hh>
#include <array.hh>

namespace gsw{

template<unsigned long N, typename T = double>
class vec{
public:
  using value_type = T;
  using w_type = named_type<value_type, struct w_struct>;
  using x_type = named_type<value_type, struct x_struct>;
  using y_type = named_type<value_type, struct y_struct>;
  using z_type = named_type<value_type, struct z_struct>;

private:
  static constexpr unsigned long mSize = N;

public:
  using storage_t = array<value_type[mSize]>;

private:
  storage_t mData;

  //template<unsigned long>
  //friend class vec;

public:
  vec() = default;

//!@todo construct and assign from collection of x_type y_type etc?
  vec(const vec& v)
    : mData(v.mData)
  {}

  vec(const storage_t& data)
    : mData{data}
  {}

  vec(const value_type data[mSize])
    : mData(data)
  {}

  vec(std::initializer_list<value_type> il)
  {
    int i = 0;
    for(auto& value : il)
    {
      mData[i++] = value;
    }
  }

  vec&
  operator=(const vec& v)
  {
    for(auto i = 0; i < mSize; ++i)
    {
      mData[i] = v.mData[i];
    }
  }

  value_type&
  operator[](unsigned long idx)
  {
    return mData[idx];
  }

  value_type&
  x()
  {
    return mData[0];
  }

  value_type&
  y()
  {
    return mData[1];
  }

  value_type&
  z()
  {
    return mData[2];
  }

  value_type&
  w()
  {
    return mData[3];
  }

  const value_type&
  x() const
  {
    return mData[0];
  }

  const value_type&
  y() const
  {
    return mData[1];
  }

  const value_type&
  z() const
  {
    return mData[2];
  }

  const value_type&
  w() const
  {
    return mData[3];
  }

  vec&
  operator=(const x_type& x)
  {
    mData[0] = x.get();

    return *this;
  }

  vec&
  operator=(const y_type& y)
  {
    mData[1] = y.get();

    return *this;
  }

  vec&
  operator=(const z_type& z)
  {
    mData[2] = z.get();

    return *this;
  }

  vec&
  operator=(const w_type& w)
  {
    mData[3] = w.get();

    return *this;
  }

  template<unsigned long M>
  vec&
  operator=(const vec<M>& v)
  {
    //where M < N
    for(unsigned int i = 0; i < v.mData.size(); ++i)
    {
      mData[i] = v.mData[i];
    }

    return *this;
  }

  bool
  operator==(const vec& v) const
  {
    if(mData.size() != v.mData.size())
    {
      return false;
    }

    for(int i = 0; i < mData.size(); ++i)
    {
      if(mData[i] != v.mData[i])
        return false;
    }

    return true;
  }

  template<unsigned long M>
  bool
  operator==(storage_t v) const
  {
    return mData == v;
  }

  bool
  operator<(const vec& v) const
  {
    for(auto i = 0; i < mSize; ++i)
    {
      if(mData[i] < v.mData[i])
      {
        return true;
      }
    }
    return false;
  }

  bool
  operator==(const x_type& x) const
  {
    return mData[0] == x.get();
  }

  bool
  operator==(const y_type& y) const
  {
    return mData[1] == y.get();
  }

  bool
  operator==(const z_type& z) const
  {
    return mData[2] == z.get();
  }

  bool
  operator==(const w_type& w) const
  {
    return mData[3] == w.get();
  }
};

using point1 = vec<1>;
using point2 = vec<2>;
using point3 = vec<3>;
using point4 = vec<4>;

}

#endif


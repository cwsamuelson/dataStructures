#ifndef __NAMED_POINT_HH__
#define __NAMED_POINT_HH__

#include<array>

#include<named_type.hh>

namespace gsw{

using coord_t = double;
using w_type = named_type<coord_t, struct w_struct>;
using x_type = named_type<coord_t, struct x_struct>;
using y_type = named_type<coord_t, struct y_struct>;
using z_type = named_type<coord_t, struct z_struct>;

template<unsigned long N>
class vec{
public:
  using val_t = coord_t;

private:
  std::array<val_t, N> mData;

  template<unsigned long>
  friend class vec;

public:
  vec(){
    for( auto& val : mData ){
      val = 0;
    }
  }
//!@todo construct and assign from collection of x_type y_type etc?
  vec( const vec& v )
    : mData( v.mData ){
  }

  vec( const std::array<val_t, N>& data )
    : mData( data ){
  }

  val_t&
  operator[]( unsigned long idx ){
    return mData[idx];
  }

  val_t&
  x(){
    return mData[0];
  }

  val_t&
  y(){
    return mData[1];
  }

  val_t&
  z(){
    return mData[2];
  }

  val_t&
  w(){
    return mData[3];
  }

  const val_t&
  x() const{
    return mData[0];
  }

  const val_t&
  y() const{
    return mData[1];
  }

  const val_t&
  z() const{
    return mData[2];
  }

  const val_t&
  w() const{
    return mData[3];
  }

  vec&
  operator=( const x_type& x ){
    mData[0] = x.get();

    return *this;
  }

  vec&
  operator=( const y_type& y ){
    mData[1] = y.get();

    return *this;
  }

  vec&
  operator=( const z_type& z ){
    mData[2] = z.get();

    return *this;
  }

  vec&
  operator=( const w_type& w ){
    mData[3] = w.get();

    return *this;
  }

  template<unsigned long M>
  vec&
  operator=( const vec<M>& v ){
    //where M < N
    for( unsigned int i = 0; i < v.mData.size(); ++i ){
      mData[i] = v.mData[i];
    }

    return *this;
  }

  bool
  operator==( const vec& v ) const{
    return mData == v.mData;
  }

  //! @todo add tests for this function
  bool
  operator<( const vec& v ) const{
    for( unsigned int i = 0; i < v.mData.size(); ++i ){
      if( mData[i] == v.mData[i] ){
        continue;
      } else {
        return mData[i] < v.mData[i];
      }
    }
  }

  template<unsigned long M>
  bool
  operator==( std::array<val_t, M> v ) const{
    return mData == v;
  }
};

using point1 = vec<1>;
using point2 = vec<2>;
using point3 = vec<3>;
using point4 = vec<4>;

}

#endif

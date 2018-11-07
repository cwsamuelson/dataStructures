#ifndef __NAMED_POINT_HH__
#define __NAMED_POINT_HH__

#include<array>
#include<type_traits>

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
  vec( const x_type& x = 0.0, const y_type& y = 0.0, const z_type& z = 0.0, const w_type& w = 0.0 ){
    if( N >= 1 ){
      mData[0] = x;
      if( N>= 2 ){
        mData[1] = y;
        if( N >= 3 ){
          mData[2] = z;
          if( N >= 4 ){
            mData[3] = w;
          }
        }
      }
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
    return mData.at( 0 );
  }

  val_t&
  y(){
    return mData.at( 1 );
  }

  val_t&
  z(){
    return mData.at( 2 );
  }

  val_t&
  w(){
    return mData.at( 3 );
  }

  template<size_t M>
  val_t&
  get(){
    return mData.at( M );
  }

  const val_t&
  x() const{
    return mData.at( 0 );
  }

  const val_t&
  y() const{
    return mData.at( 1 );
  }

  const val_t&
  z() const{
    return mData.at( 2 );
  }

  const val_t&
  w() const{
    return mData.at( 3 );
  }

  template<size_t M>
  const val_t&
  get() const{
    return mData.at( M );
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
      if( mData[i] != v.mData[i] ){
        return mData[i] < v.mData[i];
      }
    }

    return false;
  }

  bool
  operator==( std::array<val_t, N> v ) const{
    return mData == v;
  }
};

using point1 = vec<1>;
using point2 = vec<2>;
using point3 = vec<3>;
using point4 = vec<4>;

}

#endif

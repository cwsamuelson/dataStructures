#ifndef __ARRAY_HH__
#define __ARRAY_HH__

#include<functional>
#include<vector>

#include<normal_iterator.hh>

//see mask_array and indirect array for indexing ideas
//  one allows data[data > 5] = -1 kinda syntax,
//  the other data[data2] = -2 syntax
//  each modifies a set of values
//  the first says values at indexes greater than 5 are set to -1
//  the other says values at indexes stored in data2 are set to -2

template<class T>
class array;

template<class T>
struct splice_index{
  typedef std::function<bool( T, T )> opsig;

  opsig mOp;
  unsigned int mIdx;

  splice_index( opsig op, unsigned int idx ):
    mOp( op ),
    mIdx( idx ){
  }
};

template<class T>
struct splice_helper;

template<class T, unsigned int N>
struct splice_helper<T[N]>{
  array<T[N]>& mArr;
  std::vector<unsigned int> mIdxs;

  splice_helper( array<T[N]>& arr ):
    mArr( arr ){
  }

  array<T[N]>& operator=( T t ){
    for( auto it : mIdxs ){
      mArr[it] = t;
    }

    return mArr;
  }
};

template<class T, unsigned int N>
class array<T[N]>{
public:
  typedef T value_type;
  typedef unsigned int index_t;
  static const index_t mSize = N;
  static const unsigned int ptrdiff = sizeof( value_type );
  typedef splice_index<value_type> splicer;
  typedef splice_helper<value_type[N]> helper;
  typedef normal_iterator<value_type, array> iterator;

private:
  value_type mArr[mSize];

public:
  index_t size(){
    return mSize;
  }

  value_type& operator[]( index_t idx ){
    return mArr[idx];
  }
  helper operator[]( const splicer& si ){
    helper h( *this );

    for( unsigned int i = 0; i < mSize; ++i ){
      if( si.mOp( i, si.mIdx ) ){
        h.mIdxs.push_back( i );
      }
    }

    return h;
  }
  //TODO:genericize to not only take arrays
  //TODO:provide cbegin/cend to allow this argument to be const
  template<unsigned int M>
  helper operator[]( array<unsigned int[M]>& a ){
    helper h(*this);

    for( auto it = a.begin(); it != a.end(); ++it ){
      h.mIdxs.push_back( *it );
    }

    return h;
  }

  splicer operator>( index_t idx ){
    return splicer( std::greater<value_type>(), idx );
  }
  splicer operator>=( index_t idx ){
    return splicer( std::greater_equal<value_type>(), idx );
  }
  splicer operator<( index_t idx ){
    return splicer( std::less<value_type>(), idx );
  }
  splicer operator<=( index_t idx ){
    return splicer( std::less_equal<value_type>(), idx );
  }

  iterator begin(){
    return Iterator( 0 );
  }
  iterator end(){
    return Iterator( mSize );
  }
  iterator Iterator( index_t idx ){
    return iterator( &mArr[idx] );
  }
};

template<typename OSTREAM, class T, unsigned int N>
OSTREAM& operator<<( OSTREAM& os, const array<T[N]>& arr ){
  for( unsigned int i = 0; i < N; ++i ){
    os << arr[i];
  }

  return os;
}

#endif


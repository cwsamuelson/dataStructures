#ifndef __REGION_TREE_HH__
#define __REGION_TREE_HH__

#include<tuple>
#include<vector>
#include<algorithm>

namespace gsw{

namespace detail{

template<size_t DIM, typename ...ARGS>
class vec_helper{
public:
  using type = typename vec_helper<DIM - 1, double, ARGS...>::type;
};

template<typename ...ARGS>
class vec_helper<0, ARGS...>{
public:
  using type = std::tuple<ARGS...>;
};

}// detail

template<size_t DIM>
using vec = typename detail::vec_helper<DIM>::type;

template<typename T, size_t DIM>
class region_tree{
public:
  using value_type = T;
  using dimensions = std::tuple<vec<DIM>, vec<DIM> >;

private:
  static constexpr div_count = 2 << DIM;
  std::vector<region_tree> mDivisions;
  std::vector<std::tuple<value_type, vec<DIM> > > mObjects;
  dimensions mDimensions;
  unsigned long mMaxObjects;

  template<size_t N, typename T, typename ...ARGS>
  void dim_helper( dimensions& dims, const T& t, ARGS... args ){
    auto& ref1 = std::get<N>( std::get<0>( dims ) );
    auto& ref2 = std::get<N>( std::get<1>( dims ) );

    if( t ){
      ref1 = ( ref1 + ref2 ) / 2;
    } else {
      ref2 = ( ref1 + ref2 ) / 2;
    }

    dim_helper<N - 1>( dims, args... );
  }

  template<size_t N, typename ...ARGS>
  void recur_helper( ARGS... args ){
    for( unsigned int i = 0; i < 2; ++i ){
      recur_helper<N - 1>( i, args... );
    }
  }

  template<typename ...ARGS>
  void recur_helper<0>( ARGS... args ){
    auto dims = mDimensions;
    dim_helper<DIM>( dims, args... );

    mDivisions.emplace_back( dims, mMaxObjects );
  }

  template<size_t N>
  void split_helper(){
    
  }

  void split(){
    // splits new segments
    recur_helper<DIM>();

    for( auto obj : mObjects ){
      
    }
  }

public:
  region_tree( const vec<DIM>& dim1, const vec<DIM>& dim2, unsigned long max = 2 ):
    mDimensions( {std::min( std::get<0>( dim1 ), std::get<0>( dim2 ) ),
                  std::min( std::get<1>( dim1 ), std::get<1>( dim2 ) )},
                 {std::max( std::get<0>( dim1 ), std::get<0>( dim2 ) ),
                  std::max( std::get<1>( dim1 ), std::get<1>( dim2 ) )} ),
    mMaxObjects( max ){
  }

  void insert( const value_type& vt, const vec<DIM>& v ){
    // if we're already split, insert appropriately

    // if not split, insert normally and split if necessary
    mObjects.push_back( vt );

    if( mObjects.size() > mMaxObjects ){
      split();
    }
  }
};

template<typename T>
using quad_tree = region_tree<T, 2>;
template<typename T>
using oct_tree = region_tree<T, 3>;
template<typename T>
using octree = region_tree<T, 3>;

}

#endif


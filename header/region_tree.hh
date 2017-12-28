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

template<typename T>
class quad_tree{
public:
  using value_type = T;
  using vector = std::tuple<double, double>;

private:
  std::vector<std::tuple<value_type, vector> > mObjects;
  std::vector<quad_tree> mSubRegions;
  std::tuple<vector, vector> mBounds;
  const unsigned int mMaxObjects;

  void sub_insert( const value_type& obj, vector v ){
    int idx;
    auto min_bound = std::get<0>( mBounds );
    auto max_bound = std::get<1>( mBounds );
    auto min_x = std::get<0>( min_bound );
    auto min_y = std::get<1>( min_bound );
    auto max_x = std::get<0>( max_bound );
    auto max_y = std::get<1>( max_bound );
    auto split_x = ( min_x + max_x ) / 2;
    auto split_y = ( min_y + max_y ) / 2;
    auto x = std::get<0>( v );
    auto y = std::get<1>( v );

    if( x < split_x ){
      if( y < split_y ){
        idx = 0;
      } else {
        idx = 1;
      }
    } else {
      if( y < split_y ){
        idx = 2;
      } else {
        idx = 3;
      }
    }

    mSubRegions[idx].insert( obj, v );
  }

  void split(){
    auto min_bound = std::get<0>( mBounds );
    auto max_bound = std::get<1>( mBounds );
    auto min_x = std::get<0>( min_bound );
    auto min_y = std::get<1>( min_bound );
    auto max_x = std::get<0>( max_bound );
    auto max_y = std::get<1>( max_bound );
    auto split_x = ( min_x + max_x ) / 2;
    auto split_y = ( min_y + max_y ) / 2;

    mSubRegions.emplace_back( vector{min_x, min_y}, vector{split_x, split_y}, mMaxObjects );
    mSubRegions.emplace_back( vector{min_x, split_y}, vector{split_x, max_y}, mMaxObjects );
    mSubRegions.emplace_back( vector{split_x, min_y}, vector{max_x, split_y}, mMaxObjects );
    mSubRegions.emplace_back( vector{split_x, split_y}, vector{max_x, max_y}, mMaxObjects );

    for( auto obj : mObjects ){
      sub_insert( std::get<0>( obj ), std::get<1>( obj ) );
    }

    mObjects.clear();
  }

  void get_groups( std::vector<std::vector<value_type> >& groups ){
    std::vector<value_type> list;

    for( auto data : mObjects ){
      list.push_back( std::get<0>( data ) );
    }

    if( !list.empty() ){
      groups.push_back( list );
    }

    for( auto region : mSubRegions ){
      region.get_groups( groups );
    }
  }

public:
  quad_tree( vector v1, vector v2, int max = 2 ):
    mBounds( {std::min( std::get<0>( v1 ), std::get<0>( v2 ) ),
              std::min( std::get<1>( v1 ), std::get<1>( v2 ) )},
             {std::max( std::get<0>( v1 ), std::get<0>( v2 ) ),
              std::max( std::get<1>( v1 ), std::get<1>( v2 ) )} ),
    mMaxObjects( max ){
  }

  void insert( const value_type& obj, vector v ){
    auto min_bound = std::get<0>( mBounds );
    auto max_bound = std::get<1>( mBounds );
    auto min_x = std::get<0>( min_bound );
    auto min_y = std::get<1>( min_bound );
    auto max_x = std::get<0>( max_bound );
    auto max_y = std::get<1>( max_bound );
    auto x = std::get<0>( v );
    auto y = std::get<1>( v );

    // validate bounds
    if( ( x < min_x ) || ( y < min_y ) ||
        ( x > max_x ) || ( y > max_y ) ){
      return;//! @todo should throw?
    }

    if( !mSubRegions.empty() ){
      sub_insert( obj, v );
    } else {
      mObjects.emplace_back( obj, v );

      if( mObjects.size() > mMaxObjects ){
        split();
      }
    }
  }

  //! @todo should be sets, not vectors?
  std::vector<std::vector<value_type> > get_groups(){
    std::vector<std::vector<value_type> > ret;

    get_groups( ret );

    return ret;
  }
};

/*
template<typename T, size_t DIM>
class region_tree{
public:
  using value_type = T;
  using dimensions = std::tuple<vec<DIM>, vec<DIM> >;

private:
  static constexpr int div_count = 2 << DIM;
  std::vector<region_tree> mDivisions;
  std::vector<std::tuple<value_type, vec<DIM> > > mObjects;
  dimensions mDimensions;
  unsigned long mMaxObjects;

  template<size_t N>
  void split_helper( dimensions& dims ){
    for( unsigned int i = 0; i < 2; ++i ){
      auto& ref1 = std::get<N - 1>( std::get<0>( dims ) );
      auto& ref2 = std::get<N - 1>( std::get<1>( dims ) );

      if( i == 0 ){
        ref2 = ( ref1 + ref2 ) / 2;
      } else {
        ref1 = ( ref1 + ref2 ) / 2;
      }

      split_helper<N - 1>( dims );
    }
  }

  void insert_helper( const vec<DIM>& pos, const value_type& obj ){
    int i = 0;

    while( i++ < mDivisions.size() && !mDivisions[i].insert( obj, pos ) ){
      ;
    }
  }

  void split(){
    auto dims = mDimensions;
    // split new segments
    split_helper<DIM>( dims );

    // insert current objects into new groupings
    for( auto obj : mObjects ){
      insert_helper( std::get<1>( obj ), std::get<0>( obj ) );
    }

    mObjects.clear();
  }

  template<size_t N>
  bool bounds_helper( const vec<DIM>& v ){
    return ( std::get<N>( v ) < std::get<N>( std::get<1>( mDimensions ) ) ) &&
           ( std::get<N>( v ) > std::get<N>( std::get<0>( mDimensions ) ) );
  }

  template<size_t N>
  bool bounds_check( const vec<DIM>& v ){
    return bounds_check<N - 1>( v ) && bounds_helper<N>( v );
  }

  template<>
  bool bounds_check<0>( const vec<DIM>& v ){
    return bounds_helper( v );
  }

  template<>
  void split_helper<0>( dimensions& dims ){
    mDivisions.emplace_back( dims, mMaxObjects );
  }

public:
  //! @todo mdimensions initialization needs to be refactored for higher dimensions
  region_tree( const vec<DIM>& dim1, const vec<DIM>& dim2, unsigned long max = 2 ):
    mDimensions( {std::min( std::get<0>( dim1 ), std::get<0>( dim2 ) ),
                  std::min( std::get<1>( dim1 ), std::get<1>( dim2 ) )},
                 {std::max( std::get<0>( dim1 ), std::get<0>( dim2 ) ),
                  std::max( std::get<1>( dim1 ), std::get<1>( dim2 ) )} ),
    mMaxObjects( max ){
  }

  bool insert( const value_type& vt, const vec<DIM>& v ){
    // return false when this object doesn't belong in our bounds
    if( !bounds_check<DIM>( v ) ){
      return false;
    }

    if( mDivisions.size() > 0 ){
      // if we're already split, insert appropriately
      insert_helper( v, vt );
    } else {
      // if not split, insert normally and split if necessary
      mObjects.push_back( vt );
    }

    if( mObjects.size() > mMaxObjects ){
      split();
    }

    return true;
  }
};

template<typename T>
using quad_tree = region_tree<T, 2>;
template<typename T>
using oct_tree = region_tree<T, 3>;
template<typename T>
using octree = region_tree<T, 3>;
*/

}

#endif


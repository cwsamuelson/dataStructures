#ifndef __REGION_TREE_HH__
#define __REGION_TREE_HH__

#include<tuple>
#include<array>
#include<set>
#include<algorithm>

namespace gsw{

template<typename T, size_t DIM>
class region_tree{
public:
  using value_type = T;
  using vector = std::array<double, DIM>;

private:
  std::set<std::tuple<value_type, vector> > mObjects;
  std::set<region_tree> mSubRegions;
  std::tuple<vector, vector> mBounds;
  const unsigned int mMaxObjects;

  bool check_bounds( vector position ){
    for( unsigned int i = 0; i < DIM; ++i ){
      if( !( ( position[i] >  std::get<0>( mBounds )[i] ) &&
             ( position[i] <= std::get<1>( mBounds )[i] ) ) ){
        return false;
      }
    }

    return true;
  }

  void sub_insert( const value_type& vt, vector position ){
    for( auto region : mSubRegions ){
      if( region.check_bounds( position ) ){
        region.insert( vt, position );
        break;
      }
    }
  }

  void split_helper( vector min, vector max, const vector& split_bounds, int depth = DIM ){
    if( depth == 0 ){
      mSubRegions.emplace( min, max, mMaxObjects );
      return;
    }

    split_helper( min, max, split_bounds, depth - 1 );

    min[depth] = split_bounds[depth];
    max[depth] = std::get<1>( mBounds )[depth];

    split_helper( min, max, split_bounds, depth - 1 );
  }

  void split(){
    vector split_bounds;

    for( unsigned int i = 0; i < DIM; ++i ){
      split_bounds[i] = ( std::get<0>( mBounds )[i] + std::get<1>( mBounds )[i] ) / 2;
    }

    split_helper( std::get<0>( mBounds ), std::get<1>( mBounds ), split_bounds );

    for( auto obj : mObjects ){
      sub_insert( std::get<0>( obj ), std::get<1>( obj ) );
    }

    mObjects.clear();
  }

  void get_groups( std::set<std::set<value_type> >& groups ){
    if( !mObjects.empty() ){
      std::set<value_type> sub_set;

      for( auto object : mObjects ){
        sub_set.emplace( std::get<0>( object ) );
      }

      groups.emplace( std::set<value_type>( sub_set.begin(), sub_set.end() ) );
    }

    for( auto region : mSubRegions ){
      region.get_groups( groups );
    }
  }

public:
  region_tree( vector v1, vector v2, int max = 2 ):
    mBounds( {v1, v2} ),
    mMaxObjects( max ){
  }

  void insert( const value_type& obj, vector location ){
    // validate bounds
    if( check_bounds( location ) ){
      return;//! @todo should throw?
    }

    if( !mSubRegions.empty() ){
      sub_insert( obj, location );
    } else {
      mObjects.emplace( obj, location );

      if( mObjects.size() > mMaxObjects ){
        split();
      }
    }
  }

  std::set<std::set<value_type> > get_groups(){
    std::set<std::set<value_type> > ret;

    get_groups( ret );

    return ret;
  }

  bool operator<( const region_tree& rt ) const{
    return mBounds < rt.mBounds;
  }
};

template<typename T>
using quad_tree = region_tree<T, 2>;
template<typename T>
using oct_tree = region_tree<T, 3>;
template<typename T>
using octree = oct_tree<T>;

}

#endif


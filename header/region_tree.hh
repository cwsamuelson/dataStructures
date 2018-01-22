#ifndef __REGION_TREE_HH__
#define __REGION_TREE_HH__

#include<tuple>
#include<set>
#include<algorithm>

namespace gsw{

namespace detail{

template<size_t DIM, typename T, typename ...ARGS>
class vec_helper{
public:
  using value_type = T;
  using type = typename vec_helper<DIM - 1, value_type, ARGS...>::type;
};

template<typename ...ARGS>
class vec_helper<0, ARGS...>{
public:
  using type = std::tuple<ARGS...>;
};

}// detail

template<size_t DIM>
using vec = typename detail::vec_helper<DIM>::type;

namespace detail{

template<size_t DIM, size_t MAX = DIM + 1>
class bounds_helper : public bounds_helper<DIM - 1, MAX>{
public:
  using vector = vec<MAX, double>;
  using base = bounds_helper<DIM - 1, MAX>;

private:
  std::tuple<double, double> mBounds;

protected:
  void split_helper( vector& v ){
    auto min_bound = std::get<0>( mBounds );
    auto max_bound = std::get<1>( mBounds );
    auto split_bound = ( min_bound + max_bound ) / 2;

    std::get<DIM>( v ) = split_bound;

    base::split_helper( v );
  }

public:
  bounds_helper( vector v1, vector v2 ):
    base( v1, v2 ),
    mBounds( {std::min( std::get<DIM>( v1 ), std::get<DIM>( v2 ) ),
              std::max( std::get<DIM>( v1 ), std::get<DIM>( v2 ) )} ){
  }

  bool check( vector v ){
    return ( std::get<DIM>( v ) >  std::get<0>( mBounds ) ) &&
           ( std::get<DIM>( v ) <= std::get<1>( mBounds ) ) &&
           base::check( v );
  }

  vector split(){
    vector v;

    split_helper( v );

    return v;
  }

  bool operator<( const bounds_helper& rt ) const{
    auto l_min = std::get<0>( mBounds );
    auto l_max = std::get<1>( mBounds );
    auto r_min = std::get<0>( rt.mBounds );
    auto r_max = std::get<1>( rt.mBounds );

    if( ( l_min < r_min ) ||
        ( ( l_min == r_min ) &&
          ( l_max <  r_max ) ) ||
        base::operator<( rt::base( rt ) ) ){
      return true;
    } else {
      return false;
    }
  }
};

template<size_t MAX>
class bounds_helper<0, MAX>{
private:
  using vector = vec<MAX, double>;

private:
  std::tuple<double, double> mBounds;
  constexpr size_t DIM = 0;

protected:
  void split_helper( vector& v ){
    auto min_bound = std::get<0>( mBounds );
    auto max_bound = std::get<1>( mBounds );
    auto split_bound = ( min_bound + max_bound ) / 2;

    std::get<DIM>( v ) = split_bound;
  }

public:
  bounds_helper( vector v1, vector v2 ):
    mBounds( {std::min( std::get<DIM>( v1 ), std::get<DIM>( v2 ) ),
              std::max( std::get<DIM>( v1 ), std::get<DIM>( v2 ) )} ){
  }

  bool check( vector v ){
    return ( std::get<DIM>( v ) >  std::get<0>( mBounds ) ) &&
           ( std::get<DIM>( v ) <= std::get<1>( mBounds ) );
  }

  bool operator<( const bounds_helper& rt ) const{
    auto l_min = std::get<0>( mBounds );
    auto l_max = std::get<1>( mBounds );
    auto r_min = std::get<0>( rt.mBounds );
    auto r_max = std::get<1>( rt.mBounds );

    if( ( l_min < r_min ) ||
        ( ( l_min == r_min ) &&
          ( l_max <  r_max ) ) ){
      return true;
    } else {
      return false;
    }
  }
};

}

template<typename T, size_t DIM>
class region_tree{
public:
  using value_type = T;
  using vector = vec<DIM, double>;

private:
  std::set<std::tuple<value_type, vector> > mObjects;
  std::set<region_tree> mSubRegions;
  detail::bounds_helper<DIM> mBounds;
  const unsigned int mMaxObjects;

  void sub_insert( const value_type& obj, vector v ){
    for( auto region : mSubRegions ){
      if( region.mBounds.check( v ) ){
        region.insert( obj, v );
        break;
      }
    }
  }

  void split(){
    auto split_point = mBounds.split();

    helper<DIM - 1> h( std::get<0>( mBounds ),
                       split_point,
                       std::get<1>( mBounds ) );

    h.use_values( []( vector v1, vector v2 ){
      mSubRegions.emplace( v1, v2, mMaxObjects );
    } );

    for( auto obj : mObjects ){
      sub_insert( std::get<0>( obj ), std::get<1>( obj ) );
    }

    mObjects.clear();
  }

  void get_groups( std::set<std::set<value_type> >& groups ){
    std::set<value_type> list;

    for( auto data : mObjects ){
      list.insert( std::get<0>( data ) );
    }

    if( !list.empty() ){
      groups.insert( list );
    }

    for( auto region : mSubRegions ){
      region.get_groups( groups );
    }
  }

  void sub_insert( const value_type& obj, vector v ){
  }

public:
  region_tree( vector v1, vector v2, int max = 2 ):
    mBounds( {v1, v2} ),
    mMaxObjects( max ){
  }

  void insert( const value_type& obj, vector v ){
    // validate bounds
    if( mBounds.check( v ) ){
      return;//! @todo should throw?
    }

    if( !mSubRegions.empty() ){
      sub_insert( obj, v );
    } else {
      mObjects.emplace( obj, v );

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

namespace detail{

template<typename T>
class swapper{
public:
  using value_type = T;

private:
  value_type a;
  value_type b;
  bool swapped = false;

public:
  swapper( const value_type& x, const value_type& y ):
    a( x ),
    b( y ){
  }

  operator value_type(){
    return swapped ? a : b;
  }

  void swap(){
    swapped = !swapped;
  }
};

template<size_t DIM, size_t MAX = DIM + 1>
class helper : public helper<DIM - 1, MAX>{
public:
  using base = helper<DIM - 1, MAX>;
  using vector = vec<double, MAX>;

private:
  std::tuple<swapper<double>, swapper<double> > swaps;

public:
  helper( vector a, vector b, vector c ):
    base( a, b, c ),
    swaps( {{std::get<DIM>( a ), std::get<DIM>( b )},
            {std::get<DIM>( b ), std::get<DIM>( c )}} ){
  }

  void use_values( vector v1, vector v2, std::function<void( vector, vector )> fn ){
    for( int i = 0; i < 2; ++i ){
      std::get<DIM>( v1 ) = std::get<0>( swaps );
      std::get<DIM>( v2 ) = std::get<1>( swaps );

      base::use_values( v1, v2, fn );

      std::get<0>( swaps ).swap();
      std::get<1>( swaps ).swap();
    }
  }
};

template<size_t MAX>
class helper<0, MAX>{
private:
  std::tuple<swapper<double>, swapper<double> > swaps;

public:
  helper( vector a, vector b, vector c ):
    swaps( {{std::get<DIM>( a ), std::get<DIM>( b )},
            {std::get<DIM>( b ), std::get<DIM>( c )}} ){
  }

  void use_values( vector v1, vector v2, std::function<void( vector, vector )> fn ){
    for( int i = 0; i < 2; ++i ){
      std::get<DIM>( v1 ) = std::get<0>( swaps );
      std::get<DIM>( v2 ) = std::get<1>( swaps );

      fn( v1, v2 );

      std::get<0>( swaps ).swap();
      std::get<1>( swaps ).swap();
    }
  }
};

}

template<typename T>
using quad_tree = region_tree<T, 2>;
template<typename T>
using oct_tree = region_tree<T, 3>;
template<typename T>
using octree = oct_tree<T>;

}

#endif


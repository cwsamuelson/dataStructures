#ifndef __SKIP_LIST_HH__
#define __SKIP_LIST_HH__

#include<tuple>

#include<normal_iterator.hh>

namespace gsw{

template<typename KEY, typename VALUE>
class skip_list{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using storage_type = std::tuple<key_type, value_type>;
  using iterator = normal_iterator<storage_type, skip_list>;

private:

public:
  bool
  empty() const{
    return true;
  }

  value_type&
  operator[]( const key_type& ){
  }

  iterator
  begin(){
  }

  iterator
  end(){
  }
};

}

#endif


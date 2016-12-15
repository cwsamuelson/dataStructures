#ifndef __MENU_HH__
#define __MENU_HH__

#include<vector>
#include<map>
#include<string>
#include<functional>
#include<tuple>

typedef std::function<void()> optionCallback;

template<typename selector>
class menu{
private:
  std::map<selector, std::tuple<std::string, menu, optionCallback> > mOptions;

public:
  void addOption( const selector& selection, const std::string& optText, const menu& nextMenu, optionCallback callback = optionCallback( [](){} ) ){
    mOptions[selection] = std::make_tuple( optText, nextMenu, callback );
  }
  menu& select( const selector& selection ){
    auto it = mOptions.at( selection );

    // call the callback
    std::get<2>( it )();

    // return next menu
    return std::get<1>( it );
  }
  template<typename OSTREAM>
  OSTREAM& print( OSTREAM& os ){
    for( auto it : mOptions ){
      os << std::get<0>( it ) << '\t' << std::get<0>( std::get<1>( it ) ) << '\n';
    }

    return os;
  }
};

#endif


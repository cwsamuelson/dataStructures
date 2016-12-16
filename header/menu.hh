#ifndef __MENU_HH__
#define __MENU_HH__

#include<map>
#include<string>
#include<functional>
#include<tuple>
#include<memory>

typedef std::function<void()> optionCallback;

template<typename SELECTOR>
class menu{
public:
  typedef std::shared_ptr<menu> menuPtr;

private:
  std::map<SELECTOR, std::tuple<std::string, menuPtr, optionCallback> > mOptions;

public:
  menu() = default;
  menu( const menu& other ):
    mOptions( other.mOptions ){
  }
  menu( const menu* other ):
    mOptions( other->mOptions ){
  }
//TODO: add ctor for menu&&

  void addOption( const SELECTOR& selection, const std::string& optText, menuPtr nextMenu, optionCallback callback = optionCallback( [](){} ) ){
    mOptions[selection] = std::make_tuple( optText, nextMenu, callback );
  }
  menuPtr select( const SELECTOR& selection ){
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


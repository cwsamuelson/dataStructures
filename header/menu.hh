#ifndef __MENU_HH__
#define __MENU_HH__

/*!
 * @example test-menu.cc
 */

#include<map>
#include<string>
#include<functional>
#include<tuple>
#include<memory>
#include<utility>

namespace gsw{

template<typename SELECTOR>
class menu{
public:
  typedef std::shared_ptr<menu> menuPtr;
  typedef std::function<void()> optionCallback;

private:
  std::map<SELECTOR, std::tuple<std::string, menuPtr, optionCallback> > mOptions;

public:
  /*! Default ctor
   */
  menu() = default;

  /* Copy/Move ctor
   *
   * @param other  Parameter containing menu options to copy/move
   *
   * Copies/moves menu options from other parameter
   */
  template<typename U>
  menu( U&& other ):
    mOptions( std::forward<decltype( mOptions )>( other.mOptions ) ){
  }

  /*! Adds a new menu option to menu
   *
   * @param selection  What option number should be used for this option
   *
   * @param optText  What text should be provided with this option
   *
   * @param nextMenu  Which menu should be presented when this option is selected
   *
   * @param callback  What function should be called when this option is chosen
   *
   * Describe a new option including number, text, next menu, and action to
   * take upon selection
   */
  void addOption( const SELECTOR& selection, const std::string& optText,
                  menuPtr nextMenu, optionCallback callback = optionCallback( [](){} ) ){
    mOptions[selection] = std::make_tuple( optText, nextMenu, callback );
  }

  /*! Select a menu option
   *
   * @param selection  Chosen option
   *
   * Retrieve the selection, call its callback, and return next menu
   */
  menuPtr select( const SELECTOR& selection ){
    auto it = mOptions.at( selection );

    // call the callback
    std::get<2>( it )();

    // return next menu
    return std::get<1>( it );
  }

  /*! Provide menu options to given stream
   *
   * @param os  Output stream to provide menu information to
   */
  template<typename OSTREAM>
  OSTREAM& print( OSTREAM& os ){
    for( auto it : mOptions ){
      os << std::get<0>( it ) << '\t' << std::get<0>( std::get<1>( it ) ) << '\n';
    }

    return os;
  }
};

}

#endif


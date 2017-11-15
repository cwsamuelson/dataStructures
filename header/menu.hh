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

/*! menu utility class.
 *
 * @tparam SELECTOR Selection type.  The type used to distinguish between menu options.
 *
 * Each menu object contains a list of menu 'nodes'.  These nodes, once
 * connected, can be retrieved using the SELECTOR type and the select method,
 * which will return the associated menu node.
 *
 * @code{.cpp}
 * auto node1 = make_shared<menu<int> >();
 * auto node2 = make_shared<menu<int> >();
 * auto node3 = make_shared<menu<int> >();
 *
 * node1->addOption( 0, "Menu selection 0, from node 1", node1 );
 * node1->addOption( 1, "Menu selection 1, from node 1", node2 );
 * node1->addOption( 2, "Menu selection 2, from node 1", node3 );
 *
 * node2->addOption( 0, "Menu selection 0, from node 2", node1 );
 * node2->addOption( 1, "Menu selection 1, from node 2", node2 );
 * node2->addOption( 2, "Menu selection 2, from node 2", node3 );
 *
 * node3->addOption( 0, "Menu selection 0, from node 3", node1 );
 * node3->addOption( 1, "Menu selection 1, from node 3", node2 );
 * node3->addOption( 2, "Menu selection 2, from node 3", node3 );
 *
 * auto current_node = node1;
 *
 * while( true ){
 *   current_node->select( getUserInput() );
 * }
 * @endcode
 */
template<typename SELECTOR>
class menu{
public:
  /*! selector type, used to differentiate and retrieve menu options from this node
   */
  using selector = SELECTOR;

  /*! pointer to menu type
   */
  using pointer = std::shared_ptr<menu>;

  /*! callback used to inform user of changed state
   */
  using optionCallback = std::function<bool(selector)>;

  /*!
   */
  using menu_item = std::tuple<std::string, pointer, optionCallback>;

private:
  std::map<selector, menu_item > mSubMenus;

public:
  /*! Default ctor
   */
  menu() = default;

  /*! Copy/Move ctor
   *
   * @param other  Parameter containing menu options to copy/move
   *
   * Copies/moves menu options from other
   */
  template<typename U>
  menu( U&& other ):
    mSubMenus( std::forward<decltype( mSubMenus )>( other.mSubMenus ) ){
  }

  /*! Copy/move assignment
   *
   * @param other  Parameter containing menu options to copy/move
   *
   * Copies/moves menu options from other
   */
  template<typename U>
  menu& operator=( U&& other ){
    mSubMenus = std::forward<decltype( mSubMenus )>( other.mSubMenus );
  }

  /*!
   *
   * @param sel
   *
   * @return
   */
  menu_item& operator[]( const selector& sel ){
    return mSubMenus[sel];
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
  void addOption( const selector& selection, const std::string& optText,
                  pointer nextMenu, optionCallback callback = optionCallback( []( selector ){ return true; } ) ){
    mSubMenus[selection] = std::make_tuple( optText, nextMenu, callback );
  }

  /*! Select a menu option
   *
   * @param selection  Chosen option
   *
   * @todo currently returns a new shared_ptr to this.  this enables double freeing.
   *
   * Retrieve the selection, call its callback, and return next menu
   */
  pointer select( const selector& selection ){
    auto it = mSubMenus.at( selection );

    // call the callback; return next menu
    if( std::get<2>( it )( selection ) ){
      return std::get<1>( it );
    } else {
       return pointer( this );
    }
  }

  /*! Provide menu options to given stream
   *
   * @param os  Output stream to provide menu information to
   */
  template<typename OSTREAM>
  OSTREAM& print( OSTREAM& os ){
    for( auto it : mSubMenus ){
      os << std::get<0>( it ) << '\t' << std::get<0>( std::get<1>( it ) ) << '\n';
    }

    return os;
  }

  /*! Provide menu options to given stream
   *
   * @param os  Output stream to provide menu information to
   *
   * @param m  Menu printed options are to come from
   */
  template<typename OSTREAM>
  friend
  OSTREAM& operator<<( OSTREAM& os, menu m ){
    m.print( os );

    return os;
  }
};

}

#endif


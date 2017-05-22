#ifndef __RANGE_HH__
#define __RANGE_HH__

#include<functional>

template<class>
class range;

/*! Range filtering iterator
 *
 * @tparam CONTAINER  Type of container being iterated
 *
 * Provides a normal iterator interface over a container, however the data
 * retrieved from said container is not the raw data stored; instead the data
 * returned by this iterator is filtered using a provided filter callback,
 * as well as modified by a provided modification callback.  This allows for a
 * customized view into a storage container.
 */
template<class CONTAINER>
class range_iterator{
public:
  typedef CONTAINER container;
  typedef typename container::value_type value_type;
  typedef typename container::value_type& reference;
  typedef typename container::value_type* pointer;
  typedef const value_type const_value;
  typedef typename container::iterator iterator;

private:
  const range<container>* mRange;
  iterator mIterator;

public:
  range_iterator( const range<container>* rang, iterator iter ):
    mRange( rang ),
    mIterator( iter ){
  }
  range_iterator( const range_iterator& iter ):
    mRange( iter.mRange ),
    mIterator( iter.mIterator ){
  }

  bool operator==( const range_iterator& other ) const{
    return mIterator == other.mIterator;
  }
  bool operator==( const iterator& other ) const{
    return mIterator == other;
  }
  bool operator!=( const range_iterator& other ) const{
    return !( ( *this ) == other );
  }
  bool operator!=( const iterator& other ) const{
    return !( mIterator == other );
  }

  value_type operator*() const{
    return mRange->mModifier( *mIterator );
  }
  pointer operator->() const{
    return mIterator.operator->();
  }
  
  range_iterator& operator++(){
    while( ( !mRange->mFilter( *++mIterator ) ) && ( mRange->end() != mIterator ) ){
      ;
    }
    return *this;
  }
  range_iterator operator++( int ){
    range_iterator ret( *this );
    ++( *this );
    return ret;
  }
  
  range_iterator& operator--(){
    while( !mRange->mFilter( *--mIterator ) && ( mRange->begin() != mIterator ) ){
      ;
    }
    return *this;
  }
  range_iterator operator--( int ){
    range_iterator ret( *this );
    --( *this );
    return ret;
  }
};

/*! Range filter class
 *
 * @tparam CONTAINER  Type of container being filtered
 *
 * Range class takes a container, or iterators to its beginning and ending
 * and will provide custom iterators to said container.  These custom iterators
 * allow custom data filtering and data modification based on provided callbacks.
 */
template<class CONTAINER>
class range{
public:
  typedef CONTAINER container;
  typedef typename container::value_type value_type;
  typedef typename container::pointer pointer;
  typedef typename container::reference reference;
  typedef typename container::iterator contIter;
  typedef std::function<bool( const reference )> filter;
  typedef std::function<value_type( const reference )> modifier;
  typedef range_iterator<container> iterator;

private:
  contIter mBegin;
  contIter mEnd;
  filter mFilter;
  modifier mModifier;

  friend iterator;

public:
  /*! Stores beginning and ending iterators, filtering callback, and modification callback
   *
   * @param begin  Iterator to beginning iterator of target container
   *
   * @param end  Iterator to end iterator of target container
   *
   * @param filFN  Filter callback
   *
   * @param modFN  Modification callback
   *
   * Takes iterator, filtering, and modification information that will be
   * needed when continuing to use range.
   */
  range( contIter begin, contIter end,
         filter filFN = []( const reference ){ return true; },
         modifier modFN = []( const reference t ){ return t; } ):
    mBegin( begin ),
    mEnd( end ),
    mFilter( filFN ),
    mModifier( modFN ){
  }

  /*! Takes a container, and stores its beginning and ending iterators, and filtering callback, and modification callback
   *
   * @param cont  Reference to container that begin and end iterators will pull from
   *
   * @param filFN  Filter callback
   *
   * @param modFN  Modification callback
   *
   * Takes container, filtering, and modification information that will be
   * needed when continuing to use range.
   */
  range( container& cont, 
         filter filFN = []( const reference ){ return true; },
         modifier modFN = []( const reference t ){ return t; } ):
    range( cont.begin(), cont.end(), filFN, modFN ){
  }

  /*! Get beginning iterator
   *
   * @return Iterator pointing to beginning of container
   */
  iterator begin() const{
    contIter iter( mBegin );
    while( !mFilter( *iter ) ){
      ++iter;
    }
    return iterator( this, iter );
  }

  /*! Get ending iterator
   *
   * @return Iterator pointing to past end of container
   */
  iterator end() const{
    return iterator( this, mEnd );
  }
};

#endif


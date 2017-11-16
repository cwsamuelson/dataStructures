#ifndef __VECTOR_HH__
#define __VECTOR_HH__

/*!
 * @example test-vector.cc
 */

#include<cmath>
#include<exception>
#include<string>
#include<utility>
#include<type_traits>

#include<normal_iterator.hh>
#include<allocator_traits.hh>
#include<allocator.hh>

namespace gsw{

template<typename T>
using requireInputIter =
        typename std::enable_if<
                   std::is_convertible<typename std::iterator_traits<T>::iterator_category,
                                       std::input_iterator_tag
                                      >::value
                               >::type;

/*! Class that stores items of type T
 *
 * @tparam T Type of items to be stored
 *
 * @tparam ALLOC type of allocator to use
 *
 * This class stores a dynamic number of items of type T, allocating additional
 * space as it becomes necessary.
 */
template<typename T, typename ALLOC = allocator<T> >
class vector{
public:
  /*! Type of stored values
   */
  using value_type = T;

  /*! pointer type to stored value
   */
  using pointer = value_type*;

  /*! reference to stored value
   */
  using reference = value_type&;

  /*! const reference to stored value
   */
  using const_reference = const value_type&;

  /*! const pointer type to stored value
   */
  using const_pointer = const value_type*;

  /*! Iterator type
   */
  using iterator = normal_iterator<value_type, vector>;

  /*! Type used for anything associated with container size
   */
  using size_type = unsigned long;

  /*!
   */
  using alloc = ALLOC;

private:
  using alloc_traits = allocator_traits<alloc>;

  alloc mAlloc;
  size_type mSize;
  size_type mCapacity;
  /* data is stored as char array, allowing constructors and destructors to be
   * manually run */
  value_type* mData;
  static const unsigned int datasize = sizeof( value_type );
  const float goldenRatio = 1.4;

  void reallocateTo( size_type size ){
    value_type* bfr;

    bfr = alloc_traits::allocate( mAlloc, size );

    // copy data to new buffer
    for( size_type i = 0; i < mSize; ++i ){
      bfr[i] = std::move( mData[i] );
    }

    alloc_traits::deallocate( mAlloc, mData, mCapacity );
    mCapacity = size;
    mData = bfr;
  }

public:
  /*! ctor, initialize with given capacity
   *
   * @param capacity  the value the capacity will be initialized to
   *
   * @param alc Allocator object to allocate data
   */
  vector( size_type capacity = 1, const alloc& alc = alloc() ):
    mAlloc( alc ),
    mSize( 0 ),
    mCapacity( capacity ),
    mData( alloc_traits::allocate( mAlloc, mCapacity ) ){
  }

  /*! ctor, initialize with count copies of val
   *
   * @param val  data to be copied
   *
   * @param count  the number of copies of val to be made
   *
   * @param alc Allocator object to allocate data
   */
  vector( const_reference val, size_type count, const alloc& alc = alloc() ):
    vector( count, alc ){

    while( count-- ){
      push_back( val );
    }
  }

  /*! copy ctor, copy other
   *
   * @param other  vector to copy data from
   *
   * @param alc Allocator object to allocate data
   */
  vector( const vector& other, const alloc& alc = alloc() ):
    mAlloc( alc ),
    mSize( other.mSize ),
    mCapacity( mSize + 5 ),
    mData( alloc_traits::allocate( mAlloc, mCapacity ) ){

    for( size_type i = 0; i < mSize; ++i ){
      mData[i] = other.mData[i];
    }
  }

  /*! move ctor, move other to this container
   *
   * @param other  vector to be moved here
   *
   * @param alc Allocator object to allocate data
   */
  vector( vector&& other, const alloc& alc = alloc() ):
    mAlloc( alc ),
    mSize( other.mSize ),
    mCapacity( other.mCapacity ),
    mData( other.mData ){

    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;
  }

  /*! copy array of elements
   *
   * @param other  array to copy values from
   *
   * @param size   the number of elements in other
   *
   * @param alc Allocator object to allocate data
   */
  vector( pointer other, size_type size, const alloc& alc = alloc() ):
    mAlloc( alc ),
    mSize( size ),
    mCapacity( mSize + 5 ),
    mData( alloc_traits::allocate( mAlloc, mCapacity ) ){

    for( size_type i = 0; i < mSize; ++i ){
      mData[i] = other[i];
    }
  }

  /*! copy ctor, copy elements from an arbitrary container
   *
   * @tparam inputIter  Iterator type to be read from
   *
   * @param first  first element to be copied
   *
   * @param last   one past the end of the container to be copied from
   *
   * @param alc Allocator object to allocate data
   */
  template<typename inputIter, typename = requireInputIter<inputIter> >
  vector( inputIter first, inputIter last, const alloc& alc = alloc() ):
    mAlloc( alc ){

    for( ; first != last; ++first ){
      push_back( *first );
    }
  }

  /*! dtor
   *
   * all data is cleared, destructors ran, and memory freed
   */
  virtual ~vector(){
    clear();
    alloc_traits::deallocate( mAlloc, mData, mCapacity );
  }

  /*! copy assignment, copy data from other
   *
   * @param other  vector from which data will be copied
   *
   * @return reference to this container
   *
   * @todo make this exception safe (i.e. don't delete mData until copy is safely complete)
   */
  vector& operator=( const vector& other ){
    if( mData == other.mData ){
      return *this;
    }

    if( mCapacity < other.mSize ){
      alloc_traits::deallocate( mAlloc, mData, mCapacity );

      mCapacity = other.mSize;
      mData = alloc_traits::allocate( mAlloc, mCapacity );
    }

    mSize = other.mSize;
    for( size_type i = 0; i < mSize; ++i ){
      mData[i] = other.mData[i];
    }

    return *this;
  }

  /*! move assignment, move data from other
   *
   * @param other  vector from which data will be moved
   *
   * @return reference to this container
   */
  vector& operator=( vector&& other ){
    alloc_traits::deallocate( mAlloc, mData, mCapacity );

    mSize = other.mSize;
    mCapacity = other.mCapacity;
    mData = other.mData;

    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;

    return *this;
  }

  /*! indexed getter, get element at index idx
   *
   * @param idx  index into container, from which data will be returned
   *
   * @return reference to data located at index idx
   */
  reference operator[]( size_type idx ){
    if( idx >= mSize ){
      throw std::out_of_range( "Index "s + std::to_string( idx ) + " out of bounds! Maximum value:\t" + std::to_string( max ) );
    }

    return ( reference )( *( mData + idx ) );
  }

  /*! indexed const getter, get const element at index idx
   *
   * @param idx  index into container, from which const data will be returned
   *
   * @return const reference to data located at index idx
   */
  const_reference operator[]( size_type idx ) const{
    return ( *this )[idx];
  }

  /*! first element getter
   *
   * @return reference to first element
   */
  reference front(){
    return ( *this )[0];
  }

  /*! last element getter
   *
   * @return reference to last element
   */
  reference back(){
    return ( *this )[mSize - 1];
  }

  /*! add data to the end
   *
   * @param data  data to be copied at the end of container
   *
   * Uses the copy constructor to copy data parameter into container
   */
  void push_back( const_reference data ){
    if( mSize + 1 > mCapacity ){
      reallocateTo( std::ceil( mCapacity * goldenRatio ) );
    }

    alloc_traits::construct( mAlloc, mData + mSize, data );
    ++mSize;
  }

  /*! construct new object at the end of container
   *
   * @tparam ...Args  Parameter pack of types of parameters to forward to constructor
   *
   * @param args  arguments to be passed to ctor of new object
   *
   * Forwards args to value_type constructor.
   */
  template<typename ...Args>
  void emplace_back( Args&&... args ){
    if( mSize + 1 > mCapacity ){
      reallocateTo( std::ceil( mCapacity * goldenRatio ) );
    }

    //use placement new to call ctor
    alloc_traits::construct( mAlloc, mData + mSize, std::forward<Args>( args )... );
    ++mSize;
  }

  /*! removes and destructs element at end of container
   */
  void pop_back(){
    --mSize;
    //call dtor
    alloc_traits::destroy( mAlloc, mData + mSize );
  }

  /*! removes and destructs all elements in container
   */
  void clear(){
    while( mSize > 0 ){
      pop_back();
    }
  }

  /*! get whether the container is empty
   *
   * @return container size equal to zero
   */
  bool empty() const{
    return mSize == 0;
  }

  /*! get current container size
   *
   * @return count of currently stored elements
   */
  size_type size() const{
    return mSize;
  }

  /*! get current container capacity
   *
   * @return number of elements that can be stored before a resize is necessary
   */
  size_type capacity() const{
    return mCapacity;
  }

  /*! request container to be a certain size
   *
   * @param count  new size
   *
   * @param value  the value to use in filling additional elements
   */
  void resize( size_type count, value_type value = value_type() ){
    while( mSize < count ){
      push_back( value );
    }
    while( mSize > count ){
      pop_back();
    }
  }

  /*! request container capacity be a certain size
   *
   * @param cap  new capacity
   */
  void reserve( size_type cap ){
    if( ( cap > mCapacity ) && ( cap > 0 ) ){
      reallocateTo( cap );
    }
  }

  /*! get iterator to beginning
   *
   * @return iterator to the first element of the container
   */
  iterator begin(){
    return Iterator( 0 );
  }

  /*! get const iterator to beginning
   *
   * @return const iterator to the first element of the container
   */
  const iterator cbegin() const{
    return begin();
  }

  /*! get iterator to end
   *
   * @return iterator to the last element of the container
   */
  iterator end(){
    return Iterator( mSize );
  }

  /*! get const iterator to end
   *
   * @return const iterator to the last element of the container
   */
  const iterator cend() const{
    return end();
  }

  /*! get general iterator
   *
   * @param idx  index iterator will point to
   *
   * @return iterator pointing to element at index idx
   */
  iterator Iterator( size_type idx ){
    return iterator( pointer( mData + idx ) );
  }
};

}

#endif


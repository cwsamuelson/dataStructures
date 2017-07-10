#ifndef __VECTOR_HH__
#define __VECTOR_HH__

/*!
 * @example test-vector.cc
 */

#include<cmath>
#include<exception>
#include<string>
#include<utility>

#include<normal_iterator.hh>

namespace gsw{

class indexOutOfBoundsException : public std::exception{
private:
  std::string msg;

public:
  indexOutOfBoundsException( unsigned long long idx ){
    msg = "Index ";
    msg += idx;
    msg += " out of bounds!";
  }
  virtual const char* what() const noexcept{
    return msg.data();
  }
};

/*! Class that stores items of type T
 *
 * @tparam T  Type of items to be stored
 *
 * This class stores a dynamic number of items of type T, allocating additional
 * space as it becomes necessary.
 */
template<class T>
class vector{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef const value_type* const_pointer;
  typedef normal_iterator<value_type, vector> iterator;
  typedef unsigned long size_type;

private:
  size_type mSize;
  size_type mCapacity;
  /* data is stored as char array, allowing constructors and destructors to be
   * manually run */
  unsigned char* mData;
  static const unsigned int datasize = sizeof( value_type );
  const float goldenRatio = 1.4;

  void reallocateTo( size_type size ){
    unsigned char* bfr;

    mCapacity = size;
    bfr = new unsigned char[( mCapacity * datasize )];

    // copy data to new buffer
    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
      bfr[i] = mData[i];
    }

    delete[] mData;
    mData = bfr;
  }

public:
  /*! ctor, initialize with givin capacity
   *
   * @param capacity  the value the capacity will be initialized to
   */
  vector( size_type capacity = 1 ):
    mSize( 0 ),
    mCapacity( capacity ),
    mData( new unsigned char[( mCapacity * datasize )] ){
  }

  /*! ctor, initialize with count copies of val
   *
   * @param val  data to be copied
   *
   * @param count  the number of copies of val to be made
   */
  vector( const_reference val, size_type count ):
    vector( count ){

    while( count-- ){
      push_back( val );
    }
  }

  /*! copy ctor, copy other
   *
   * @param other  vector to copy data from
   */
  vector( const vector& other ):
    mSize( other.mSize ),
    mCapacity( mSize + 5 ),
    mData( new unsigned char[( mCapacity * datasize )] ){

    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
      mData[i] = other.mData[i];
    }
  }

  /*! move ctor, move other to this container
   *
   * @param other  vector to be moved here
   */
  vector( vector&& other ):
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
   */
  vector( pointer other, size_type size ):
    mSize( size ),
    mCapacity( mSize + 5 ),
    mData( new unsigned char[( mCapacity * datasize )] ){

    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
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
   */
  template<typename inputIter>
  vector( inputIter first, inputIter last ){
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
    delete[] mData;
  }

  /*! copy assignment, copy data from other
   *
   * @param other  vector from which data will be copied
   *
   * @return reference to this container
   */
  vector& operator=( const vector& other ){
    if( mData == other.mData ){
      return *this;
    }

    if( mCapacity < other.mSize ){
      delete[] mData;
      
      mCapacity = other.mSize;
      mData = new unsigned char[( mCapacity * datasize )];
    }

    mSize = other.mSize;
    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
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
      throw indexOutOfBoundsException( idx );
    }

    return ( reference )( *( mData + ( idx * datasize ) ) );
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

    new ( ( pointer )( mData + ( mSize * datasize ) ) ) value_type( data );
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
  template<class ...Args>
  void emplace_back( Args&&... args ){
    if( mSize + 1 > mCapacity ){
      reallocateTo( std::ceil( mCapacity * goldenRatio ) );
    }

    //use placement new to call ctor
    new( ( pointer )( mData + ( mSize * datasize ) ) ) value_type( std::forward<Args>( args )... );
    ++mSize;
  }

  /*! removes and destructs element at end of container
   */
  void pop_back(){
    --mSize;
    //call dtor
    ( ( pointer )( mData + ( mSize * datasize ) ) )->~value_type();
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
    if( ( mCapacity < cap ) && ( cap > 0 ) ){
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
    return iterator( pointer( mData + ( idx * datasize ) ) );
  }
};

}

#endif


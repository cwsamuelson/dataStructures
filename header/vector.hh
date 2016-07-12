#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include<normal_iterator.hh>

template<class T>
class vector{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef normal_iterator<value_type, vector > iterator;

private:
    unsigned long mSize;
    unsigned long mCapacity;
    unsigned char* mData;
    //polymorphic data sizes? O.o
    const unsigned int datasize = sizeof(value_type);

public:
    vector():
        mSize(0),
        mCapacity(1),
        mData(new unsigned char[(mCapacity * datasize)]){
    }
    vector(unsigned int capacity):
        mSize(0),
        mCapacity(capacity),
        mData(new unsigned char[(mCapacity * datasize)]){
    }
    vector(const vector& other):
        mSize(other.mSize),
        mCapacity(mSize + 5),
        mData(new unsigned char[(mCapacity * datasize)]){
        for(unsigned long i = 0; i < (mSize * datasize); ++i){
            mData[i] = other.mData[i];
        }
    }
    vector(vector&& other):
        mSize(other.mSize),
        mCapacity(other.mCapacity),
        mData(other.mData){
        other.mSize = 0;
        other.mCapacity = 0;
        other.mData = nullptr;
    }
    vector(value_type* other, unsigned int size):
        mSize(size),
        mCapacity(mSize + 5),
        mData(new unsigned char[(mCapacity * datasize)]){
        for(unsigned int i = 0; i < (mSize * datasize); ++i){
            mData[i] = other[i];
        }
    }
    virtual ~vector(){
        delete[] mData;
    }
    
    vector& operator=(const vector& other){
        delete[] mData;
        
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = new unsigned char[(mCapacity * datasize)];
        
        for(unsigned int i = 0; i < (mSize * datasize); ++i){
            mData[i] = other.mData[i];
        }
        
        return *this;
    }
    vector& operator=(vector&& other){
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = other.mData;
        
        other.mSize = 0;
        other.mCapacity = 0;
        other.mData = nullptr;
        
        return *this;
    }
    value_type& operator[](unsigned int idx){
        return (value_type&)(*(mData + (idx * datasize)));
    }
    const reference operator[](unsigned int idx) const{
        return (value_type&)(*(mData + (idx * datasize)));
    }
    
    void push_back(const value_type& data){
        //reallocate
        if(mSize + 1 > mCapacity){
            mCapacity = mSize * 1.4;
            unsigned char* bfr = new unsigned char[mCapacity];
            for(unsigned int i = 0; i < (mSize * datasize); ++i){
                bfr[i] = mData[i];
            }
            delete[] mData;
            mData = bfr;
        }
        (T&)(*(mData + (mSize * datasize))) = data;
        ++mSize;
    }
    void push_back(value_type&& data){
        //reallocate
        if(mSize + 1 > mCapacity){
            mCapacity = mSize * 1.4;
            unsigned char* bfr = new unsigned char[mCapacity];
            for(unsigned int i = 0; i < (mSize * datasize); ++i){
                bfr[i] = mData[i];
            }
            delete[] mData;
            mData = bfr;
        }
        (value_type&)(*(mData + (mSize * datasize))) = data;
        ++mSize;
    }
    void pop_back(){
        --mSize;
    }
    unsigned int size() const{
        return mSize;
    }
    unsigned int capacity() const{
        return mCapacity;
    }
    iterator begin(){
        return iterator((pointer)mData);
    }
    iterator end(){
        return iterator((pointer)(mData + (mSize * datasize)));
    }
    iterator Iterator(unsigned int idx){
        return iterator(pointer(mData + (idx * datasize)));
    }
};

#endif


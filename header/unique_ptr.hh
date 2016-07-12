#ifndef __UNIQUE_PTR_HH__
#define __UNIQUE_PTR_HH__

template<class T>
class uniquePtr{
private:
    T* data;

public:
    uniquePtr(T* ptr):
        data(ptr){
    }
    uniquePtr(uniquePtr& other):
        data(other.data){
        other.data = nullptr;
    }
    virtual ~uniquePtr(){
        delete data;
    }
    
    uniquePtr& operator=(uniquePtr& other){
        if(data != other.data){
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
    
    T& operator*(){
        return *data;
    }
    
    T* operator->(){
        return data;
    }
};


#endif


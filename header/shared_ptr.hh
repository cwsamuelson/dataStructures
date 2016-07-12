#ifndef __SHARED_PTR_HH__
#define __SHARED_PTR_HH__

template<class T>
class sharedPtr{
private:
    T* data;
    unsigned long* count;

public:
    sharedPtr(T* ptr):
        data(ptr),
        count(new unsigned long(1)){
    }
    sharedPtr(const sharedPtr& other):
        data(other.data),
        count(other.count){
        ++(*count);
    }
    virtual ~sharedPtr(){
        if(--(*count) == 0){
            delete data;
            delete count;
        }
    }
    
    sharedPtr& operator=(sharedPtr& other){
        if(data != other.data){
            if(--(*count) == 0){
                delete data;
                delete count;
            }
            data = other.data;
            count = other.count;
            ++(*count);
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


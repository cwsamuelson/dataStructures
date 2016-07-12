#ifndef __BASIC_STRING_HH__
#define __BASIC_STRING_HH__

template<class T>
class basic_string{
private:
    unsigned int mSize;
    T* mString;
    static const T terminal;

public:
    basic_string(const basic_string& other){
        *this = other;
    }
    basic_string(basic_string&& other){
        *this = other;
    }
    basic_string(const T* str):
        mSize(0){
        while(str[mSize] != terminal){
            ++mSize;
        }
        mString = new char[mSize];
        for(unsigned int i = 0; i < mSize; ++i){
            mString[i] = str[i];
        }
    }
    virtual ~basic_string(){
        delete mString;
    }
    
    basic_string& operator=(const basic_string& other){
        mSize = other.mSize;
        
        delete[] mString;
        mString = new char[mSize];
        
        for(unsigned int i = 0; i < mSize; ++i){
            mString[i] = other.mString[i];
        }
        
        return *this;
    }
    basic_string& operator=(basic_string&& other){
        mSize = other.mSize;
        mString = other.mString;
        other.mSize = 0;
        other.mString = nullptr;
        
        return *this;
    }
    bool operator==(const basic_string& other){
        if(mSize != other.mSize){
            return false;
        }
        
        bool ret = true;
        
        for(unsigned int i = 0; i < mSize; ++i){
            ret &= (mString[i] == other.mString[i]);
        }
        return ret;
    }
    bool operator==(const char* other){
        return *this == basic_string(other);
    }
    T& operator[](unsigned int idx){
        return mString[idx];
    }
    const T& operator[](unsigned int idx) const{
        return mString[idx];
    }
    unsigned int size() const{
        return mSize;
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const basic_string<T>& str){
    for(unsigned int i = 0; i < str.size(); ++i){
        os << str[i];
    }
    return os;
}

#endif


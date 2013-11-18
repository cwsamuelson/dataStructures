#ifndef STRING_H
#define STRING_H

#include<cstdlib>
#include<iostream>

using std::ostream;
using std::istream;

class string{
private:
//    typedef unsigned int size_t;
    static const size_t npos = -1;
    char* data;
    size_t size;

    void init();

public:
    string();
    string(string& str);
    string(const char* s);
    ~string();

    const char* getString() const;
    const char* getString(size_t pos, size_t len) const;

    string& append(const string& str);
    string& append(const string& str, size_t subpos, size_t sublen);
    string& append(const char* s);
    string& append(const char* s, size_t n);
    string& append(size_t n, char c);

    string& assign(const string& str);
    string& assign(const string& str, size_t subpos, size_t sublen);
    string& assign(const char* s);
    string& assign(const char* s, size_t n);
    string& assign(size_t n, char c);

    string& erase(size_t pos = 0, size_t len = npos);
    size_t copy(char* s, size_t len = 0, size_t pos = 0) const;
    size_t find(char c);
    size_t find(const string& str, size_t pos = 0) const;
    size_t find(const char* s, size_t pos = 0) const;
    size_t rfind(const string& str, size_t pos = 0) const;
    size_t rfind(const char* s, size_t pos = 0) const;
    size_t length() const;
    bool empty() const;
    void clear();

    string& operator=(const string& str);
    string& operator=(const char* s);

    string& operator+=(const char* s);
    string& operator+=(const string& s);

    string  operator+(const string& opstr) const;
    string  operator+(const char* ops) const;
    string  operator+(const char opc) const;

//    string  operator+(const char* lhs, const string& rhs);
//    string  operator+(const char* lhs, const char* rhs);
//    string  operator+(const char lhs, const string& rhs);

    char& operator[](size_t pos);

};

ostream& operator<<(ostream& os, const string& str);

// STRING_H
#endif


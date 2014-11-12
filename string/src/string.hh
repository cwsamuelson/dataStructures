#ifndef __STRING_H__
#define __STRING_H__

#include<Jing/Object.hh>
#include<Jing/Iterable.hh>
#include<Jing/Comparable.hh>
#include<Jing/List>
#include<Jing/character>
#include<Jing/Misc.hh>
#include<iostream>

namespace Jing{

//index_t defined in AbstractList, will need to find a different name.
typedef unsigned long long index_t;

class string:public Iterable<char>, public Comparable<string>, public Comparable<char*>{
private:
  static const size_t npos = -1;
  char* data;
  //size should not include null terminating character
  size_t size;

  class stringIterator:public Iterator<char>{
  private:
    size_t idx;
    string* str;
  public:
    stringIterator(string* const & str);
    ~stringIterator();
    bool hasNext();
    char& next();
    void remove();
    void reset();
  };

public:
  //add regex methods in the future

  string();
  string(const string& str);
  string(const string& str, size_t length);
  string(const string& str, index_t offset, size_t length);

  string(const char* s);
  string(const char* s, size_t length);
  string(const char* s, index_t offset, size_t length);

  string(const int i);
  string(const char c);
  virtual ~string();

//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
  bool is_equal(const Object& obj)const;
//States
//  [inherited from Object]
//  hash
  unsigned long long hash() const;
//  clone
  string* clone() const;
//Iterator
//  [inherited from Iterable]
  Iterator<char>* iterator();

  char charAt(size_t idx) const;
  //IgnoreCase
  int compareToIC(const string& str) const;
  int compareTo(const string& str) const;
  int compareToIC(const char* str) const;
  int compareTo(const char* str) const;
  string& concat(const string& str);
  string& concat(char* s);
  string& concat(int i);
  bool contains(const string& str) const;
  bool endsWith(const string& suffix) const;
  bool startsWith(const string& prefix) const;
  //IgnoreCase
  bool equalsIC(const string& str) const;
  bool equalsIC(const char* s) const;

  bool equals(const string& str) const;
  bool equals(const char* s) const;
//formats a string using a format string and args list..
//  string& format(
//No gaurantee of data safety
  const char* c_str() const;
  index_t indexOf(char ch) const;
  index_t indexOf(char ch, index_t start) const;
  index_t indexOf(char* ch) const;
  index_t indexOf(char* ch, index_t start) const;
  index_t indexOf(const string& str) const;
  index_t indexOf(const string& str, index_t start) const;
  index_t lastIndexOf(char ch) const;
  index_t lastIndexOf(char ch, index_t start) const;
  index_t lastIndexOf(const string& str) const;
  index_t lastIndexOf(const string& str, index_t start) const;
  bool isEmpty() const;
  size_t length() const;
  void replace(char oldChar, char newChar);
  void replace(const char* oldS, const char* newS);
  void replace(string& oldStr, string& newStr);
  void replace(string& str);
  void replace(const char* s);
  string subString(index_t idx) const;
  string subString(index_t start, index_t end) const;
  List<string>* split(char c) const;
  List<string>* split(character& c) const;
  List<string>* split(char* c) const;
  List<string>* split(string& str) const;
  string& strip(char c);
  string& strip(character& c);
  string& strip(const char* c);
  string& strip(string& str);
//Returned pointer must be deleted by user.
  char* toCharArray() const;
  char* toCharArray(size_t length) const;
  char* toCharArray(index_t srcStart, index_t srcEnd) const;
  string toUpper() const;
  string toLower() const;
  string& trim();

  //returned string must be deleted by user.
  //factory methods
  static string& copyValue(char* data);
  static string& copyValue(char* data, size_t length);
  static string& copyValue(char* data, index_t offset, size_t length);

  static const string& intToString(int i);

  char operator[](size_t pos);

  string& operator=(const string& rhs);
  string& operator=(const char* rhs);
  string& operator=(const int rhs);

  string& operator+=(const string& rhs);
  string& operator+=(const char* rhs);
  string& operator+=(const int rhs);

  const string operator+(const string& rhs) const;
  const string operator+(const char* rhs) const;
  const string operator+(const int rhs);

//These should all exist from comparable inheritance.
//  bool operator==(const string& rhs) const;
//  bool operator==(const char* rhs) const;

//  bool operator!=(const string& rhs) const;
//  bool operator!=(const char* rhs) const;


  friend std::ostream& operator<<(std::ostream& os, const string& str);

  friend string& operator+=(const char* lhs, const string& rhs);

  friend const string operator+(const char* lhs, const string& rhs);
  friend const string operator+(char lhs, const string& rhs);

  friend bool operator==(const char* lhs, const string& rhs);

};

std::ostream& operator<<(std::ostream& os, const string& str);

string& operator+=(const char* lhs, const string& rhs);

const string operator+(const char* lhs, const string& rhs);
const string operator+(char lhs, const string& rhs);

bool operator==(const char* lhs, const string& rhs);

}

// STRING_H
#endif


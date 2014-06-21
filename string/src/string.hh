#ifndef __STRING_H__
#define __STRING_H__

#include<Jing/Misc.hh>
#include<iostream>

using std::ostream;
using std::istream;

namespace Jing{

class string:public Object{
private:
  static const size_t npos = -1;
  char* data;
  size_t size;

  void init();

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
  ~string();

//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//States
//  [inherited from Object]
//  hash
  int hash() const;
//  ID
  int classID() const;
//  clone
  Object* clone() const;

  char charAt(index_t idx) const;
  //IgnoreCase
  int compareToIC(const string& str) const;
  int compareTo(const string& str) const;
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
  //uses uninitialized pointer
  void getChars(char** dest) const;
  void getChars(char** dest, size_t length) const;
  void getChars(char** dest, index_t start, index_t end) const;
  const char* c_str() const;
  int hashCode() const;
  index_t indexOf(char ch) const;
  index_t indexOf(char ch, index_t start) const;
  index_t indexOf(const string& str) const;
  index_t indexOf(const string& str, index_t start) const;
  index_t lastIndexOf(char ch) const;
  index_t lastIndexOf(char ch, index_t start) const;
  index_t lastIndexOf(const string& str) const;
  index_t lastIndexOf(const string& str, index_t start) const;
  bool isEmpty() const;
  size_t length() const;
  string& replace(char oldChar, char newChar);
  string& subString(index_t idx) const;
  string& subString(index_t start, index_t end) const;
  char* toCharArray() const;
  string& toUpper() const;
  string& toLower() const;
  string& trim();

  //returned string must be deleted by user.
  //factory methods
  static string& copyValue(char* data);
  static string& copyValue(char* data, size_t length);
  static string& copyValue(char* data, index_t offset, size_t length);

  static const string& intToString(int i);

  string& operator=(const string& rhs);
  string& operator=(const char* rhs);
  string& operator=(const int rhs);

  string& operator+=(const string& rhs);
  string& operator+=(const char* rhs);
  string& operator+=(const int rhs);

  const string operator+(const string& rhs) const;
  const string operator+(const char* rhs) const;
  const string operator+(const int rhs);

  bool operator==(const string& rhs) const;
  bool operator==(const char* rhs) const;

  bool operator!=(const string& rhs) const;
  bool operator!=(const char* rhs) const;

  friend ostream& operator<<(ostream& os, const string& str);
  friend string& operator+=(const char* lhs, const string& rhs);
  friend const string operator+(const char* lhs, const string& rhs);
  friend const string operator+(char lhs, const string& rhs);
  friend bool operator==(const char* lhs, const string& rhs);

};

ostream& operator<<(ostream& os, const string& str);

string& operator+=(const char* lhs, const string& rhs);

const string operator+(const char* lhs, const string& rhs);
const string operator+(char lhs, const string& rhs);

bool operator==(const char* lhs, const string& rhs);

}

// STRING_H
#endif


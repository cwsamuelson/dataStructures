#ifndef STRING_H
#define STRING_H

#include<Jing/Misc.hh>

namespace Jing{

class string{
private:
  static const size_t npos = -1;
  char* data;
  size_t size;

  void init();

public:
  //add regex methods in the futur

  string();
  string(string& str);
  string(string& str, size_t length);
  string(string& str, index_t offset, size_t length);
  string(const char* s);
  string(const char* s, size_t length);
  string(const char* s, index_t offset, size_t length);
  ~string();

  char charAt(index_t idx) const;
  //IgnoreCase
  int compareToIC(const string& str) const;
  int compareTo(const string& str) const;
  string* concat(const string& str);
  string* concat(char* s);
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
  void getChars(char* dest) const;
  void getChars(char* dest, index_t start, index_t end) const;
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
  string* replace(char oldChar, char newChar);
  string* subString(index_t idx) const;
  string* subString(index_t start, index_t end) const;
  char* toCharArray() const;
  string* toUpper() const;
  string* toLower() const;
  string* trim();

  //returned string must be deleted by user.
  //factory methods
  static string& copyValue(char* data);
  static string& copyValue(char* data, size_t length);
  static string& copyValue(char* data, index_t offset, size_t length);

};

//ostream& operator<<(ostream& os, const string& str);

}

// STRING_H
#endif


#include<Jing/string>

using namespace Jing;

void string::init(){
    this->data = 0;
    this->size = 0;
}

string::string(){
  this->init();
}

string::string(const string& str){
  this->init();
  str.getChars(&(this->data), 0, str.length());
}

string::string(const string& str, size_t length){
  this->init();
  str.getChars(&(this->data), 0, length);
}

string::string(const string& str, index_t offset, size_t length){
  this->init();
  str.getChars(&(this->data), offset, length);
}

string::string(const char* s){
  this->init();
  unsigned int idx = 0;
  while(s[idx] != '\0'){
    ++idx;
  }
  this->data = new char[idx + 1];
  for(int i = 0; i < idx; ++i){
    this->data[i] = s[i];
  }
  this->data[idx] = '\0';
  this->size = idx;
}

string::string(const char* s, size_t length){
  this->init();
  unsigned int idx = 0;
  while(s[idx] != '\0'){
    ++idx;
  }
  if(idx < length){
    length = idx;
  }
  this->data = new char[length + 1];
  for(int i = 0; i < length; ++i){
    this->data[i] = s[i];
  }
  this->data[length] = '\0';
  this->size = length;
}

string::string(const char* s, index_t offset, size_t length){
  this->init();
  unsigned int idx = 0;
  while(s[idx] != '\0'){
    ++idx;
  }
  if(idx < length){
    length = idx;
  }
  this->data = new char[length + 1];
  for(int i = offset; i < length; ++i){
    this->data[i] = s[i];
  }
  this->data[length] = '\0';
  this->size = idx;
}

string::~string(){
  if(this->data != 0)
    delete this->data;
}

char string::charAt(index_t idx) const{
  if(this->data != 0)
    return this->data[idx];
  return 0;
}

int string::compareToIC(const string& str) const{
}

int string::compareTo(const string& str) const{
  int res = 0;
  while(this->length() > 0 && str.length() > 0){
    for(int i = 0; i < this->length() && i < str.length(); ++i){
      res += (char)this->charAt(i) - (char)str.charAt(i);
      if(res != 0){
        return res;
      }
    }
  }
  return res;
}

string* string::concat(const string& str){
//might be getting extra null characters
  size_t newSize = this->length() + str.length() + 1;
  //NEED TO CLEAN UP TEMP
  //because memory leak :(
  char* temp = new char[newSize];
  for(int i = 0; i < this->length(); ++i){
    temp[i] = this->charAt(i);
  }
  for(int i = 0; i < str.length(); ++i){
    temp[this->length() + i] = str.charAt(i);
  }
  temp[newSize] = '\0';

  return new string(temp);
}

string* string::concat(char* s){
  string temp(s);
  return this->concat(temp);
}

bool string::contains(const string& str) const{
  return false;
}

bool string::endsWith(const string& suffix) const{
  return false;
}

bool string::startsWith(const string& prefix) const{
  for(int i = 0; i < this->length() && i < prefix.length(); i++){
    if(this->charAt(i) != prefix.charAt(i)){
      return false;
    }
  }
  return true;
}

bool string::equalsIC(const string& str) const{
  return this->equals(str);
}

bool string::equalsIC(const char* s) const{
  return this->equalsIC(string(s));
}

bool string::equals(const string& str) const{
  return false;
}

bool string::equals(const char* s) const{
  return this->equals(string(s));
}

void string::getChars(char** dest) const{
  this->getChars(dest, 0, this->length());
}

void string::getChars(char** dest, size_t length) const{
  this->getChars(dest, 0, length);
}

void string::getChars(char** dest, index_t start, index_t end) const{
  unsigned int size = end - start + 1;
  char * temp = new char[size + 1];
  for(int i = start; i < end; ++i){
    temp[i] = this->data[i];
  }
  *dest = temp;
}

int string::hashCode() const{
  return 0;
}

index_t string::indexOf(char ch) const{
  return this->indexOf(ch, 0);
}

index_t string::indexOf(char ch, index_t start) const{
  for(int i = start; i < this->length(); i++){
    if(this->charAt(i) == ch){
      return i;
    }
  }
  return -1;
}

index_t string::indexOf(const string& str) const{
  return this->indexOf(str, 0);
}

index_t string::indexOf(const string& str, index_t start) const{
//  for(int i = 0; i < this->length(); i++){
//    while(i < this->length && 
}

index_t string::lastIndexOf(char ch) const{
  return this->lastIndexOf(ch, this->length());
}

index_t string::lastIndexOf(char ch, index_t start) const{
  for(int i = this->length(); i > start; i--){
    if(this->charAt(i) == ch){
      return i;
    }
  }
  return -1;
}

index_t string::lastIndexOf(const string& str) const{
  return this->lastIndexOf(str, this->length());
}

index_t string::lastIndexOf(const string& str, index_t start) const{
  return -1;
}

bool string::isEmpty() const{
  if(this->size == 0){
    return true;
  }
  return false;
}

size_t string::length() const{
  return this->size;
}

string* string::replace(char oldChar, char newChar){
  char* ret = new char[this->length()];
  for(int i = 0; i < this->length(); i++){
    if(this->charAt(i) == oldChar){
      ret[i] = newChar;
    } else {
      ret[i] = this->charAt(i);
    }
  }
  string* str = new string(ret);
  delete ret;
  return str;
}

string* string::subString(index_t idx) const{
  return this->subString(idx, this->length());
}

//Returned reference must be deleted by user.
string* string::subString(index_t start, index_t end) const{
  if(start < this->length() && end < this->length()){
    return new string(this->data, start, end - start);
  }
  //throw exception
}

//Returned pointer must be deleted by user.
char* string::toCharArray() const{
  char* ret = new char[this->length()];
  for(int i = 0; i < this->length(); i++){
    ret[i] = this->data[i];
  }
  return ret;
}

//Returned reference must be deleted by user.
string* string::toUpper() const{
  string* ret = new string(this->data);
  for(int i = 0; i < this->length(); ++i){
    if(ret->data[i] >= 97 && ret->data[i] <= 122){
      ret->data[i] -= 32;
    }
  }
  return ret;
}

//Returned reference must be deleted by user.
string* string::toLower() const{
  string* ret = new string(this->data);
  for(int i = 0; i < this->length(); ++i){
    if(ret->data[i] >= 65 && ret->data[i] <= 90){
      ret->data[i] += 32;
    }
  }
  return ret;
}

string* string::trim(){
}

string& string::operator=(const string& rhs){
  //Self assignment?  You sneaky devil.
  if(this != &rhs){
    size_t len = rhs.length();
    if(this->data != 0)
      delete this->data;
    this->size = len;
    this->data = new char[len];
    for(int i = 0; i < len; ++i){
      this->data[i] = rhs.charAt(i);
    }
    this->data[len] = '\0';
  }
  return *this;
}

string& string::operator=(const char* rhs){
  string *temp = new string(rhs);
  *this = rhs;
  delete temp;
  return *this;
}

string& string::operator+=(const string& rhs){
  *this->concat(rhs);
  return *this;
}

string& string::operator+=(const char* rhs){
  *this->concat(rhs);
  return *this;
}

const string string::operator+(const string& rhs) const{
  return string(*this) += rhs;
}

const string string::operator+(const char* rhs) const{
  return string(*this) += rhs;
}

bool string::operator==(const char* rhs) const{
  return this->equals(rhs);
}

bool string::operator==(const string& rhs) const{
  return this->equals(rhs);
}

bool string::operator!=(const char* rhs) const{
  return !this->equals(rhs);
}

bool string::operator!=(const string& rhs) const{
  return !this->equals(rhs);
}

//----------------------
// non-member operators.
//----------------------

ostream& Jing::operator<<(ostream& os, const string& str){
  if(str.data != 0)
    os << str.data;
  return os;
}

string& operator+=(const char* lhs, const string& rhs){
  return (string(lhs) += rhs);
}

const string operator+(const char* lhs, const string& rhs){
  return (string(lhs) + rhs);
}

bool operator==(const char* lhs, const string& rhs){
  return rhs.equals(lhs);
}


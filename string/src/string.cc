#include<Jing/string>

void Jing::string::init(){
    this->data = 0;
    this->size = 0;
}

const Jing::string& Jing::string::intToString(int i){
  Jing::string *temp = new Jing::string();
//  char *temp;
  int num = i;
  int digit;
  char c;
  c = '\0';
  while(num > 0){
    switch(num % 10){
    case 0:
      digit = 0;
      c = '0';
      break;
    case 1:
      digit = 1;
      c = '1';
      break;
    case 2:
      digit = 2;
      c = '2';
      break;
    case 3:
      digit = 3;
      c = '3';
      break;
    case 4:
      digit = 4;
      c = '4';
      break;
    case 5:
      digit = 5;
      c = '5';
      break;
    case 6:
      digit = 6;
      c = '6';
      break;
    case 7:
      digit = 7;
      c = '7';
      break;
    case 8:
      digit = 8;
      c = '8';
      break;
    case 9:
      digit = 9;
      c = '9';
      break;
    }

    num -= digit;
    num /=10;
    temp = c + temp;
  }
  return *temp;
}

Jing::string::string(){
  this->init();
}

Jing::string::string(const Jing::string& str){
  this->init();
  str.getChars(&(this->data), 0, str.length());
}

Jing::string::string(const Jing::string& str, size_t length){
  this->init();
  str.getChars(&(this->data), 0, length);
}

Jing::string::string(const Jing::string& str, index_t offset, size_t length){
  this->init();
  str.getChars(&(this->data), offset, length);
}

Jing::string::string(const char* s){
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

Jing::string::string(const char* s, size_t length){
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

Jing::string::string(const char* s, index_t offset, size_t length){
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

Jing::string::string(const int i){
  *this = intToString(i);
}

Jing::string::string(const char c){
  this->init();
  this->data = new char[2];
  this->data[0] = c;
  this->data[1] = '\0';
  this->size = 1;
}

Jing::string::~string(){
  if(this->data != 0)
    delete this->data;
}

bool Jing::string::equals(Object& obj) const{
  return false;
}

int Jing::string::hash() const{
  return 0;
}

int Jing::string::classID() const{
  return 0;
}

Object* clone() const{
  return this;
}

char Jing::string::charAt(index_t idx) const{
  if(this->data != 0)
    return this->data[idx];
  return 0;
}

int Jing::string::compareToIC(const Jing::string& str) const{
}

int Jing::string::compareTo(const Jing::string& str) const{
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

Jing::string& string::concat(const Jing::string& str){
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

  return *(new string(temp));
}

Jing::string& Jing::string::concat(char* s){
  Jing::string temp(s);
  return this->concat(temp);
}

Jing::string& Jing::string::concat(int i){
}

bool Jing::string::contains(const Jing::string& str) const{
  return false;
}

bool Jing::string::endsWith(const Jing::string& suffix) const{
  return false;
}

bool Jing::string::startsWith(const Jing::string& prefix) const{
  for(int i = 0; i < this->length() && i < prefix.length(); i++){
    if(this->charAt(i) != prefix.charAt(i)){
      return false;
    }
  }
  return true;
}

bool Jing::string::equalsIC(const Jing::string& str) const{
  return this->equals(str);
}

bool Jing::string::equalsIC(const char* s) const{
  return this->equalsIC(string(s));
}

bool Jing::string::equals(const Jing::string& str) const{
  return false;
}

bool Jing::string::equals(const char* s) const{
  return this->equals(string(s));
}

void Jing::string::getChars(char** dest) const{
  this->getChars(dest, 0, this->length());
}

void Jing::string::getChars(char** dest, size_t length) const{
  this->getChars(dest, 0, length);
}

void Jing::string::getChars(char** dest, index_t start, index_t end) const{
  unsigned int size = end - start + 1;
  char * temp = new char[size + 1];
  for(int i = start; i < end; ++i){
    temp[i] = this->data[i];
  }
  *dest = temp;
}

int Jing::string::hashCode() const{
  return 0;
}

index_t Jing::string::indexOf(char ch) const{
  return this->indexOf(ch, 0);
}

index_t Jing::string::indexOf(char ch, index_t start) const{
  for(int i = start; i < this->length(); i++){
    if(this->charAt(i) == ch){
      return i;
    }
  }
  return -1;
}

index_t Jing::string::indexOf(const Jing::string& str) const{
  return this->indexOf(str, 0);
}

index_t Jing::string::indexOf(const Jing::string& str, index_t start) const{
//  for(int i = 0; i < this->length(); i++){
//    while(i < this->length && 
}

index_t Jing::string::lastIndexOf(char ch) const{
  return this->lastIndexOf(ch, this->length());
}

index_t Jing::string::lastIndexOf(char ch, index_t start) const{
  for(int i = this->length(); i > start; i--){
    if(this->charAt(i) == ch){
      return i;
    }
  }
  return -1;
}

index_t Jing::string::lastIndexOf(const Jing::string& str) const{
  return this->lastIndexOf(str, this->length());
}

index_t Jing::string::lastIndexOf(const Jing::string& str, index_t start) const{
  return -1;
}

bool Jing::string::isEmpty() const{
  if(this->size == 0){
    return true;
  }
  return false;
}

Jing::size_t Jing::string::length() const{
  return this->size;
}

Jing::string& Jing::string::replace(char oldChar, char newChar){
  char* ret = new char[this->length()];
  for(int i = 0; i < this->length(); i++){
    if(this->charAt(i) == oldChar){
      ret[i] = newChar;
    } else {
      ret[i] = this->charAt(i);
    }
  }
  Jing::string* str = new string(ret);
  delete ret;
  return *str;
}

Jing::string& Jing::string::subString(index_t idx) const{
  return this->subString(idx, this->length());
}

//Returned reference must be deleted by user.
Jing::string& Jing::string::subString(index_t start, index_t end) const{
  if(start < this->length() && end < this->length()){
    return *(new string(this->data, start, end - start));
  }
  //throw exception
}

//Returned pointer must be deleted by user.
char* Jing::string::toCharArray() const{
  char* ret = new char[this->length()];
  for(int i = 0; i < this->length(); i++){
    ret[i] = this->data[i];
  }
  return ret;
}

//Returned reference must be deleted by user.
Jing::string& Jing::string::toUpper() const{
  Jing::string* ret = new string(this->data);
  for(int i = 0; i < this->length(); ++i){
    if(ret->data[i] >= 97 && ret->data[i] <= 122){
      ret->data[i] -= 32;
    }
  }
  return *ret;
}

//Returned reference must be deleted by user.
Jing::string& Jing::string::toLower() const{
  Jing::string* ret = new string(this->data);
  for(int i = 0; i < this->length(); ++i){
    if(ret->data[i] >= 65 && ret->data[i] <= 90){
      ret->data[i] += 32;
    }
  }
  return *ret;
}

Jing::string& Jing::string::trim(){
}

Jing::string& Jing::string::operator=(const Jing::string& rhs){
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

Jing::string& Jing::string::operator=(const char* rhs){
  Jing::string *temp = new string(rhs);
  *this = *temp;
  delete temp;
  return *this;
}

Jing::string& Jing::string::operator=(const int rhs){
  Jing::string *temp = new Jing::string(rhs);
  *this = *temp;
  delete temp;
  return *this;
}

Jing::string& Jing::string::operator+=(const Jing::string& rhs){
  this->concat(rhs);
  return *this;
}

Jing::string& Jing::string::operator+=(const char* rhs){
  this->concat(rhs);
  return *this;
}

Jing::string& Jing::string::operator+=(const int rhs){
  this->concat(rhs);
  return *this;
}

const Jing::string Jing::string::operator+(const Jing::string& rhs) const{
  return string(*this) += rhs;
}

const Jing::string Jing::string::operator+(const char* rhs) const{
  return string(*this) += rhs;
}

const Jing::string Jing::string::operator+(const int rhs){
  return string(*this) += rhs;
}

bool Jing::string::operator==(const char* rhs) const{
  return this->equals(rhs);
}

bool Jing::string::operator==(const Jing::string& rhs) const{
  return this->equals(rhs);
}

bool Jing::string::operator!=(const char* rhs) const{
  return !this->equals(rhs);
}

bool Jing::string::operator!=(const Jing::string& rhs) const{
  return !this->equals(rhs);
}

//----------------------
// non-member operators.
//----------------------

ostream& Jing::operator<<(ostream& os, const Jing::string& str){
  if(str.data != 0){
    os << str.data;
  }
  return os;
}

Jing::string& operator+=(const char* lhs, const Jing::string& rhs){
  return (string(lhs) += rhs);
}

const Jing::string operator+(const char* lhs, const Jing::string& rhs){
  return (string(lhs) + rhs);
}

const Jing::string operator+(char lhs, const Jing::string& rhs){
  return (string(lhs) + rhs);
}

bool operator==(const char* lhs, const Jing::string& rhs){
  return rhs.equals(lhs);
}


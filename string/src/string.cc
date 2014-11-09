#include<Jing/string>

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

Jing::string::string():data(0),size(0){  }

Jing::string::string(const Jing::string& str):string(str, str.length()){  }

Jing::string::string(const Jing::string& str, Jing::size_t length):string(str, 0, length){  }

Jing::string::string(const Jing::string& str, Jing::index_t offset, Jing::size_t length):string(){
  this->data = str.toCharArray(offset, offset + length);
  if(this->data != 0){
    this->size = length;
  }
}

Jing::string::string(const char* s):string(){
  unsigned int idx = 0;
  while(s[idx] != '\0'){
    ++idx;
  }
  this->data = new char[idx + 1];
  for(unsigned int i = 0; i < idx; ++i){
    this->data[i] = s[i];
  }
  this->data[idx] = '\0';
  this->size = idx;
}

Jing::string::string(const char* s, Jing::size_t length):string(s, 0, length){  }

Jing::string::string(const char* s, Jing::index_t offset, Jing::size_t length):string(){
  unsigned int idx = offset;
  while(s[idx] != '\0'){
    ++idx;
  }
  if(idx < length){
    length = idx;
  }
  this->data = new char[length + 1];
  for(unsigned int i = offset; i < length; ++i){
    this->data[i] = s[i];
  }
  this->data[length] = '\0';
  this->size = length;
}

Jing::string::string(const int i){
  *this = intToString(i);
}

Jing::string::string(const char c):string(){
  this->data = new char[2];
  this->data[0] = c;
  this->data[1] = '\0';
  this->size = 1;
}

Jing::string::~string(){
  if(this->data != 0)
    delete[] this->data;
}

bool Jing::string::is_equal(const Object& obj) const{
  const Jing::string& obj_derived = dynamic_cast<const Jing::string&>(obj);
  Jing::index_t len = obj_derived.length();
  if(this->length() != obj_derived.length()){
    return false;
  }
  for(Jing::index_t i = 0; i < len; ++i){
    if(this->charAt(i) != obj_derived.charAt(i)){
      return false;
    }
  }
  return true;
}

//Hash based on murmur hash 3 found on wikipedia.
//  https://en.wikipedia.org/wiki/MurmurHash#Implementations
//Murmur hash requires 3 parameters.
//  1. key
//  2. length
//  3. seed
//For this implementation
//  the key is the stored letter
//  the length is one
//  the seed will be constant
//  need to make the seed to be random, and not constant are described:
//One reason is that attackers may use the properties of a hash function 
//  to construct a denial of service attack. They could do this by providing
//  strings to your hash function that all hash to the same value destroying
//  the performance of your hash table. But if you use a different seed for
//  each run of your program, the set of strings the attackers must use changes.
//This feature is not included for simplicity,
//  and for the sake of not including std libraries (keeping all code my own)
/*
       char:8   bits
       long:32  bits
  long long:64  bits
*/
unsigned long long Jing::string::hash() const{
  unsigned long len = 1;
  unsigned long long key = 0;
  unsigned long seed = 5871;

  const unsigned long c1 = 0xcc9e2d51;
  const unsigned long c2 = 0x1b873593;
  const unsigned long r1 = 15;
  const unsigned long r2 = 13;
  const unsigned long m = 5;
  const unsigned long n = 0xe6546b64;

  unsigned long long hash = seed;
  unsigned int nblocks = 0;

  for(unsigned long long int j = 0; j < this->length(); ++j){
    key = (int)(this->data[j]);
//    key = this->get(j).hash();
    for(unsigned long long i = 0, mask = 0xf; i < 16; ++i, mask <<= 4){
      unsigned long long k = (key & mask) >> (4 * i);
      ++nblocks;

      k = k * c1;
      k = (k << r1) | (k >> (32 - r1));
      k = k * c2;

      hash = hash ^ k;
      hash = (hash << r2) | (hash >> (32 - r2));
      hash = hash * m + n;
    }
  }

  len = nblocks;
  hash = hash ^ len;

  hash = hash ^ (hash >> 16);
  hash = hash * 0x85ebca6b;
  hash = hash ^ (hash >> 13);
  hash = hash * 0xc2b2ae35;
  hash = hash ^ (hash >> 16);

  return hash;
}

Jing::string* Jing::string::clone() const{
  return new string(this->data);
}

Jing::Iterator<char>* Jing::string::iterator(){
  return new stringIterator(this);
}

char Jing::string::charAt(Jing::size_t idx) const{
  if(this->data != 0)
    return this->data[idx];
  return 0;
}

int Jing::string::compareToIC(const Jing::string& str) const{
  return 0;
}

int Jing::string::compareTo(const Jing::string& str) const{
  int result = 0;
  //not sure why this was a while loop?
  if(this->length() > 0 && str.length() > 0){
    for(unsigned int i = 0; i < this->length() && i < str.length(); ++i){
      result += (char)this->charAt(i) - (char)str.charAt(i);
      if(result != 0){
        return result;
      }
    }
  }
  return result;
}

int Jing::string::compareToIC(const char* str) const{
  string foo(str);
  return this->compareToIC(foo);
}

int Jing::string::compareTo(const char* str) const{
  string foo(str);
  this->compareTo(foo);
}


//TODO:concat should modify this, and return *this
Jing::string& Jing::string::concat(const Jing::string& str){
  size_t newSize = this->length() + str.length() + 1;
  char* temp = new char[newSize];
  for(unsigned int i = 0; i < this->length(); ++i){
    temp[i] = this->charAt(i);
  }
  for(unsigned int i = 0; i < str.length(); ++i){
    temp[this->length() + i] = str.charAt(i);
  }
  temp[newSize] = '\0';
  delete this->data;
  this->data = temp;
  this->size = newSize;
  return *this;
}

Jing::string& Jing::string::concat(char* s){
  Jing::string temp(s);
  return this->concat(temp);
}

Jing::string& Jing::string::concat(int i){
}

bool Jing::string::contains(const Jing::string& str) const{
  if(this->indexOf(str) == (Jing::index_t)-1){
    return false;
  } else {
    return true;
  }
}

bool Jing::string::endsWith(const Jing::string& suffix) const{
  return false;
}

bool Jing::string::startsWith(const Jing::string& prefix) const{
  for(unsigned int i = 0; i < this->length() && i < prefix.length(); i++){
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

bool Jing::string::equals(const char* s) const{
  return this->equals(string(s));
}

const char* Jing::string::c_str() const{
  return this->data;
}

Jing::index_t Jing::string::indexOf(char ch) const{
  return this->indexOf(ch, 0);
}

Jing::index_t Jing::string::indexOf(char ch, Jing::index_t start) const{
  for(Jing::index_t i = start; i < this->length(); i++){
    if(this->charAt(i) == ch){
      return i;
    }
  }
  return -1;
}

Jing::index_t Jing::string::indexOf(const Jing::string& str) const{
  return this->indexOf(str, 0);
}

Jing::index_t Jing::string::indexOf(const Jing::string& str, Jing::index_t start) const{
  Jing::index_t strIndex = 1;
  for(Jing::index_t i = 0; i < this->length(); ++i){
    if(this->charAt(i) != str.charAt(strIndex)){
      strIndex = 0;
      continue;
    } else {
      ++strIndex;
    }

    if(strIndex == str.length()){
      return i - strIndex;
    }
  }
  return -1;
}

Jing::index_t Jing::string::lastIndexOf(char ch) const{
  return this->lastIndexOf(ch, this->length());
}

Jing::index_t Jing::string::lastIndexOf(char ch, Jing::index_t start) const{
  for(unsigned int i = this->length(); i > start; i--){
    if(this->charAt(i) == ch){
      return i;
    }
  }
  return -1;
}

Jing::index_t Jing::string::lastIndexOf(const Jing::string& str) const{
  return this->lastIndexOf(str, this->length());
}

Jing::index_t Jing::string::lastIndexOf(const Jing::string& str, Jing::index_t start) const{
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

void Jing::string::replace(char oldChar, char newChar){
  this->data[this->indexOf(oldChar)] = newChar;
}

void Jing::string::replace(Jing::string& str){
  delete[] this->data;
  this->data = str.toCharArray();
  this->size = str.length();
}

void Jing::string::replace(const char* s){
  string* temp = new string(s);
  this->replace(*temp);
  delete temp;
}

Jing::string& Jing::string::subString(Jing::index_t idx) const{
  return this->subString(idx, this->length());
}

//Returned reference must be deleted by user.
Jing::string& Jing::string::subString(Jing::index_t start, Jing::index_t end) const{
  if(start < this->length() && end < this->length()){
    return *(new string(this->data, start, end - start));
  }
  //throw exception
}

Jing::List<Jing::string>* Jing::string::split(char c) const{
  Jing::List<Jing::string>* ret = new Jing::List<Jing::string>();
  Jing::index_t idx1 = 0;
  Jing::index_t idx2 = 0;

  while(idx2 < this->length()){
    idx2 = this->indexOf(c);
    //return maybe a little prematurely to handle failed find
    if(idx2 == (Jing::index_t)-1){
      return ret;
    }
    ret->insert(this->substring(idx1, idx2 - 1);
    idx1 = idx2 + 1;
    idx2 = idx1;
  }
  
  return ret;
}

Jing::List<Jing::string>* Jing::string::split(character& c) const{
  return 0;
}

Jing::List<Jing::string>* Jing::string::split(char* c) const{
  return 0;
}

Jing::List<Jing::string>* Jing::string::split(Jing::string& str) const{
  return 0;
}

Jing::string& Jing::string::strip(char c){
  return *this;
}

Jing::string& Jing::string::strip(character& c){
  return *this;
}

Jing::string& Jing::string::strip(const char* c){
  return *this;
}

Jing::string& Jing::string::strip(Jing::string& str){
  return *this;
}

char* Jing::string::toCharArray() const{
  return this->toCharArray(this->length());
}

char* Jing::string::toCharArray(Jing::size_t length) const{
  return this->toCharArray(0, length);
}

char* Jing::string::toCharArray(Jing::index_t srcStart, Jing::index_t srcEnd) const{
  if(srcEnd > this->length())
    return 0;
  if(srcStart > srcEnd)
    return 0;

  //if len == 0, array of length 1 containing null terminator should be returned
  Jing::index_t len = srcEnd - srcStart;
  char* ret = new char[len + 1];
  for(Jing::index_t i = 0; i < len; ++i){
    ret[i] = this->data[i + srcStart];
  }
  this->data[len] = '\0';
  return ret;
}

//Returned reference must be deleted by user.
Jing::string& Jing::string::toUpper() const{
  Jing::string* ret = new string(this->data);
  for(unsigned int i = 0; i < this->length(); ++i){
    if(ret->data[i] >= 97 && ret->data[i] <= 122){
      ret->data[i] -= 32;
    }
  }
  return *ret;
}

//Returned reference must be deleted by user.
Jing::string& Jing::string::toLower() const{
  Jing::string* ret = new string(this->data);
  for(unsigned int i = 0; i < this->length(); ++i){
    if(ret->data[i] >= 65 && ret->data[i] <= 90){
      ret->data[i] += 32;
    }
  }
  return *ret;
}

Jing::string& Jing::string::trim(){
}

char Jing::string::operator[](size_t pos){
  return this->charAt(pos);
}

Jing::string& Jing::string::operator=(const Jing::string& rhs){
  //Self assignment?  You sneaky devil.
  if(this != &rhs){
    Jing::size_t len = rhs.length();
    if(this->data != 0){
      delete[] this->data;
    }
    this->size = len;
    this->data = new char[len];
    for(size_t i = 0; i < len; ++i){
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

//code covered by comparable inheritance
//leaving until confirmed it works
/*
bool Jing::string::operator==(const char* rhs) const{
  return this->equals(rhs);
}

bool Jing::string::operator!=(const char* rhs) const{
  return !this->equals(rhs);
}
*/

//----------------------
// non-member operators.
//----------------------

std::ostream& Jing::operator<<(std::ostream& os, const Jing::string& str){
  if(str.data != 0){
    os << str.data;
  }
  return os;
}

Jing::string& operator+=(const char* lhs, const Jing::string& rhs){
  return (Jing::string(lhs) += rhs);
}

const Jing::string operator+(const char* lhs, const Jing::string& rhs){
  return (Jing::string(lhs) + rhs);
}

const Jing::string operator+(char lhs, const Jing::string& rhs){
  return (Jing::string(lhs) + rhs);
}

bool operator==(const char* lhs, const Jing::string& rhs){
  return rhs.equals(lhs);
}

Jing::string::stringIterator::stringIterator(string* const & str):idx(0),str(str){  }

Jing::string::stringIterator::~stringIterator(){  }

bool Jing::string::stringIterator::hasNext(){
  return (this->idx < this->str->length());
}

char& Jing::string::stringIterator::next(){
  if(this->idx < this->str->length()){
    ++this->idx;
  }

  char c = this->str->charAt(this->idx);
  char& b = c;
  return b;
}

void Jing::string::stringIterator::remove(){
  //I don't wanna  do it.
}

void Jing::string::stringIterator::reset(){
  this->idx = 0;
}


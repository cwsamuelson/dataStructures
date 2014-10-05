#include"Integer.hh"

Jing::Integer::Integer(int c):value(new int(c)){
//  *(this->value) = c;
}

Jing::Integer::~Integer(){  }

bool Jing::Integer::is_equal(const Jing::Object& obj) const{
  const Jing::Integer& obj_derived = dynamic_cast<const Jing::Integer&>(obj);
  if(this->value == obj_derived.value){
    return true;
  } else {
    return false;
  }
}

bool Jing::Integer::equals(Integer& ch) const{
  return this->is_equal(ch);
}

bool Jing::Integer::equals(int ch) const{
  Jing::Integer* temp = new Jing::Integer(ch);
  bool ret = this->equals(*temp);
  delete temp;
  return ret;
}

//Hash based on murmur hash 3 found on wikipedia.
//  https://en.wikipedia.org/wiki/MurmurHash#Implementations
//Murmur hash requires 3 parameters.
//  1. key
//  2. length
//  3. seed
//For this implementation
//  the key is the stored value
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
unsigned long long Jing::Integer::hash() const{
  unsigned long len = 1;
  unsigned long key = (unsigned long)this->value;
  unsigned long seed = 5871;

  const unsigned long c1 = 0xcc9e2d51;
  const unsigned long c2 = 0x1b873593;
  const unsigned long r1 = 15;
  const unsigned long r2 = 13;
  const unsigned long m = 5;
  const unsigned long n = 0xe6546b64;

  unsigned long long hash = seed;

  unsigned long long k = key;

  k = k * c1;
  k = (k << r1) | (k >> (32 - r1));
  k = k * c2;

  hash = hash ^ k;
  hash = (hash << r2) | (hash >> (32 - r2));
  hash = hash * m + n;

  hash = hash ^ len;

  hash = hash ^ (hash >> 16);
  hash = hash * 0x85ebca6b;
  hash = hash ^ (hash >> 13);
  hash = hash * 0xc2b2ae35;
  hash = hash ^ (hash >> 16);

  return hash;
}

Jing::Integer* Jing::Integer::clone() const{
  return new Integer(*(this->value));
}

int Jing::Integer::compareTo(Integer& c) const{
  return (int)this->value - (int)c.value;
}

double Jing::Integer::asDouble() const{
  return (double)*(this->value);
}

int Jing::Integer::asInt() const{
  return (int)this->value;
}

char Jing::Integer::asChar() const{
  return (char)*(this->value);
}

Jing::Number& Jing::Integer::operator=(const Number& rhs){
  //Self assignment?  You sneaky devil.
  if(this != &rhs){
    int temp = *((int*)(rhs.value));
    *(this->value) = temp;
  }
  return *this;
}

std::ostream& Jing::operator<<(std::ostream& os, const Jing::Integer& let){
  os << let.value;
  return os;
}


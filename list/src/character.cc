#include"character.hh"

Jing::character::character(char c):letter(c){ }

Jing::character::~character(){  }

bool Jing::character::equals(Jing::Object& obj) const{
  this->equals((character&)obj);
  return false;
}

bool Jing::character::equals(Jing::character& ch) const{
  if(this->letter == ch.letter)
    return true;
  else
    return false;
}

bool Jing::character::equals(char ch) const{
  if(this->letter == ch)
    return true;
  else
    return false;
}

int Jing::character::hash() const{
  return ((int)this->letter - (int)'a');
}

Jing::character* Jing::character::clone() const{
  return new character(this->letter);
}

std::ostream& Jing::operator<<(std::ostream& os, const Jing::character& let){
  os << let.letter;
  return os;
}


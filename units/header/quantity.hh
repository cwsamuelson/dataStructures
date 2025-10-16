#pragma once

namespace flp {

template<typename Unit, typename Type>
struct Quantity{
private:
  Quantity(const Type& value){}
};

template<typename Type, typename Unit>
Quantity operator*(const Type& value, const Unit&) {
  return Quantity<Unit, Type>(value);
}

}

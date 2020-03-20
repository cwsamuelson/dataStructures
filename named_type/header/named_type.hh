#ifndef __NAMED_TYPE_HH__
#define __NAMED_TYPE_HH__

//#include<utility>

namespace gsw {

template<typename T, typename parameter>
class named_type {
public:
  using value_type = T;
  using reference = T&;
  using const_ref = T const&;

private:
  value_type mValue;

public:
  named_type()
          : mValue() {
  }

  explicit
  named_type(const_ref value)
          : mValue(value) {
  }

  explicit
  named_type(T&& value)
          : mValue(std::move(value)) {
  }

  [[nodiscard]]
  reference get() {
    return mValue;
  }

  [[nodiscard]]
  const_ref get() const {
    return mValue;
  }

  [[nodiscard]]
  explicit
  operator T() const {
    return mValue;
  }

  named_type& operator=(const named_type& name_t) {
    mValue = name_t;

    return *this;
  }

  named_type& operator=(const_ref value) {
    mValue = value;

    return *this;
  }

  [[nodiscard]]
  bool operator==(const named_type& name_t) const {
    return mValue == name_t.mValue;
  }

  [[nodiscard]]
  bool operator==(const_ref value) const {
    return mValue == value;
  }
};

}

#endif

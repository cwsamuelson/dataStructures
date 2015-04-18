vector_iterator::vector_iterator(const vector_iterator& other):
  idx_(other.idx_),
  data_(other.data_){  }

vector_iterator::vector_iterator(vector_iterator::pointer ptr):
  vector_iterator(ptr, 0){  }

vector_iterator::vector_iterator(vector_iterator::pointer ptr, size_t idx):
  idx_(idx),
  data_(ptr){  }

vector_iterator& vector_iterator::operator=(const vector_iterator& rhs){
  data_ = rhs.data_;
  idx_ = rhs.idx_;
  return *this;
}

vector_iterator& vector_iterator::operator++(){
  ++idx_;
  return *this;
}

vector_iterator vector_iterator::operator++(int){
  vector_iterator tmp(*this);
  ++(*this);
  return tmp;
}

vector_iterator& vector_iterator::operator--(){
  --idx_;
  return *this;
}

vector_iterator vector_iterator::operator--(int){
  vector_iterator tmp(*this);
  --(*this);
  return tmp;
}

vector_iterator::reference vector_iterator::operator*(){
  return data_[idx_];
}

vector_iterator::pointer vector_iterator::operator->(){
  return data_ + idx_;
}

bool operator==(const vector_iterator& lhs, const vector_iterator& rhs){
  return (lhs.data_ == rhs.data_ && lhs.idx_ == rhs.idx_);
}

bool operator!=(const vector_iterator& lhs, const vector_iterator& rhs){
  return !(lhs == rhs);
}


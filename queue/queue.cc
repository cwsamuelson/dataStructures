void push(value_type data){
  que.pushBack(data);
}

void pop(){
  que.popFront();
}

reference front(){
  return que.front();
}

const_reference front() const{
  return front();
}

reference back(){
  return que.back();
}

const_reference back() const{
  return back();
}

bool isEmpty() const{
  return que.isEmpty();
}

size_t size() const{
  return que.size();
}


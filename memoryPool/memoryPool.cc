#include"memoryPool.hh"

template<class T>
T* memoryPool<T>::allocate(size_t amt){
  T* ret;
  //If the request is larger than that available, return null;
  if(amt == 0){
    return 0;
  }else if(amt > (size - inUse)){
    ret = 0;
  }else{
    //Determine where free memory exists to return;
    //If there's no memory in use, return beginning;
    if(this->slots.size() == 0){
      this->slots.push_back(slot(this->storage, this->storage + amt));
      ret = this->storage;
    }else if(this->slots.begin()->start != this->storage){
        if(this->slots.begin()->start - this->storage >= amt){
          this->slots.push_back(slot(this->storage, this->storage + amt));
          ret = this->storage;
        }
    }else{
      auto first = this->slots.begin();
      for(auto second = ++this->slots.begin(); second != this->slots.end(); ++second, ++first){
        if(second->start - first->end >= amt){
          ret = first->end;
          break;
        }
      }
      //If we get to the end of the list and there's no free space found, check the tail end;
      if((this->storage + this->size) - first->end >= amt){
        this->slots.push_back(slot(first->end, first->end+amt));
        ret = first->end;
      }
    }
    //Only re-sort when new things have been added;
    this->slots.sort();
  }

  return ret;
}

template<class T>
void memoryPool<T>::deallocate(T* ptr){
  for(auto it = this->slots.begin(); it != this->slots.end(); ++it){
    if(it->start == ptr){
      this->slots.erase(it);
      break;
    }
  }
}

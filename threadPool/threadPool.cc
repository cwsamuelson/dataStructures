
void threadPool::threadFn(){
  while(true){
    if(size() > 0){
      mtxSelf.lock();
      auto it = front();
      pop();
      mtxSelf.unlock();
      it();
    }
  }
}

threadPool::threadPool(unsigned int nThreads){
  for(unsigned int i = 0; i < nThreads; ++i){
    pool.push_back(std::thread(&threadPool::threadFn, this));
  }
}

threadPool::~threadPool(){
  for(auto it = pool.begin(); it != pool.end(); ++it){
    (*it).join();
  }
}


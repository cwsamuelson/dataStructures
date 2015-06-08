
void threadPool::threadFn(){
  while(isWorking){
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
  isWorking = true;
  for(unsigned int i = 0; i < nThreads; ++i){
    pool.push_back(std::thread(&threadPool::threadFn, this));
  }
}

threadPool::~threadPool(){
  isWorking = false;
  for(auto it = pool.begin(); it != pool.end(); ++it){
    (*it).join();
  }
}


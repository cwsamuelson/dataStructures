
void threadPool::threadFn(){
  while(isWorking){
    if(size() > 0){
      mtxSelf.lock();
      auto it = front();
      pop();
      mtxSelf.unlock();
      //if it's a valid function, run it
      //  this check prevents running invalid functions when mutex was unlucked during shutdown
      if(it.target<void()>() != 0){
        it();
      }
    }
  }
}

threadPool::threadPool(unsigned int nThreads):
  isWorking(true){
  for(unsigned int i = 0; i < nThreads; ++i){
    pool.push_back(std::thread(&threadPool::threadFn, this));
  }
}

threadPool::~threadPool(){
  isWorking = false;
  //While already locked(try_lock failed), unlock
  //  This frees the running threads, allowing them to exit
  while(!mtxSelf.try_lock()){
    mtxSelf.unlock();
  }
  //unlock from incidental locking
  mtxSelf.unlock();
  for(auto it = pool.begin(); it != pool.end(); ++it){
    (*it).join();
  }
}


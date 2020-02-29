#ifndef GALACTICSTRUCTURES_LOCKED_RESOURCE_HH
#define GALACTICSTRUCTURES_LOCKED_RESOURCE_HH

#include <mutex>
#include <memory>

namespace gsw{

template<typename T, typename M = std::mutex, template<typename> typename L = std::lock_guard>
class locked_resource{
public:
  using value_type = T;
  using resource_type = value_type;
  using ptr_type = std::shared_ptr<resource_type>;
  using mutex_type = M;
  using lock_type = L<mutex_type>;

  class proxy{
    friend class locked_resource;
    ptr_type mRef;
    lock_type mLock;

    proxy(ptr_type in, mutex_type& m)
      : mRef(in)
      , mLock(m)
    {}

  public:
    auto& operator*(){
      return *mRef;
    }

    auto operator->(){
      return mRef;
    }
  };

private:
  std::shared_ptr<resource_type> mData;
  std::mutex mMutex;

public:
  locked_resource()
    : mData(std::make_shared<resource_type>())
  {}

  template<typename ...Args>
  explicit
  locked_resource(Args... args)
    : mData(std::make_shared<resource_type>(std::forward<Args>(args)...))
  {}

  proxy get(){
    return {mData, mMutex};
  }
};

}

#endif //GALACTICSTRUCTURES_LOCKED_RESOURCE_HH

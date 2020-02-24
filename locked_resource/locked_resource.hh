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
  using mutex_type = M;
  using lock_type = L<resource_type>;

  class proxy{
    friend class locked_resource;
    std::shared_ptr<resource_type> mRef;
    lock_type mLock;

    proxy(std::shared_ptr<resource_type> in, mutex_type m)
      : mRef(in)
      , mLock(m)
    {}

  public:
    operator resource_type&(){
      return *mRef;
    }

    operator const resource_type&() const{
      return *mRef;
    }
  };

private:
  std::shared_ptr<resource_type> mData;
  std::mutex mMutex;

public:
  locked_resource() = default;

  template<typename ...Args>
  locked_resource(Args... args)
    : mData(std::make_shared<resource_type>(std::forward<Args>(args)...))
  {}

  proxy get(){
    return mData;
  }
};

}

#endif //GALACTICSTRUCTURES_LOCKED_RESOURCE_HH

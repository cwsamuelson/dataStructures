#ifndef __PREFIX_TREE_HH__
#define __PREFIX_TREE_HH__

#include<set>
#include<queue>
#include<map>
#include<functional>
#include<optional>

namespace gsw {

/*!
 * @tparam key
 * @tparam VALUE
 */
template<typename KEY, typename VALUE>
class prefix_tree {
public:
  using key_type = KEY;
  using value_type = VALUE;
  //using iterator = iter;

private:
  struct node {
    // using a map slows down processing
    // managing some kind of array may speed things up (but also increase memory footprint)
    // maybe should provide facilities to do either?
    // unordered_map might give both
    // the irony here is using a map to implement what is to be a type of map
    std::map<typename key_type::value_type, node> mChildren;
    std::optional<value_type> mData;
  };

  [[nodiscard]]
  node* seek_node(const key_type& key) {
    node* curr = &mRoot;

    for(auto ch : key) {
      if( curr->mChildren.contains( ch ) ){
        curr = &curr->mChildren.at(ch);
      } else {
        return nullptr;
      }
    }

    return curr;
  }

  [[nodiscard]]
  node const* c_seek_node(const key_type& key) const {
    node const* curr = &mRoot;

    for(auto ch : key) {
      //c++20 provides a contains facility
      //if( curr->mChildren.contains( ch ) ){
      if(curr->mChildren.count(ch) > 0) {
        curr = &curr->mChildren.at(ch);
      } else {
        return nullptr;
      }
    }

    return curr;
  }

  void explore(const key_type& key, std::function<void(node const*)> callback) const {
    std::queue<node const*> node_que;
    node const* n = c_seek_node(key);

    if(!n) {
      return;
    }

    node_que.push(n);

    while(!node_que.empty()) {
      node const* ptr = node_que.front();
      node_que.pop();

      callback(ptr);

      std::for_each(ptr->mChildren.begin(), ptr->mChildren.end(), [&](const auto& pair)
        {
          node_que.push(&pair.second);
        });
    }
  }

  node mRoot;

public:
  prefix_tree() = default;
  prefix_tree(const prefix_tree&) = default;
  prefix_tree(prefix_tree&&) noexcept = default;
  friend auto operator<=>(const prefix_tree&, const prefix_tree&) = default;

  void insert(const key_type& key, const value_type& value) {
    node* curr = &mRoot;

    for(auto ch : key) {
      curr = &curr->mChildren[ch];
    }

    curr->mData = std::make_optional<value_type>(value);
  }

  [[nodiscard]]
  bool contains(const key_type& key) const {
    auto nod = c_seek_node(key);

    return nod && nod->mData.has_value();
  }

  void erase(const key_type& key) {
    node* nod = seek_node(key);

    if(nod) {
      nod->mData.reset();
    }
  }

  [[nodiscard]]
  std::set<value_type> find(const key_type& key) const {
    std::set<value_type> results;

    explore(key, [&](node const* ptr)
      {
        if(ptr && ptr->mData.has_value()) {
          results.insert(ptr->mData.value());
        }
      });

    return results;
  }

  [[nodiscard]]
  size_t count(const key_type& key = key_type()) const {
    size_t count = 0;

    explore(key, [&](node const* ptr)
      {
        if(ptr && ptr->mData.has_value()) {
          ++count;
        }
      });

    return count;
  }

  /*value_type get
    value_type match
    iterator begin
    iterator end*/

  [[nodiscard]]
  bool empty() const {
    return mRoot.mChildren.empty();
  }

  void clear() {
    mRoot.mChildren.clear();
    mRoot.mData.reset();
  }
};

}

#endif

#ifndef SEGMENT_TREE_HH__
#define SEGMENT_TREE_HH__

#include<set>
#include<vector>
#include<array>
#include<optional>
#include<utility>

namespace gsw {

namespace detail {

template<long DIMS>
class bound {
private:
  std::array<double, DIMS> data;

public:
  bound() = default;

  bound(std::array<double, DIMS> arr)
          : data(arr) {
  }

  bound(const bound&) = default;

  bound& operator=(const bound&) = default;

  bool operator==(const bound& other) const {
    return data == other.data;
  }

  bound operator+(const bound& rhs) const {
    bound b;
    for(int i = 0; i < DIMS; ++i) {
      b.data[i] = data[i] + rhs.data[i];
    }

    return b;
  }

  bound operator/(long long rhs) const {
    bound b = *this;

    for(auto& val : b.data) {
      val /= rhs;
    }

    return b;
  }

  double& operator[](size_t idx) {
    return data[idx];
  }

  const double& operator[](size_t idx) const {
    return data[idx];
  }
};

template<typename T, long DIM, long DIMS>
class recurse_bounds {
private:
  const size_t mMax;

  std::vector<T>& mSubregions;

public:
  using location = bound<DIMS>;

  recurse_bounds(size_t max, std::vector<T>& sub_regions)
          : mMax(max)
          , mSubregions(sub_regions) {
  }

  void recur(location low, location half) {
    recurse_bounds<T, DIM - 1, DIMS> recurse(mMax, mSubregions);

    recurse.recur(low, half);

    low[DIM - 1] += half[DIM - 1];

    recurse.recur(low, half);
  }
};

template<typename T, long DIMS>
class recurse_bounds<T, 0, DIMS> {
private:
  const size_t mMax;

  std::vector<T>& mSubregions;

public:
  using location = bound<DIMS>;

  recurse_bounds(size_t max, std::vector<T>& sub_regions)
          : mMax(max)
          , mSubregions(sub_regions) {
  }

  void recur(location low, location half) {
    mSubregions.emplace_back(low, low + half, mMax);
  }
};

}

template<typename T, long DIMS>
class segment_tree {
public:
  using value_type = T;
  using location = detail::bound<DIMS>;
  using bounds = std::array<location, 2>;
  using segment = std::array<double, 3>;

  class item {
  public:
    value_type value;
    location loc;

    bool operator<(const item& other) const {
      for(int i = 0; i < DIMS; ++i) {
        if(loc[i] < other.loc[i]) {
          return true;
        }
      }
      return false;
    }

    bool operator==(const item& other) const {
      return value == other.value && loc == other.loc;
    }
  };

private:
  const size_t mMaxCount;
  std::vector<item> mData;
  std::vector<segment_tree> mSubregions;
  bounds mBounds;

  bool contains(location loc) const {
    for(unsigned int i = 0; i < DIMS; ++i) {
      if(loc[i] < mBounds[0][i] || loc[i] > mBounds[1][i]) {
        return false;
      }
    }
    return true;
  }

  void split() {
    location half = (mBounds[0] + mBounds[1]) / 2;
    detail::recurse_bounds<segment_tree, DIMS, DIMS>(mMaxCount, mSubregions).recur(mBounds[0], half);
  }

  bool sub_insert(item itm) {
    if(!mSubregions.empty()) {
      for(auto& region : mSubregions) {
        if(region.contains(itm.loc)) {
          region.insert(itm);
          return true;
        }
      }
      throw; //should never get here
    }
    return false;
  }

public:
  segment_tree(location min, location max, size_t max_count = 2)
          : mMaxCount(max_count)
          , mBounds{ min, max } {
  }

  segment_tree(const segment_tree&) = default;

  segment_tree& operator=(const segment_tree&) = default;

  void insert(item itm) {
    if(!sub_insert(itm)) {
      mData.push_back(itm);
    }

    if(mData.size() > mMaxCount) {
      split();
      for(auto data : mData) {
        sub_insert(data);
      }
      mData.clear();
    }
  }

  std::set<std::set<item>> get_groups() const {
    std::set<std::set<item>> result;

    if(!mData.empty()) {
      result.emplace(mData.begin(), mData.end());
    }

    for(auto region : mSubregions) {
      auto groups = region.get_groups();
      result.insert(groups.begin(), groups.end());
    }

    return result;
  }

  auto size() const -> decltype(mData.size()) {
    auto result = mData.size();

    for(auto region: mSubregions) {
      result += region.size();
    }

    return result;
  }

  void clear() {
    mSubregions.clear();
    mData.clear();
  }
};

template<typename T> using double_tree = segment_tree<T, 1>;
template<typename T> using quad_tree = segment_tree<T, 2>;
template<typename T> using octree = segment_tree<T, 3>;
template<typename T> using hexadecatree = segment_tree<T, 4>;

}

#endif

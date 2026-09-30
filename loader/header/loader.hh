#pragma once

#include <error_help.hh>

#include <filesystem>
#include <functional>
#include <map>
#include <optional>

namespace flp {

template<typename Type>
struct Loader {
  using Key = std::filesystem::path;
  // struct Key {
  //   std::filesystem::path path;

  //   friend
  //   auto operator<=>(const Key&, const Key&) noexcept = default;
  // };

  using Resource = std::optional<Type>;
  // struct Resource {
  //   std::optional<Type> data;
  // };

  using Storage = std::map<Key, Resource>;
  using Iterator = typename Storage::iterator;
  struct Handle {
    Loader* loader{nullptr};
    Iterator iterator;

    const Type& operator*() const {
      auto& opt = iterator->second;
      if (not opt.has_value()) {
        loader->load(iterator);
      }

      return opt.value();
    }

    Type& operator*() {
      auto& opt = iterator->second;
      if (not opt.has_value()) {
        load(iterator);
      }

      return opt.value();
    }
  };

  using LoadFunc = std::function<Type(const Key&)>;

  template<typename Function = Type(*)(const std::filesystem::path&)>
  Loader(Function&& function)
    : Loader(std::filesystem::current_path(), std::forward<Function>(function))
  {}

  // create?
  template<typename Function = Type(*)(const std::filesystem::path&)>
  Loader(const std::filesystem::path& root, Function&& function)
    // must be canonicalized for 'is_directory' to guarantee sane result - we don't care if it's a symlink
    : root_directory(canonical(root))
    , load_function(std::forward<Function>(function)) {
    VERIFY(exists(root_directory), "Requested loader root directory({}) doesn't exist.", root_directory.string());
    VERIFY(is_directory(root_directory), "Requested loader root path({}) isn't a directory.", root_directory.string());
  }

  Handle load(std::filesystem::path path) {
    if (storage.contains(path)) {
      return {this, storage.find(path)};
    }

    if (path.is_relative()) {
      path = canonical(root_directory / path);
    }

    VERIFY(exists(path), "Requested file({}) doesn't exist.", path.string());
    VERIFY(is_regular_file(path), "Requested path({}) isn't a regular file", path.string());

    const auto [iterator, success] = storage.emplace(Key{std::move(path)}, Resource{});
    // VERIFY(success, ""); // ?
    return {this, iterator};
  }

  Handle get(const std::filesystem::path& path) {
    return {this, storage.find(path)};
  }

private:
  void load(Iterator iterator) {
    iterator->second = load_function(iterator->first);
  }

  std::filesystem::path root_directory;
  LoadFunc load_function;
  Storage storage;
};

} // namespace flp

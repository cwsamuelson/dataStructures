#pragma once

#include <error_help.hh>

#include <filesystem>
#include <functional>
#include <map>
#include <optional>
#include <set>

namespace flp {

template<typename Type>
struct Loader {
  using Resource = std::optional<Type>;
  using ResourceKey = std::filesystem::path;
  using AssetPath = std::filesystem::path; // actual path
  using LoadFunc = std::function<Type(const AssetPath&)>;

  struct Metadata {
    Resource resource;
    ResourceKey rkey;
    AssetPath path;

    friend
    auto operator<=>(const Metadata&, const Metadata&) noexcept = default;
  };

  using Storage = std::set<Metadata>;
  using Iterator = typename Storage::iterator;

  struct Handle {
    Loader* loader{nullptr};
    Iterator iterator;

    const Type& operator*() const {
      auto& res = iterator->resource;
      if (not res.has_value()) {
        loader->load(iterator);
      }

      return res.value();
    }

    Type& operator*() {
      auto& res = iterator->resource;
      if (not res.has_value()) {
        load(iterator);
      }

      return res.value();
    }
  };

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

  Handle load(AssetPath path) {
    if (file_keys.contains(path)) {
      return {this, *file_keys.find(path)};
    }

    if (path.is_relative()) {
      path = canonical(root_directory / path);
    }

    VERIFY(exists(path), "Requested file({}) doesn't exist.", path.string());
    VERIFY(is_regular_file(path), "Requested path({}) isn't a regular file", path.string());

    const ResourceKey rkey = relative(path, root_directory);
    const auto [iterator, success] = storage.emplace({
        .resource = std::nullopt,
        .rkey = rkey,
        .path = path,
      }
    );
    file_keys.insert(path);
    asset_keys.insert(rkey);

    // VERIFY(success, ""); // ?
    return {this, iterator};
  }

  Handle get(const AssetPath& path) {
    return {this, *file_keys.find(path)};
  }

private:
  void load(Iterator iterator) {
    iterator->second = load_function(iterator->first);
  }

  std::filesystem::path root_directory;
  LoadFunc load_function;

  std::map<ResourceKey, Iterator> asset_keys;
  std::map<AssetPath, Iterator> file_keys;
  Storage storage;
};

} // namespace flp

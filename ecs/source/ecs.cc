#include <ecs.hh>

namespace flp {

Registry::EntityID Registry::create() {
  static size_t counter{};
  return counter++;
}

std::vector<Registry::EntityID> Registry::create(const size_t count) {
  std::vector<EntityID> result;

  for(size_t i = 0; i < count; i++) {
    result.push_back(create());
  }

  return result;
}

void Registry::destroy(const EntityID entity_id) {
  clear(entity_id);
  valid_entities.erase(entity_id);
}

bool Registry::valid(const EntityID entity_id) {
  return valid_entities.contains(entity_id);
}

Registry::EntityID Registry::current(const EntityID entity_id) {
  return {};
}

void Registry::clear() {
  component_maps.clear();
  valid_entities.clear();
}

void Registry::clear(const EntityID entity_id) {
  for (auto&& [component_hash, component_map] : component_maps) {
    component_map.erase(entity_id);
  }
}

}

#include <ecs.hh>

namespace flp {

Registry::EntityID Registry::create() {
  return {};
}

std::vector<Registry::EntityID> Registry::create(const size_t count) {
  std::vector<EntityID> result;

  for(size_t i = 0; i < count; i++) {
    result.push_back(create());
  }

  return result;
}

void Registry::destroy(const EntityID entity_id) {
}

bool Registry::valid(const EntityID entity_id) {
  return false;
}

Registry::EntityID Registry::current(const EntityID entity_id) {
  return {};
}

void Registry::clear() {
  component_map.clear();
}

void Registry::clear(const EntityID entity_id) {
}

}

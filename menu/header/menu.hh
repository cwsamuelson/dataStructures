#pragma once

#include <ranges>
#include <string>
#include <vector>
#include <map>

namespace flp {

struct Menu {
  Menu(const std::string_view prmp)
    : prompt(prmp)
  {}

  Menu(const std::string_view prmp, std::map<size_t, Menu> menus)
    : prompt(prmp)
    , sub_menus(std::move(menus))
  {}

  Menu(const std::string_view prmp, std::vector<Menu> menus)
    : prompt(prmp)
    , sub_menus(std::from_range, menus | std::views::enumerate)
  {}

  std::string prompt;
  std::map<size_t, Menu> sub_menus;
};

struct MenuManager {
  Menu* current{nullptr};

  void select(const size_t selection) {
    current = &current->sub_menus.at(selection);
  }

private:
  friend struct Menu;

  MenuManager() = delete;
  MenuManager(const MenuManager&) noexcept = default;
  MenuManager(MenuManager&&) noexcept = default;
  MenuManager& operator=(const MenuManager&) = default;
  MenuManager& operator=(MenuManager&&) noexcept = default;
  ~MenuManager() noexcept = default;

  MenuManager(Menu& menu)
    : current(&menu)
  {}
};

} // namespace flp

#include <canvas/canvas.hh>

#include <print>
#include <ranges>

constexpr flp::ColorRGBA32 black{0, 0, 0, 0};
constexpr flp::ColorRGBA32 white{1, 1, 1, 0};

void Draw(const flp::Canvas<>& canvas) {
  for (const auto& line : canvas.canvas) {
    std::println("{}", line | std::views::transform([&](const auto& value) {
      return value == black ? 'x' : (value == white ? '#' : '?');
    }) | std::ranges::to<std::string>());
  }

  std::println("");
}

int main() {
  flp::Canvas<> canvas(10, 10);

  canvas.clear(black);
  canvas.draw({1, 1}, white);
  canvas.draw_line({}, {}, white);
  canvas.draw_line({0, 9}, {10, 9}, white);
  canvas.draw_line({1, 8}, {9, 8}, white);

  Draw(canvas);

  canvas.draw_triangle({5, 0}, {0, 9}, {9, 9}, white);

  Draw(canvas);

  canvas.fill_triangle({5, 0}, {0, 9}, {9, 9}, white);

  Draw(canvas);
}

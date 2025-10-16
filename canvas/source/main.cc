#include <canvas.hh>

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
}

int main() {
  flp::Canvas<> canvas(10, 10);

  canvas.Clear(black);
  canvas.Draw({1, 1}, white);
  canvas.DrawLine({}, {}, white);
  canvas.DrawLine({0, 9}, {10, 9}, white);

  Draw(canvas);

  canvas.DrawTriangle({5, 0}, {0, 9}, {10, 9}, white);

  Draw(canvas);

  canvas.FillTriangle({5, 0}, {0, 9}, {10, 9}, white);

  Draw(canvas);
}

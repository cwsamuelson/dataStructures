#pragma once

#include <error_help.hh>

#include <cmath>
#include <cstdint>
#include <format>
#include <ranges>
#include <string>
#include <vector>

namespace flp {

template<typename Type>
struct Position2 {
  Type x;
  Type y;
};

template<typename Type>
struct Size2 {
  Type width;
  Type height;
};

template<typename Type>
struct vec2 {
  Type x;
  Type y;
};

// math with constant
template<typename Type>
Position2<Type> operator+(const Position2<Type>& position, const Type& constant) {
  return { position.x + constant, position.y + constant };
}

template<typename Type>
Position2<Type> operator-(const Position2<Type>& position, const Type& constant) {
  return { position.x - constant, position.y - constant };
}

template<typename Type>
Position2<Type> operator*(const Position2<Type>& position, const Type& constant) {
  return { position.x * constant, position.y * constant };
}

template<typename Type>
Position2<Type> operator/(const Position2<Type>& position, const Type& constant) {
  return { position.x / constant, position.y / constant };
}

// math with self

template<typename Type>
vec2<Type> operator+(const Position2<Type>& start, const Position2<Type>& stop) {
  return { start.x + stop.x, start.y + stop.y };
}

template<typename Type>
vec2<Type> operator-(const Position2<Type>& start, const Position2<Type>& stop) {
  return { start.x - stop.x, start.y - stop.y };
}

// math with vec

template<typename Type>
Position2<Type> operator+(const Position2<Type>& position, const vec2<Type>& offset) {
  return { position.x + offset.x, position.y + offset.y };
}

template<typename Type>
Position2<Type> operator-(const Position2<Type>& position, const vec2<Type>& offset) {
  return { position.x - offset.x, position.y - offset.y };
}

// math with size
template<typename Type>
Position2<Type> operator+(const Position2<Type>& position, const Size2<Type>& size) {
  return { position.x + size.width, position.y + size.height };
}

template<typename Type>
Position2<Type> operator-(const Position2<Type>& position, const Size2<Type>& size) {
  return { position.x - size.width, position.y - size.height };
}

struct ColorRGBA32 {
  union {
    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    };

    struct {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      uint8_t alpha;
    };

    uint32_t value;
  };

  constexpr
  ColorRGBA32(const uint8_t R, const uint8_t G, const uint8_t B, const uint8_t A)
    : red(R)
    , green(G)
    , blue(B)
    , alpha(A)
  {}

  constexpr
  ColorRGBA32(const uint32_t V)
    : value(V)
  {}

  friend auto operator<=>(const ColorRGBA32& lhs, const ColorRGBA32& rhs) noexcept {
    return lhs.value <=> rhs.value;
  }
  friend bool operator==(const ColorRGBA32& lhs, const ColorRGBA32& rhs) noexcept {
    return lhs.value == rhs.value;
  }
};

using Color1 = bool;

template<typename Color = ColorRGBA32>
struct Canvas {
  using Position = Position2<size_t>;
  using Vertex = Position;
  using Size = Size2<size_t>;

  std::vector<std::vector<Color>> canvas;

  Canvas(Size size);
  Canvas(size_t width, size_t height);
  ~Canvas();

  void clear(Color color);

  // 0D
  void draw(const Position&, Color color);
  // 1D
  void draw_line(const Position& start, const Position& stop, Color color);
  void draw_line(const std::vector<Position>& points, Color color);

  // 2D
  // 'draw'
  void draw_circle(const Position& center, float radius, Color color);
  void draw_rectangle(const Position& top_left, const Position& bot_right, Color color);
  void draw_rectangle(const Position& top_left, const Size& size, Color color);
  // DrawQuad?
  void draw_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color);
  void draw_text(const Position& position, const std::string& text, Color color);
  // DrawString?
  void draw_polygon(const std::vector<Position>& points, Color color);

  // placeholder
  using Polynomial = int;
  void draw_curve(const Polynomial);

  // 'fill'
  void fill_circle(const Position& center, float radius, Color color);
  void fill_rectangle(const Position& top_left, const Position& bot_right, Color color);
  void fill_rectangle(const Position& top_left, const Size& size, Color color);
  // FillQuad?
  void fill_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color);
  void fill_text(const Position& position, const std::string& text, Color color);
  // FillString?
  void fill_polygon(const std::vector<Position>& points, Color color);

  // sprite?
  // decal?

private:
  void fill_flat_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color);
};

template<typename Color>
Canvas<Color>::Canvas(Size size)
  : Canvas(size.width, size.height)
{}

template<typename Color>
Canvas<Color>::Canvas(const size_t width, const size_t height)
  : canvas(height, std::vector<Color>(width, {uint32_t{0}}))
{}

template<typename Color>
Canvas<Color>::~Canvas() = default;

// - DRAW

template<typename Color>
void Canvas<Color>::clear(const Color color) {
  for (auto& row : canvas) {
    for (auto& value : row) {
      value = color;
    }
  }
}

// -- 0D
template<typename Color>
void Canvas<Color>::draw(const Position& position, Color color) {
  canvas.at(position.y).at(position.x) = color;
}

// -- 1D
template<typename Color>
void Canvas<Color>::draw_line(const Position& start, const Position& stop, Color color) {
  const auto delta = stop - start;

  // vertical line
  if (delta.x == 0) {
    // jk, just a pixel
    if (delta.y == 0) {
      draw(start, color);
      return;
    }

    for (auto cursor = start.y; cursor < stop.y; ++cursor) {
      draw({delta.x, cursor}, color);
    }

    return;
  }

  const float slope = delta.y / delta.x;

  // this line drawing algorithm can have gaps
  // In particular with sufficiently steep lines
  for (auto cursor = start.x; cursor < stop.x; ++cursor) {
    draw({cursor, start.y + (cursor * slope)}, color);
  }
}

template<typename Color>
void Canvas<Color>::draw_line(const std::vector<Position>& points, Color color) {
  for (const auto&& span : points | std::views::slide(2)) {
    draw_line(span[0], span[1], color);
  }
}

// -- 2D

template<typename Color>
void Canvas<Color>::draw_circle(const Position& center, float radius, Color color) {
  // bad approximation :)
  draw(center, color);

  draw({center.x + radius, center.y}, color);
  draw({center.x - radius, center.y}, color);
  draw({center.x, center.y + radius}, color);
  draw({center.x, center.y - radius}, color);
}

template<typename Color>
void Canvas<Color>::draw_rectangle(const Position& top_left, const Position& bot_right, Color color) {
  draw_line(top_left, {bot_right.x, top_left.y}, color); // top
  draw_line(top_left, {top_left.x, bot_right.y}, color); // left
  draw_line({bot_right.x, top_left.y}, bot_right, color); // right
  draw_line({top_left.x, bot_right.y}, bot_right, color); // bottom
}

template<typename Color>
void Canvas<Color>::draw_rectangle(const Position& top_left, const Size& size, Color color) {
  draw_rectangle(top_left, top_left + size, color);
}

//   Canvas::DrawQuad {
//   }

template<typename Color>
void Canvas<Color>::draw_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color) {
  draw_polygon({v1, v2, v3}, color);
}

template<typename Color>
void Canvas<Color>::draw_text(const Position& position, const std::string& text, Color color) {
}

//   Canvas<Color>::DrawString {
//   }

template<typename Color>
void Canvas<Color>::draw_polygon(const std::vector<Position>& points, Color color) {
  draw_line(points, color);
  draw_line(points.back(), points.front(), color);
}

template<typename Color>
void Canvas<Color>::draw_curve(const Polynomial) {
}

// - FILL

template<typename Color>
void Canvas<Color>::fill_circle(const Position& center, float radius, Color color) {
  // bad approximation :)
  draw_line({center.x - radius, center.y}, {center.x + radius, center.y}, color);
  draw_line({center.x, center.y - radius}, {center.x, center.y + radius}, color);
}

template<typename Color>
void Canvas<Color>::fill_rectangle(const Position& top_left, const Position& bot_right, Color color) {
  for (size_t y = top_left.y; y < bot_right.y; ++y) {
    draw_line({top_left.x, y}, {bot_right.x, y}, color);
  }
}

template<typename Color>
void Canvas<Color>::fill_rectangle(const Position& top_left, const Size& size, Color color) {
  fill_rectangle(top_left, top_left + size, color);
}

//   Canvas<Color>::FillQuad {
//   }

template<typename Color>
void Canvas<Color>::fill_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color) {
  // to guarantee clean drawing, horizontal lines will be preferred
  // otherwise any inconsistency in the algorithm to draw sloped lines will
  // manifest in ugly triangles (likely with holes/gaps etc)

  // to do this, triangles are checked for a flat/horizontal edge

  if (v1.y == v2.y) {
    fill_flat_triangle(v1, v2, v3, color);
    return;
  } else if (v1.y == v3.y) {
    fill_flat_triangle(v1, v3, v2, color);
    return;
  } else if (v2.y == v3.y) {
    fill_flat_triangle(v2, v3, v1, color);
    return;
  }

  // if no flat edges are found, the triangle is split into 2 triangles with a shared flat edge
  // then they will be drawn separately

  // find the vertically middle vertex, and use that as the basis for the shared flat edge
  const auto [low, high] = std::minmax({v1.y, v2.y, v3.y});

  // high, low, middle, 'synthetic'
  Vertex vh;
  Vertex vl;
  Vertex vm;
  Vertex vs;

  //! @TODO this is really just a sort, right?
  if (v1.y != low and v1.y != high) {
    vm = v1;

    if (v2.y == high) {
      vh = v2;
      vl = v3;
    } else if (v3.y == high) {
      vh = v3;
      vl = v2;
    } else {
      THROW("");
    }
  } else if (v2.y != low and v2.y != high) {
    vm = v2;

    if (v1.y == high) {
      vh = v1;
      vl = v3;
    } else if (v3.y == high) {
      vh = v3;
      vl = v1;
    } else {
      THROW("");
    }
  } else if (v3.y != low and v3.y != high) {
    vm = v3;

    if (v1.y == high) {
      vh = v1;
      vl = v2;
    } else if (v2.y == high) {
      vh = v2;
      vl = v1;
    } else {
      THROW("");
    }
  } else {
    THROW("");
  }

  const float rslope = (vh.x - vl.x) / (vh.y - vl.y);

  // once the middle vertex is identified, the 'synthetic' point must be created.
  // it will have the same height as the middle point, but it's x-position will be dependent on the slope of the other 2 points
  vs.y = vm.y;
  vs.x = vh.x + ((vm.y - vh.y) * rslope);

  // upper triangle
  fill_flat_triangle(vm, vs, vh, color);
  // lower triangle
  fill_flat_triangle(vm, vs, vl, color);
}

template<typename Color>
void Canvas<Color>::fill_text(const Position& position, const std::string& text, Color color) {
}

//   Canvas<Color>::FillString {
//   }

template<typename Color>
void Canvas<Color>::fill_polygon(const std::vector<Position>& points, Color color) {
  // tesselate, then `DrawTringle`s.
}

// the first 2 vertices will always be the 'flat' edge
template<typename Color>
void Canvas<Color>::fill_flat_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color) {
  VERIFY(v1.y == v2.y, "Invalid arguments to draw 'flat' triangle.");

  // 'reverse' slope.  how much change in x per change in y
  const float rslope1 =
    (static_cast<float>(v3.x) - static_cast<float>(v1.x))
    /
    (static_cast<float>(v3.y) - static_cast<float>(v1.y));
  const float rslope2 =
    (static_cast<float>(v3.x) - static_cast<float>(v2.x))
    /
    (static_cast<float>(v3.y) - static_cast<float>(v2.y));

  // increasing vs decreasing

  using C = decltype(v1.x);
  const auto inc = std::signbit(v3.y - v1.y) ? 1 : -1;

  float x1 = v1.x;
  float x2 = v2.x;
  for (C y = v1.y; y != v3.y; y += inc) {
    draw_line({x1, y}, {x2, y}, color);

    x1 += rslope2;
    x2 += rslope1;
  }
}

}

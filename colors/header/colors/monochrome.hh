#pragma once

namespace flp::Colors {

template<typename Type = float>
struct Monochrome {
  union {
    Type red;
    Type green;
    Type blue;
    Type alpha;

    Type r;
    Type g;
    Type b;
    Type a;

    Type t;
    Type u;
    Type v;
    Type w;

    Type shade;
    Type value;
    Type bytes[4];
  };
};

}

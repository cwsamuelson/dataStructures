#pragma once

namespace flp::Random {

template<typename Type>
concept Source = requires(Type source) {
};

template<typename Type>
concept Engine = requires(Type engine) {
};

template<typename Type>
concept Distribution = requires(Type distribution) {
};

}

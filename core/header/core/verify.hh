#pragma once

#include <stdexcept>

#define VERIFY(condition, ...) \
  if (not (condition)) { \
    throw std::runtime_error(#condition); \
  }

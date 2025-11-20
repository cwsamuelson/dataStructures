#pragma once

#define PASTER(x, y) x ## _ ## y
#define BUILD_NAME(base, suffix) PASTER(base, suffix)

#define UNIQUE_NAME_FROM_LINE(name) BUILD_NAME(name, __LINE__)

#define UNIQUE_NAME(name) UNIQUE_NAME_FROM_LINE(name)

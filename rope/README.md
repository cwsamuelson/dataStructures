It's worth noting, that rope leaf size should use hysteresis (i.e. stay within
\[min, max]), to help reduce the number of split/join/reallocate operations.
Guess from my intuition: \[3072, 4096]

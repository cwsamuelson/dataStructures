Immutable
=========

Immutable Containers.

```
flp::immutable::Vector<int> vector{ 0, 1, 2, 3 };
XXX vector = flp::immutable::Vector<int>{ 4, 5, 6, 7 };
vector.push_back(4);
vector.size() != 4;

auto new_vector = vector.push_back(4);
new_vector.size() == 4;
```

ETC...

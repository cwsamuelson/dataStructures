The idea is to enable something like Python keyword arguments.  Python uses a
`dict`, but the C++ equivalent would be `std::map<std::string, std::any>`.  This
seems perhaps heavy and slow.  Using tag types, along with some kind of integral
typeID to key into a `std::unordered_map` may be significantly faster.  This is
convenient for when there are many possible configuration parameter combinations.

```C++
void foo(const TaggedArgumentSet& args) {
    const auto arg1 = args.at(FooArg1);
    ...
}

void foo() {
    foo({});
}
```

```C++
foo();
foo(...);
```
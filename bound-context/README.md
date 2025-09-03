# The Idea
A bound context is essentially a scoped region defining when a given bound object is active.  This comes from APIs such as OpenGL that are stateful, and require one to first bind a buffer, and then send data to the bound buffer.  These actions seem oddly disjointed, and in a sense at risk of the state being corrupted.  While I have no doubt this rarely or never happens, it certainly makes the interface less clear.

My hope is to establish a pattern by which this can be made clearer to a new developer, while not modifying the original API directly.

# Example
Python has something similar with `with`.
```Python
with open('file/path.txt', 'r') as file:
  file.read(...)
```

This can't be achieved so succinctly, but maybe with callbacks.
```C++
template<typename Type>
concept Unbindable = requires(Type resource) {
  { resource.unbind() };
};

template<typename Type>
concept Bindable = requires(Type resource) {
  { resource.bind() } -> Unbindable;
};

template<typename Functor, typename ...Resources>
With(Resources&& ...resources, Functor&& functor) {
  auto ...bound = ((resources.bind()), ...);
  functor(bound...);
  ((bound.unbind()), ...);
}

Bindable auto bindable_resource = ...;
With(bindable_resource, [](auto& handle_to_bound_resource){
});
With(bindable_resource1, bindable_resource2, bindable_resource3, [](auto& handle1, auto& handle2, auto& handle3){
});
```
Where `With` would bind all given resources, call the callback with the results as argument, and unbind them.

This way a bound resource has a different interface.  This allows wrappers to not have to bind resources every time it is modified, just to ensure the correct resource is active before making modifications.  Doing so incurs many extraneous binds.

If those actions are not available on the base resource, but are available on a bound resource, then re-binding isn't necessary!

# Constraints
Of course the idea of 'only one texture can be bound to this texture slot at a time' isn't expressed in the shown model, which is a valuable to necessary feature.
An implementation of a bindable resources will likely want the ability to track and manage other constraints etc as well.
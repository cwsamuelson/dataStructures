Scheduler Design
================

## Design decisions
The task runner handle could be several different things.  It's primary purpose
is to be an entry point to the client's task.  The simplest form of this is a
function.  But given the abstract nature of the client, polymorphism is also an
intuitive answer.  Making most basic answers:
1. `void()`
2. `std::function<void()>`
3. Polymorphic base class

## Factors
In order to discuss the determined alternatives, some things may need some
definition/discussion in order to make their 'pro' or 'con'-ness clear.

### Polymorphism
In general, I consider polymorphism to be an anti-pattern, excluding certain
use-cases that essentially require it (plugins loading dynamic objects).  While
'object-oriented' programming is promoted in academic settings, and is very easy
to reason about, it also promotes what I call 'class-oriented' design and
architecture, much like the Java, .NET, or QT standard support libraries.  While
very useful tools, these libraries tend to have deep class hierarchies, and
force the client to insert themselves into the hierarchy in order to integrate
properly, which also makes it harder to integrate external libraries when they
weren't designed for that particular framework.  This should be considered the
likely case.

Besides the architectural implications, one must consider cache cohesion.  The
rule of thumb I use is that any pointer dereference must be assumed to be a
cache miss.  Remember that a cache miss is expensive, the OS must interject,
swap pages in memory, then your program will be rescheduled later.  While one's
objective isn't necessarily only performance, when many polymorphic objects are
in play, resolving the memory pages for every single one can be costly since
their arrangement in memory may not correspond to the access patterns.

Point being polymorphism can incur:
- Obnoxious client design patterns
- Poor memory cohesion
- Otherwise unnecessary cache thrashing

The memory issues can largely be corrected using a well-chosen memory allocator.
While a great argument, this requires smart decisions from the client.  If
you're expecting the client to make smart decisions, they likely don't need your
library to begin with; they're smart, and will implement this feature smarter
than you.

On the other hand, providing mechanisms to make smarter decisions for their
specific domain provides a lot of flexibility.

### ABI
Application Binary Interface (ABI) is the binary interface used to communicate
between applications or between an application and the OS, etc.  The C++
standard has gone to great lengths to not break ABI due to the problems it can
cause.  ABI problems can be insidious and difficult to track.

For a virtual base class, changing the functions that are virtual, and thereby
changing the content of the vtable, the ABI is changed.  If all code that will
use said ABI is re-built, this isn't a problem, but linking code built with one
ABI version with one using a different ABI version may fail, or worse succeed,
and hopefully generate clear errors at runtime, tho the latter is unlikely.

## Options
I'll break down each choice and provide pros and cons.

### `void()`
Formally known as `void(*)()`, the function pointer is straight-forward, and
pretty easy, with low overhead.  This is what I've seen used in my experience as
an embedded developer.

Pros:
- Simple interface
- Minimal overhead
- C-API compliant
Cons:
- No flexibility for the client
- Essentially relies on global variables for client state
  - Doesn't hurt the scheduler itself any, but sub-optimal

### `std::function<void()>`
Functional programming is great, and `std::function` provides a simple and
straight-forward way to type-erasure, providing the client maximum flexibility.

Pros:
- Highly flexible
  - Works with anything that can be called as a function
  - This essentially allows the client to have any interface they want
- Naturally supports `void()` features for the client
Cons:
- Overhead of a polymorphic base class
  - Type-erasure typically uses polymorphism in the implementation
- Actual overhead not strictly known, due to `std` library implementation

### Polymorphic base `Task`
```c++ 
  struct Task {
    // Or something like this
    virtual void run() = 0;
  };
```

Pros:
- Overhead is primarily controlled by the client
  - Assuming `struct Task` with one `virtual` function, the `vtable` will
    have a fairly minimal size
- The compiler may be able to optimize out the polymorphism
- State tracking is clearly handled for the client in the derived class
Cons:
- Restricts against C-API
- Forces some amount of interface on the client
- Overhead of polymophism
- Updates to the base class for the purpose of the scheduler will incur
  ABI-compat concerns/considerations

### Templates
Surprise alternative: templates!
Templates can combine flexibility of type-erasure and polymorphic base classes
with the low overhead of a function pointer.

Pros:
- Very flexible
- Simple interface
- Low overhead
- C-API compliant
Cons:
- All tasks must have the same type
- More difficult in scheduler implementation to handle design corner cases

```c++
template<template<typename> typename Container, typename Runner>
struct Scheduler {
    Container<Runner> tasks;
};

Scheduler<std::vector, std::function<void()>> vec_function;
```
In this example, the user selected `std::vector` to store tasks, and to use
`std::function` for the runner.  So long as `Container` is `iterable`, and
`Runner` is `invocable`, the scheduler should be able to manage everything
successfully.

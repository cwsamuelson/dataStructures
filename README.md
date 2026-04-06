Galactic Structures
===================
This is an umbrella project for various code/tools/utilities I have thought of, or decided to replicate for practice.
Each subproject/directory will have its own more detailed README to cover its specific contents.

## Features
- const correctness
- exception safety
- conditional noexcept
- allocator awareness
- context allocator awareness
- fancy pointers
- iterators

## Tools
- [ ] accessor
- [ ] algorithms
- [ ] aligned-buffer
- [ ] allocators
- [ ] array
- [ ] colony/hive
- [ ] configuration
- [ ] context system
- [ ] 'core'
- [ ] date-time
- [ ] ECS
- [ ] enumerator
- [ ] equation
- [ ] event-handler
- [ ] function
- [ ] future
- [ ] graph
- [ ] hash-map
- [ ] map
- [ ] hive
- [ ] json
- [ ] lambda
- [ ] lifetime-tracking
- [ ] list
- [ ] locked-resource
- [ ] logger
- [ ] logic
- [ ] long
- [ ] matrix
- [ ] memory
- [ ] menu
- [ ] named-point
- [ ] named-type
- [ ] normal-iterator
- [ ] operators
- [ ] optional
- [ ] pager
- [ ] polynomial
- [ ] prefix-tree
- [ ] producer-consumer
- [ ] profiler
- [ ] range
- [ ] ranged-integers
- [ ] ratio
- [ ] reference_wrapper
- [ ] remote
- [ ] scheduler
- [ ] segment_tree
- [ ] skip-list
- [ ] sparse-set
- [ ] 'std::hive'
- [ ] spline
- [ ] string
- [ ] stringify
- [ ] threadPool
- [ ] timer
- [ ] traits
- [ ] tuple
- [ ] units
- [ ] vector
- [ ] versioning

## Goals

The primary function for this project for me is practice of varying kinds. It is also a useful collection of 'previous
art' for myself that I can pull from when working on other things. I use this to implement 'normal' things like std::
vector, and create new things like units (at the time I came up with the idea and original implementation, I had no idea
boost::units existed). Both things exercise my skill as a programmer and designer in different ways. Due to the
sometimes 'experimental' nature of what I'm working on and thinking about, code quality does not always meet my own
standards. It is my goal that eventually it will, but given the often necessarily WIP nature of many of this code,
nothing can be guaranteed. Improvement changes and ideas are welcome!

## TODO
- Create subproject READMEs. I'd like them to be reasonably good quality, so this will take time and focus. It also
  implies some level of completeness of the piece it documents, which many of these are certainly not.
- Add any other
  useful '[community health files](https://github.com/orgs/community/discussions/86658#discussioncomment-9116451)'
- Add project badges
- Find and leverage the open source guidelines

## Code organization
WIP

## File organization
WIP

## Namespace
Currently everything exists under the `flp` namespace.  This stands for 'Four Light Productions', and is a reference to the Star Trek episode 'Chain of Command'.  It represents integrity and truth.  Since I use this code as a reference/source of truth frequently, it seems appropriate.

Alternatives I've considered:
- cws
  - CodeWright's Standard
- lcrs
  - Low-level C++ Reference Suite

## Contributors

At this time I am the only contributor. Feel free to provide a PR or issue with ideas, changes or fixes!

## Copyright

© 2013-2025 Chris Samuelson. All rights reserved.

## [Licensing](https://choosealicense.com/licenses/gpl-3.0/)

This project is licensed under the [GPLv3](https://www.gnu.org/licenses/gpl-3.0-standalone.html).

Remember this requires attribution.

If you are interested in using this code under a different license agreement, please feel free to reach out to me; I am
open to discussing alternative agreements on a case-by-case basis.

[LGPL](https://choosealicense.com/licenses/lgpl-3.0/), [MIT](https://choosealicense.com/licenses/mit/),
and [Apache2.0](https://choosealicense.com/licenses/apache-2.0/) licenses are reasonable alternatives, but must be
negotiated with me directly.

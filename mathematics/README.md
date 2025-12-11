The idea here is to construct a library of mathematical pieces.  Eventually building up to more abstract and complex things.  While not always achievable, the kind of things I'm pushing towards is to make it such that if it builds, it's correct.  This will likely be much harder than it sounds, but I'll use it as my reference to find my design solution.

## Representation Agnostic
Importantly it will express everything in a way that is agnostic to how the ideas are represented.  A vector space is not intrinsically densely or sparsely packed, but instead is defined by a set of operations done on/with/in it.  Equally don't assume any elements are numbers/numeric in any way.  This will become especially important when approaching group theory.

## Start from the bottom
- Equality/ordering
- Sets and mappings
- Algebraic structures
- Numbers
- Functions
- Errors
- Higher structures

### Equality/ordering
Much of mathematics depends on the minimum of comparing objects to be the same, and sometimes the ability to order them.
### Sets and mappings
Finite sets, maps and relations?

### Algebraic structures
- Semigroup
- Monoid
- Group
- Ring
- Field
- Vector space
- etc

### Numbers
In order to restrain from a definition of what a number "IS", these will likely be additional traits on top of the algebraic structures.  This makes for a more extensible structure.
- Integers
- Rationals
- Reals
- Complex

### Functions
- Explicit functions (closures)
- Symbolic functions (AST-based)
- Composition
- Domains/codomains

Symbolic functions (expression templated?) will likely be necessary to do analysis on the function itself, and solve problems analytically.

### Errors
Some operations are mathematically meaningless or otherwise invalid.  This is somewhat tricky because sometimes that's allowed or expected, or a residual property after some operation is completed, and sometimes it's an indicator that something is fundamentally wrong.
Across the board this will be handled using exceptions.  A small handful of exception types might be useful in order to distinguish what happened, and whether it's truly an error.
Of course this raises the red flag that maybe they shouldn't be handled as exceptions, and instead error codes that are checked, since it may likely be part of 'normal' control flow.
- Division by zero
- Non-invertible matrices
- Undefined operations

### Higher structures
- Vector spaces
- Matrices
- Polynomials
- Calculus
- Symbolic manipulation

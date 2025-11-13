https://www.pcg-random.org/posts/bounded-rands.html

## Source
Serves as a 'uniform random bit generator'.  May or may not have state, and may or may not be deterministic.  Intended to be 'true random'; any pseudo-random source should probably be an engine.

## Engine
Has state, and acts as a pseudo-random number generator, taking a seed as its initial entropy source.  Importantly still uniformly generates numbers.

## Distribution
Distinctly non-necessarily uniform.

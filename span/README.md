MD-Span for multidimensional memory locality.
- Hilbert Curve
- Z-Order Curve (Morton Curve)

I've previously pondered the problem of memory/cache locality when accessing an
image or even a higher dimensional structure.  Apparently graphics cards do this,
typically use Z-Order curves for this already.  Hilbert curves can give better
locality characteristics, but Z-Order Curves have better performance.

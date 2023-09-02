# SciPP - [C++] A header-only scientific library


SciPP is a library that aims to give a range of optimized tools commonly used in every kind of applications, from image processing to scientific simulation through audio processing. The tools implemented shall not overlap with tools already present in the standard library, and the library shall stay simple to include in projects and simple to use.

This is why the library is built following three rules:
- No dependency.
- No parallel computing inside the library (but the whole library is thread safe).
- No GPU use.

Furthermore, the library is and shall remains a header-only library.


SciPP includes, amongst others:
- "Number types" not directly implemented in the standard library : big integers, quaternions, fractions, etc.
- Classes for linear algebra - tensors, matrices, vectors - for many kinds of use : sparse, dense, of static sizes, etc.
- Graph theory tools : A graph class that implements basic operations, pathfinding algorithms, etc.


## Examples

Real-time simulation of ocean surface with Phillips waves (J.Tessendorf, Simulating Ocean Water, 2001):

https://user-images.githubusercontent.com/13711225/215013944-7ea32ac7-5bc0-415d-b0ab-40a24f519d7a.mp4

Numerical solving of Navier-Stokes equations:

https://user-images.githubusercontent.com/13711225/215013924-cf363fdc-6b37-46d6-8d9e-24c383b3227b.mp4

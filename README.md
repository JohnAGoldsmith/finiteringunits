# finiteringunits
[I haven't finished this, but it's working provisionally.]

This is a Qt 5 C++ program that provides a graphic representation of the units in Z/N. 
A unit is a number with a multiplicative inverse. If N is prime, all n < N are units.
If N is composite, all n which do not share a prime factor with N are units.
If N is prime, then the multiplicative ring Z/N has N-1 elements, and N-1 is composite,
and has interesting structure.
There are many interesting symmetries that emerge from looking at the graphical representation.
This is a rewriting of a program I wrote in 2000 in MS VC. The color 
shows the "order" of the inverse: i.e.,  
If n has an inverse k in Z/N, then n * k = 1 mod N, 
that is, n * k = AN + 1. A is the order of n.

# README

`gmp.c` implements the extended Euclidean algorithm and compare its result with the gcd function `mpz_gcdext` provided by GMP library.

The program generates two random numbers every time, and computes their gcd with two methods and compares the results. Since the random state algorithm initialize `state` with the same value each time, `time()` is introduced to enable randomness of the two large numbers.

Using `make` for compilation and `make test` to run the program.

### Reference
- [GNU MP](https://gmplib.org/manual/index.html#Top)
- [gcdext.c File Reference](https://fossies.org/dox/gmp-6.1.2/mpz_2gcdext_8c.html)
